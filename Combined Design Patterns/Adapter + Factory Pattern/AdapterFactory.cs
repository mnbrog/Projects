using Adapter___Factory_Pattern;

public static class AdapterFactory
{
    public static ICommunicationAdapter GetAdapter(string type)
    {
        switch (type)
        {
            case "HTTP":
            var http = new HttpAdapter();
                return http;
            case "FTP":
             var ftp = new FtpAdapter();
                return ftp;
            default:
                throw new ArgumentException("Unsupported adapter type");
        }
    }
}