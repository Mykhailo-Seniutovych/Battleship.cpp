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
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace Battleship.Server
{
    public class TcpServer : IHostedService
    {
        private const int PortNumber = 5000;
        private const int DefaultBufferSize = 1024;
        private readonly TimeSpan _streamTimeout = TimeSpan.FromSeconds(1000); // TODO: use smaller interval in prod

        private readonly object Locker = new Object();
        private TcpListener _tcpListener;
        private Dictionary<string, PlayerConnection> _waitingConnections = new Dictionary<string, PlayerConnection>();
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

            StartConnectionCleaner();

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
                if (_waitingConnections.ContainsKey(connection.OpponentNickname))
                {
                    var opponentConnection = _waitingConnections[connection.OpponentNickname];
                    _ = _gameService.StartGame(new PlayerConnection(connection, incomingStream), opponentConnection);

                    _waitingConnections.Remove(connection.OpponentNickname);
                    return;
                }

                var playerAlreadyExists = _waitingConnections.ContainsKey(connection.PlayerNickname);
                if (playerAlreadyExists)
                {
                    var errorMsg = $"Nickname '{connection.PlayerNickname}' is not available at the moment, use another nickname.";
                    _messageService.SendMessage(incomingStream, new ErrorWrapper(errorMsg), _streamTimeout);
                    incomingStream.Close();
                    return;
                }

                _waitingConnections.Add(connection.PlayerNickname, new PlayerConnection(connection, incomingStream));
                _logger.LogInformation(
                    "New player '{0}' connected, and is waiting for another player '{1}'.",
                    connection.PlayerNickname,
                    connection.OpponentNickname);
            }
        }

        private byte[] GetLengthPrefixedMessage(string message)
        {
            var messageEncoded = System.Text.Encoding.ASCII.GetBytes(message);
            var buffer = new byte[DefaultBufferSize];

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

        private void StartConnectionCleaner()
        {
            Task.Run(async () =>
            {
                while (true)
                {
                    lock (Locker)
                    {
                        try
                        {
                            foreach (var connection in _waitingConnections)
                            {
                                var clientIsWaitingMoreThan10Mins =
                                    DateTime.Now - connection.Value.ConnectedTime >= TimeSpan.FromMinutes(10);
                                if (clientIsWaitingMoreThan10Mins)
                                {
                                    _waitingConnections.Remove(connection.Key);
                                }
                            }
                        }
                        catch (Exception ex)
                        {
                            _logger.LogError(ex, "Unexpected error happened when cleaning old waiting connections.");
                        }
                    }

                    await Task.Delay(TimeSpan.FromMinutes(2));
                }
            });
        }
    }
}
