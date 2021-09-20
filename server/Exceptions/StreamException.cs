using System;

namespace Battleship.Server.Exceptions
{
    public class StreamException : Exception
    {
        public StreamException(string message) : base(message)
        {
        }
    }
}