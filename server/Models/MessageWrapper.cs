namespace Battleship.Server.Models
{
    public class MessageWrapper<T> : ErrorWrapper
    {
        public T Message { get; set; }

        public MessageWrapper(T message)
        {
            Message = message;
            IsError = false;
        }
    }
}