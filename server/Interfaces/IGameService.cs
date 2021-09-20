using System.Threading.Tasks;
using Battleship.Server.Models;

namespace Battleship.Server.Interfaces
{
    public interface IGameService
    {    
        Task StartGame(PlayerConnection player1Connection, PlayerConnection player2Connection);
    }
}