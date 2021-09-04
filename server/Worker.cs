using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace battleship.server
{
    // TODO: improve this POC implementaion
    public class Worker : IHostedService
    {
        private const int PortNumber = 80;
        private TcpListener _tcpListener;

        private readonly ILogger<Worker> _logger;

        public Worker(ILogger<Worker> logger)
        {
            _logger = logger;

            var _localAddr = IPAddress.Parse("0.0.0.0");
            _tcpListener = new TcpListener(_localAddr, PortNumber);
        }

        public Task StartAsync(CancellationToken cancellationToken)
        {
            Task.Run(() =>
            {
                _tcpListener.Start();
                _logger.LogInformation("Started server, listening on port {0}", PortNumber);

                try
                {
                    var pingMsg = Encoding.ASCII.GetBytes("connected");

                    var client1 = _tcpListener.AcceptTcpClient();
                    var streamSender = client1.GetStream();
                    streamSender.Write(pingMsg, 0, pingMsg.Length);

                    var client2 = _tcpListener.AcceptTcpClient();
                    var streamReceiver = client2.GetStream();
                    streamReceiver.Write(pingMsg, 0, pingMsg.Length);

                    var startMsg = Encoding.ASCII.GetBytes("start");
                    streamSender.Write(startMsg, 0, startMsg.Length);

                    int countOfBytesRead;
                    byte[] bytes = new byte[256];
                    while ((countOfBytesRead = streamSender.Read(bytes, 0, bytes.Length)) != 0)
                    {
                        streamReceiver.Write(bytes, 0, countOfBytesRead);

                        var newReceiver = streamSender;
                        streamSender = streamReceiver;
                        streamReceiver = newReceiver;
                    }
                }
                catch (Exception ex)
                {
                    _logger.LogError(ex, "Unexpected error happened in TCP server");
                }
                finally
                {
                    _tcpListener.Stop();
                }
            });
            return Task.CompletedTask;
        }

        public Task StopAsync(CancellationToken cancellationToken)
        {
            _logger.LogInformation("Stopping TCP Server");
            _tcpListener.Stop();
            _logger.LogInformation("TCP Server stopped");

            return Task.CompletedTask;
        }
    }
}
