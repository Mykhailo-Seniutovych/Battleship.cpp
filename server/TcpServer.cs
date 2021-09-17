using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text.Json;
using System.Threading;
using System.Threading.Tasks;
using Battleship.Server.Constants;
using Battleship.Server.Exceptions;
using Battleship.Server.Models;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace Battleship.Server
{
    public class TcpServer : IHostedService
    {
        private const int PortNumber = 5000;

        private readonly TimeSpan IncomingConnectionTimeout = TimeSpan.FromSeconds(5);
        private readonly int PlayerResponseTimeout = TimeSpan.FromMinutes(10).Milliseconds;

        private TcpListener _tcpListener;
        private Dictionary<string, PlayerConnection> _waitingConnections = new Dictionary<string, PlayerConnection>();
        private readonly ILogger<TcpServer> _logger;

        public TcpServer(ILogger<TcpServer> logger)
        {
            _logger = logger;

            var _localAddr = IPAddress.Parse("0.0.0.0");
            _tcpListener = new TcpListener(_localAddr, PortNumber);
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
            Task.Run(() =>
            {
                _tcpListener.Start();
                _logger.LogInformation("TCP Server started, listening on port {0}", PortNumber);

                while (true)
                {
                    try
                    {
                        var client = _tcpListener.AcceptTcpClient();
                        var incomingStream = client.GetStream();
                        var connection = GetIncomingConnection(incomingStream);
                        AuthorizeConnection(connection);

                        StartGameOrAddToWaiting(connection, incomingStream);
                    }
                    catch (Exception ex)
                    {
                        _logger.LogError(ex, "Unexpected error happened when processing incomming connection.");
                    }
                }
            });

            return Task.CompletedTask;
        }

        private IncomingConnection GetIncomingConnection(NetworkStream incomingStream)
        {
            var cancellationTokenSource = new CancellationTokenSource();
            cancellationTokenSource.CancelAfter(IncomingConnectionTimeout);

            var buffer = new byte[1024];
            var countOfBytesRead = incomingStream.Read(buffer, 0, buffer.Length);
            if (countOfBytesRead == 0)
            {
                throw new AuthenticationException("Client didn't provide connection information.");
            }
            var incomingMsg = System.Text.Encoding.ASCII.GetString(buffer, 0, countOfBytesRead);
            var connection = JsonSerializer.Deserialize<IncomingConnection>(incomingMsg);
            return connection;
        }

        private void AuthorizeConnection(IncomingConnection connection)
        {
            if (connection.PassCode != AuthConstants.PassCode)
            {
                throw new AuthenticationException("Unknow client connected.");
            }
        }

        private void StartGameOrAddToWaiting(IncomingConnection connection, NetworkStream incomingStream)
        {
            if (_waitingConnections.ContainsKey(connection.OpponentNickname))
            {
                var opponentConnection = _waitingConnections[connection.OpponentNickname];
                StartGame(new PlayerConnection(connection, incomingStream), opponentConnection);
            }
            else
            {
                _logger.LogInformation(
                    "New player '{0}' connected, and is waiting for another player '{1}'.",
                    connection.PlayerNickname,
                    connection.OpponentNickname);
                _waitingConnections.Add(connection.PlayerNickname, new PlayerConnection(connection, incomingStream));
            }
        }

        private void StartGame(PlayerConnection player1Connection, PlayerConnection player2Connection)
        {
            Task.Run(async () =>
            {
                try
                {
                    var player1Starts = new Random().Next(2) == 1;
                    var player2Starts = !player1Starts;

                    await JsonSerializer.SerializeAsync<GameStartParams>(
                        player1Connection.Stream, new GameStartParams(player1Starts));
                    await JsonSerializer.SerializeAsync<GameStartParams>(
                        player2Connection.Stream, new GameStartParams(player2Starts));


                    player1Connection.Stream.ReadTimeout = PlayerResponseTimeout;
                    player2Connection.Stream.ReadTimeout = PlayerResponseTimeout;

                    var shootingStream = player1Starts ? player1Connection.Stream : player2Connection.Stream;
                    var receivingStream = player1Starts ? player2Connection.Stream : player1Connection.Stream;

                    int countOfBytesRead;
                    var buffer = new byte[1024];
                    while ((countOfBytesRead = shootingStream.Read(buffer, 0, buffer.Length)) != 0)
                    {
                        receivingStream.Write(buffer, 0, countOfBytesRead);

                        var shootingStreamCopy = shootingStream;
                        shootingStream = receivingStream;
                        receivingStream = shootingStreamCopy;

                        buffer = new byte[1024];
                    }

                    shootingStream.Dispose();
                    receivingStream.Dispose();
                }
                catch (Exception ex)
                {
                    _logger.LogError(
                        ex,
                        "Unexpected error happened during the game between '{0}' and '{1}'.",
                        player1Connection.PlayerNickname,
                        player2Connection.PlayerNickname);
                }
            });
        }
    }
}
