using Adapter___Factory_Pattern;

public class HttpAdapter : ICommunicationAdapter
{
    public void Send(string message)
    {
        Console.WriteLine("Sending HTTP message: " + message);
    }
}