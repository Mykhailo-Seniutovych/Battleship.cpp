namespace Battleship.Server.Models
{
    public class IncomingConnection
    {
        public string PlayerNickname { get; set; }
        public string OpponentNickname { get; set; }
        public string AuthCode { get; set; }
    }
}