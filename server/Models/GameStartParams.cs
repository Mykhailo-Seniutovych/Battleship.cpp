namespace Battleship.Server.Models
{
    /// <summary>
    /// Parameters for a game start, once two players were connected
    /// </summary>
    /// <param name="YouBeginGame">Defines whether a giving player should start the game by having a first shot.</param>
    public record GameStartParams(bool YouBeginGame);
}