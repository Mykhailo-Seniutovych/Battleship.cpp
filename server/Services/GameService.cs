using System;
using System.Net.Sockets;
using System.Threading.Tasks;
using Battleship.Server.Interfaces;
using Battleship.Server.Models;
using Microsoft.Extensions.Logging;

namespace Battleship.Server.Services
{
    public class GameService : IGameService
    {
        private const int PlayerResponseTimeout = 10 * 60 * 1000;
        private readonly ILogger<GameService> _logger;
        private readonly IMessageService _messageService;
        public GameService(
            ILogger<GameService> logger,
            IMessageService messageService)
        {
            _logger = logger;
            _messageService = messageService;
        }
        public Task StartGame(PlayerConnection player1Connection, PlayerConnection player2Connection)
        {
            return Task.Run(async () =>
            {
                var stream1 = player1Connection.Stream;
                var stream2 = player2Connection.Stream;
                try
                {
                    _logger.LogInformation(
                        "Starting the game between the game between '{0}' and '{1}'.",
                        player1Connection.PlayerNickname,
                        player2Connection.PlayerNickname);

                    await InformStartGame(stream1, stream2);

                    stream1.ReadTimeout = PlayerResponseTimeout;
                    stream2.ReadTimeout = PlayerResponseTimeout;

                    await Task.WhenAll(
                        TransferDataBetweenStreams(stream1, stream2),
                        TransferDataBetweenStreams(stream2, stream1));

                    _logger.LogInformation(
                        "Game between '{0}' and '{1}' finished.",
                        player1Connection.PlayerNickname,
                        player2Connection.PlayerNickname);
                }
                catch (Exception ex)
                {
                    _logger.LogError(
                        ex,
                        "Unexpected error happened during the game between '{0}' and '{1}'.",
                        player1Connection.PlayerNickname,
                        player2Connection.PlayerNickname);

                    stream1.Close();
                    stream2.Close();
                }
            });
        }

        private async Task InformStartGame(NetworkStream stream1, NetworkStream stream2)
        {
            var player1Starts = new Random().Next(2) == 1;
            var player2Starts = !player1Starts;

            var timeout = TimeSpan.FromMilliseconds(PlayerResponseTimeout);
            await _messageService.SendMessage(
                stream1, new MessageWrapper<GameStartParams>(new GameStartParams(player1Starts)), timeout);
            await _messageService.SendMessage(
                stream2, new MessageWrapper<GameStartParams>(new GameStartParams(player2Starts)), timeout);
        }

        private Task TransferDataBetweenStreams(NetworkStream sender, NetworkStream receiver)
        {
            return Task.Run(async () =>
            {
                const int bufferSize = 1024;

                int countOfBytesRead;
                var buffer = new byte[bufferSize];
                while ((countOfBytesRead = await sender.ReadAsync(buffer, 0, buffer.Length)) != 0)
                {
                    await receiver.WriteAsync(buffer, 0, countOfBytesRead);
                    buffer = new byte[bufferSize];
                }

                sender.Close();
                receiver.Close();
            });
        }
    }
}