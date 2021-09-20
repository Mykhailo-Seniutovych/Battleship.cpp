using Battleship.Server.Interfaces;
using Battleship.Server.Models;
using Battleship.Server.Services;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;

namespace Battleship.Server
{
    public class Program
    {
        public static void Main(string[] args)
        {
            CreateHostBuilder(args).Build().Run();
        }

        public static IHostBuilder CreateHostBuilder(string[] args) =>
            Host.CreateDefaultBuilder(args)
                .ConfigureServices((hostContext, services) =>
                {
                    services.AddSingleton<IGameService, GameService>();
                    services.AddSingleton<IMessageService, MessageService>();
                    services.AddHostedService<TcpServer>();
                });
    }
}
