using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace API
{
    public class ConnectionString
    {
        public string cs {get; set;}

        public ConnectionString()
        {
        string server = "m7nj9dclezfq7ax1.cbetxkdyhwsb.us-east-1.rds.amazonaws.com";
        string database = "yrnpcqsnrb3nf39e";
        string port = "3306";
        string userName = "vy397n4jti8aejv6";
        string password = "ot0ec8je0omcjkis";

        cs = $@"server={server};user={userName};database={database};port={port};password={password};";
        }
    }
}