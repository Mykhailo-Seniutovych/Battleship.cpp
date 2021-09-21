using System.Net.Sockets;

namespace Battleship.Server.Utils
{
    public static class NetworkStreamExtensions
    {
        public static bool IsAlive(this NetworkStream stream)
        {
            try
            {
                if (stream != null && stream.Socket != null && stream.Socket.Connected)
                {
                    if (stream.Socket.Poll(0, SelectMode.SelectRead))
                    {
                        byte[] buff = new byte[1];
                        if (stream.Socket.Receive(buff, SocketFlags.Peek) == 0)
                        {
                            return false;
                        }
                        else
                        {
                            return true;
                        }
                    }

                    return true;
                }
                else
                {
                    return false;
                }
            }
            catch
            {
                return false;
            }
        }
    }
}