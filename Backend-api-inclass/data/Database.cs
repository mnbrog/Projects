using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using MySql.Data.MySqlClient;


namespace Backend-api-inclass.data
{
    public class Database
    {
        private string server;
        private string port;

        private string username;

        private string password;

        private string schema;

        public MySqlConnection GetPublicConnection(){

            string cs = $"server={server};user={username};database={database};port={port};password={password};";
            using var con = new MySqlConnection(cs);
            con.Open();
            // // MySqlCommand cmd = new MySqlCommand(stm, con);
            // string stm = "SELECT * FROM sport_teams WHERE Id = 4"; 
            // using var cmd = new MySqlCommand(stm, con); 
            // using MySqlDataReader rdr = cmd.ExecuteReader(); 

            // while(rdr.Read()){
            //     Console.WriteLine($"{rdr.GetString(1)} {rdr.GetString(2)}"); 
            //}

        }

    }
}