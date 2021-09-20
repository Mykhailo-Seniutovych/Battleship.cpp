using System;
using System.IO;
using System.Text;
using System.Text.Json;
using System.Threading;
using System.Threading.Tasks;
using Battleship.Server.Exceptions;
using Battleship.Server.Interfaces;

namespace Battleship.Server.Services
{
    public class MessageService : IMessageService
    {
        private readonly JsonSerializerOptions _jsonOptions = new JsonSerializerOptions
        {
            PropertyNamingPolicy = JsonNamingPolicy.CamelCase,
            PropertyNameCaseInsensitive = true,
            IgnoreNullValues = true
        };

        public async Task<T> ReadNextMessage<T>(Stream stream, TimeSpan timeout)
        {
            var messageLength = await ReadMessageLength(stream, timeout);

            var contentBuffer = new byte[messageLength];
            var tokenSource = new CancellationTokenSource();
            tokenSource.CancelAfter(timeout);

            var countOfBytesRead = await stream.ReadAsync(contentBuffer, 0, contentBuffer.Length, tokenSource.Token);
            if (countOfBytesRead == 0)
            {
                throw new StreamException("Message content was not present in the stream.");
            }
            var message = Encoding.ASCII.GetString(contentBuffer, 0, countOfBytesRead);
            var result = JsonSerializer.Deserialize<T>(message, _jsonOptions);
            return result;
        }

        public async Task SendMessage<T>(Stream stream, T message, TimeSpan timeout)
        {
            var messageJson = JsonSerializer.Serialize(message, _jsonOptions);
            var messageBuffer = Encoding.ASCII.GetBytes(messageJson);
            await SendMessageLength(stream, messageBuffer.Length, timeout);

            var tokenSource = new CancellationTokenSource();
            tokenSource.CancelAfter(timeout);
            await stream.WriteAsync(messageBuffer, 0, messageBuffer.Length, tokenSource.Token);
        }

        private async Task SendMessageLength(Stream stream, int length, TimeSpan timeout)
        {
            var lengthBuffer = BitConverter.GetBytes(length);
            if (BitConverter.IsLittleEndian)
            {
                Array.Reverse(lengthBuffer);
            }

            var tokenSource = new CancellationTokenSource();
            tokenSource.CancelAfter(timeout);
            await stream.WriteAsync(lengthBuffer, 0, lengthBuffer.Length, tokenSource.Token);
        }

        private async Task<int> ReadMessageLength(Stream stream, TimeSpan timeout)
        {
            var lengthBuffer = new byte[sizeof(int)];
            var tokenSource = new CancellationTokenSource();
            tokenSource.CancelAfter(timeout);

            var countOfBytesRead = await stream.ReadAsync(
                lengthBuffer, 0, lengthBuffer.Length, tokenSource.Token);
            if (countOfBytesRead == 0)
            {
                throw new StreamException("Message length was not present in the stream.");
            }

            if (BitConverter.IsLittleEndian)
            {
                Array.Reverse(lengthBuffer);
            }
            var length = BitConverter.ToInt32(lengthBuffer, 0);
            return length;
        }
    }
}