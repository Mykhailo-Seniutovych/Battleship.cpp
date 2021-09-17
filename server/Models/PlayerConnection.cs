using System.Net.Sockets;

namespace Battleship.Server.Models
{
    public class PlayerConnection
    {
        public string PlayerNickname { get; set; }
        public string OpponentNickname { get; set; }
        public NetworkStream Stream { get; set; }

        public PlayerConnection(IncomingConnection incomingConnection, NetworkStream stream)
        {
            PlayerNickname = incomingConnection.PlayerNickname;
            OpponentNickname = incomingConnection.OpponentNickname;
            Stream = stream;
        }
    }
}