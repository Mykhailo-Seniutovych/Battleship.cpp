namespace Battleship.Server.Models
{
    public class IncomingConnection
    {
        public string PlayerNickname { get; set; }
        public string OpponentNickname { get; set; }
        public string PassCode { get; set; }

        public string PlayerBattleKey => PlayerNickname + OpponentNickname;
        public string OpponentBattleKey => OpponentNickname + PlayerNickname;
    }
}