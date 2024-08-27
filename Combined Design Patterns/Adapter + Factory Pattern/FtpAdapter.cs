using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Adapter___Factory_Pattern;
public class FtpAdapter : ICommunicationAdapter
{
    public void Send(string message)
    {
        Console.WriteLine("Sending FTP message: " + message);
    }
}