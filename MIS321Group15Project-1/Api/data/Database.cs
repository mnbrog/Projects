using MySql.Data.MySqlClient;

namespace Api.data
{
    public class Database
    {
        private string server = "qzkp8ry756433yd4.cbetxkdyhwsb.us-east-1.rds.amazonaws.com";
        private string port = "3306";
        private string username = "ylbw8hpmkntm5jmm";
        private string password = "lvkimmknj3w05woy";
        private string schema = "y47762de32w3uzq2";


        public MySqlConnection GetPublicConnection(){
            string cs= $"server={server};user={username};database={schema};port={port};password={password}";
            var con = new MySqlConnection(cs);
           return con;
        }


        
    }
}