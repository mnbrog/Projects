stringcs=  @"URI=file:C:\Users\Michael Brogan\2024SpringRepo\database\test.db";
using var con=new SQLiteConnection(cs);
con.Open();
string stm = "SELECT * FROM test"; 
using var cmd = new SQLiteCommand(stm, con); 

using SQLiteDataReader rdr = cmd.ExecuteReader;
using var cmd = new SQLiteCommand(con);
cmd.CommandText = @"UPDATE test set title = @title, author = @author WHERE id=@id";
cmd.Parameters.AddWithValue("@id",value.Id);
cmd.Parameters.AddWithValue("@title",value.Title);
cmd.Parameters.AddWithValue("@author",value.Author);
cmd.Prepare();
cmd.ExecuteNonQuery();
