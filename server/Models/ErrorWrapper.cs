namespace Battleship.Server.Models
{
    public class ErrorWrapper
    {
        public bool IsError { get; set; }
        string Error { get; set; }

        public ErrorWrapper()
        {
        }
        
        public ErrorWrapper(string error)
        {
            Error = error;
            IsError = true;
        }
    }
}