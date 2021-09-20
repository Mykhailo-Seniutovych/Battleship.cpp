using System;
using System.IO;
using System.Threading.Tasks;

namespace Battleship.Server.Interfaces
{
    public interface IMessageService
    {
        Task<T> ReadNextMessage<T>(Stream stream, TimeSpan timeout);
        Task SendMessage<T>(Stream stream, T message, TimeSpan timeout);
    }

}