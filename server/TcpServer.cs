using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Threading.Tasks;
using Battleship.Server.Constants;
using Battleship.Server.Exceptions;
using Battleship.Server.Interfaces;
using Battleship.Server.Models;
using Battleship.Server.Utils;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace Battleship.Server
{
    public class TcpServer : IHostedService
    {
        private const int PortNumber = 5000;
        private readonly TimeSpan _streamTimeout = TimeSpan.FromSeconds(1000); // TODO: use smaller interval in prod

        private readonly object Locker = new Object();
        private TcpListener _tcpListener;
        private Dictionary<string, PlayerConnection> _waitingNamedConnections =
            new Dictionary<string, PlayerConnection>();
        private PlayerConnection _waitingRandomConnection = null;

        private readonly ILogger<TcpServer> _logger;
        private readonly IGameService _gameService;
        private readonly IMessageService _messageService;

        public TcpServer(ILogger<TcpServer> logger, IGameService gameService, IMessageService messageService)
        {
            _logger = logger;
            _gameService = gameService;
            _messageService = messageService;

            const string allInterfacesAddr = "0.0.0.0";
            var addr = IPAddress.Parse(allInterfacesAddr);
            _tcpListener = new TcpListener(addr, PortNumber);
        }

        public Task StopAsync(CancellationToken cancellationToken)
        {
            _logger.LogInformation("Stopping TCP Server");
            _tcpListener.Stop();
            _logger.LogInformation("TCP Server stopped");

            return Task.CompletedTask;
        }

        public Task StartAsync(CancellationToken cancellationToken)
        {
            Task.Run(async () =>
            {
                _tcpListener.Start();
                _logger.LogInformation("TCP Server started, listening on port {0}", PortNumber);

                while (true)
                {
                    NetworkStream incomingStream = null;
                    try
                    {
                        var client = _tcpListener.AcceptTcpClient();
                        incomingStream = client.GetStream();
                        var connection = await GetIncomingConnection(incomingStream);
                        AuthorizeConnection(connection);
                        StartGameOrAddToWaiting(connection, incomingStream);
                    }
                    catch (Exception ex)
                    {
                        incomingStream?.Close();
                        _logger.LogError(ex, "Unexpected error happened when processing incomming connection.");
                    }
                }
            });

            StartIdleConnectionsCleaner();
            StartUnaliveConnectionsCleaner();

            return Task.CompletedTask;
        }

        private async Task<IncomingConnection> GetIncomingConnection(NetworkStream incomingStream)
        {
            return await _messageService
                .ReadNextMessage<IncomingConnection>(incomingStream, _streamTimeout);
        }

        private void AuthorizeConnection(IncomingConnection connection)
        {
            if (connection.PassCode != AuthConstants.PassCode)
            {
                throw new StreamException("Unknow client connected.");
            }
        }

        private void StartGameOrAddToWaiting(IncomingConnection connection, NetworkStream incomingStream)
        {
            lock (Locker)
            {
                var isRandomPlayerBattle = string.IsNullOrEmpty(connection.OpponentNickname);
                var isAnotherRandomPlayerWaiting = _waitingRandomConnection != null;
                if (isRandomPlayerBattle && isAnotherRandomPlayerWaiting)
                {
                    _ = _gameService.StartGame(
                        new PlayerConnection(connection, incomingStream), _waitingRandomConnection);
                    _waitingRandomConnection = null;
                    return;
                }

                if (isRandomPlayerBattle && !isAnotherRandomPlayerWaiting)
                {
                    _waitingRandomConnection = new PlayerConnection(connection, incomingStream);
                    return;
                }

                var isAnotherWaitingForPlayer = _waitingNamedConnections.ContainsKey(connection.OpponentBattleKey);
                if (isAnotherWaitingForPlayer)
                {
                    var opponentConnection = _waitingNamedConnections[connection.OpponentBattleKey];
                    _ = _gameService.StartGame(new PlayerConnection(connection, incomingStream), opponentConnection);

                    _waitingNamedConnections.Remove(connection.OpponentBattleKey);
                    return;
                }

                var playersPairAlreadyExists = _waitingNamedConnections.ContainsKey(connection.PlayerBattleKey);
                if (playersPairAlreadyExists)
                {
                    var errorMsg = $"Battle for players '{connection.PlayerNickname}' and '{connection.OpponentNickname}'"
                        + " is not available at the moment. Please try again later or change the nickname.";

                    _messageService.SendMessage(incomingStream, new ErrorWrapper(errorMsg), _streamTimeout);
                    incomingStream.Close();
                    return;
                }

                _waitingNamedConnections.Add(connection.PlayerBattleKey, new PlayerConnection(connection, incomingStream));
                _logger.LogInformation(
                    "New player '{0}' connected, and is waiting for another player '{1}'.",
                    connection.PlayerNickname,
                    connection.OpponentNickname);
            }
        }

        private byte[] GetLengthPrefixedMessage(string message)
        {
            var messageEncoded = System.Text.Encoding.ASCII.GetBytes(message);

            var lengthPrefix = BitConverter.GetBytes(messageEncoded.Length);
            if (BitConverter.IsLittleEndian)
            {
                Array.Reverse(lengthPrefix);
            }

            var result = new byte[lengthPrefix.Length + messageEncoded.Length];
            lengthPrefix.CopyTo(result, 0);
            messageEncoded.CopyTo(result, 0);

            return result;
        }

        private void StartIdleConnectionsCleaner()
        {
            Task.Run(async () =>
            {
                while (true)
                {
                    lock (Locker)
                    {
                        try
                        {
                            var maxConnectionTimeout = TimeSpan.FromMinutes(10);
                            foreach (var connection in _waitingNamedConnections)
                            {
                                var clientIsWaitingTooLong =
                                    DateTime.Now - connection.Value.ConnectedTime >= maxConnectionTimeout;
                                if (clientIsWaitingTooLong)
                                {
                                    _waitingNamedConnections[connection.Key].Stream.Close();
                                    _waitingNamedConnections.Remove(connection.Key);
                                }
                            }
                            var isWaitingTooLong = _waitingRandomConnection != null
                                && DateTime.Now - _waitingRandomConnection.ConnectedTime >= maxConnectionTimeout;
                            if (isWaitingTooLong)
                            {
                                _waitingRandomConnection.Stream.Close();
                                _waitingRandomConnection = null;
                            }
                        }
                        catch (Exception ex)
                        {
                            _logger.LogError(ex, "Unexpected error happened when cleaning idle waiting connections.");
                        }
                    }

                    await Task.Delay(TimeSpan.FromMinutes(2));
                }
            });
        }

        private void StartUnaliveConnectionsCleaner()
        {
            Task.Run(async () =>
            {
                while (true)
                {
                    lock (Locker)
                    {
                        try
                        {
                            foreach (var connection in _waitingNamedConnections)
                            {
                                if (!connection.Value.Stream.IsAlive())
                                {
                                    _waitingNamedConnections[connection.Key].Stream.Close();
                                    _waitingNamedConnections.Remove(connection.Key);
                                }
                            }

                            if (_waitingRandomConnection != null && !_waitingRandomConnection.Stream.IsAlive())
                            {
                                _waitingRandomConnection.Stream.Close();
                                _waitingRandomConnection = null;
                            }
                        }
                        catch (Exception ex)
                        {
                            _logger.LogError(ex, "Unexpected error happened when cleaning unalive waiting connections.");
                        }
                    }

                    await Task.Delay(TimeSpan.FromSeconds(20));
                }
            });
        }
    }
}
