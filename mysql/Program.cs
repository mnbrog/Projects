// See https://aka.ms/new-console-template for more information
using System.Data;
using MySql.Data;
using MySql.Data.MySqlClient;

string cs="server=s465z7sj4pwhp7fn.cbetxkdyhwsb.us-east-1.rds.amazonaws.com;user=bz2ddzvmt88o7g1k;database=kksr2zopg31zk81i;port=3306;password=uem5rpmx4zqjb2is";
using var con = new MySqlConnection(cs);
con.Open();
// MySqlCommand cmd = new MySqlCommand(stm, con);
string stm = "SELECT * FROM sport_teams WHERE Id = 4"; 
using var cmd = new MySqlCommand(stm, con); 
using MySqlDataReader rdr = cmd.ExecuteReader(); 

while(rdr.Read()){
    Console.WriteLine($"{rdr.GetString(1)} {rdr.GetString(2)}"); 
} 


//heroku new project
//heroku resources -JawsDb add on
//mysqlworkbench coonnection with jaws connection string
//
//dotnet new console
//install mysql.data -everytime do this
//connection string from jaws
