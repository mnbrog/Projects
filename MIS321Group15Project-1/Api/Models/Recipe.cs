using Api.data;
using MySql.Data.MySqlClient;
using System.Data;
using MySql.Data;


namespace Api.Models
{
    public class Recipe
    {
        public int Id{get; set;}
        public string MealName{get; set;}

        public string Category{get; set;}

        public string Instructions{get; set;}

        public string MealImg{get; set;}

        public string Ingredient1{get; set;}
        public string Ingredient2{get; set;}
        public string Ingredient3{get; set;}
        public string Ingredient4{get; set;}
        public string Ingredient5{get; set;}
        public string Ingredient6{get; set;}
        public string Ingredient7{get; set;}
        public string Ingredient8{get; set;}
        public string Ingredient9{get; set;}
        public string Ingredient10{get; set;}
        
        public string Measure1{get; set;}
        public string Measure2{get; set;}
        public string Measure3{get; set;}
        public string Measure4{get; set;}
        public string Measure5{get; set;}
        public string Measure6{get; set;}
        public string Measure7{get; set;}
        public string Measure8{get; set;}
        public string Measure9{get; set;}
        public string Measure10{get; set;}

        // public string Deleted{get; set;}

         public static List<Recipe> GetAllRecipes(){
            List<Recipe> myRecipes = new List<Recipe>();
            Database database = new Database();
            using var con = database.GetPublicConnection();
                string stm = "SELECT * FROM Recipes";
                MySqlCommand cmd = new MySqlCommand(stm, con);
                con.Open();
                MySqlDataReader rdr = cmd.ExecuteReader();
                while(rdr.Read()){
                myRecipes.Add(new Recipe(){Id= rdr.GetInt32(0), MealName = rdr.GetString(1), Category = rdr.GetString(2), Instructions = rdr.GetString(3), 
                MealImg = rdr.GetString(4), Ingredient1 = rdr.GetString(5), Ingredient2 = rdr.GetString(6), Ingredient3 = rdr.GetString(7),
                Ingredient4 = rdr.GetString(8), Ingredient5 = rdr.GetString(9), Ingredient6 = rdr.GetString(10), Ingredient7 = rdr.GetString(11),
                Ingredient8 = rdr.GetString(12), Ingredient9 = rdr.GetString(13), Ingredient10 = rdr.GetString(14), Measure1 = rdr.GetString(15), Measure2 = rdr.GetString(16), Measure3 = rdr.GetString(17),
                Measure4 = rdr.GetString(18), Measure5 = rdr.GetString(19), Measure6 = rdr.GetString(20), Measure7 = rdr.GetString(21), Measure8 = rdr.GetString(22),
                Measure9 = rdr.GetString(23), Measure10 = rdr.GetString(24)}); 
                }
                con.Close();
                return myRecipes;
                }


            public void AddRecipe(Recipe recipe){
            Database database = new Database();
            var con = database.GetPublicConnection();
            string stm = @"insert into Recipes(MealName, Category, Instructions, MealImg, Ingredient1, Ingredient2, Ingredient3, Ingredient4, Ingredient5, 
            Ingredient6 , Ingredient7 , Ingredient8, Ingredient9 , Ingredient10, Measure1, Measure2, Measure3 , Measure4, Measure5, Measure6, 
            Measure7,Measure8, Measure9, Measure10) values (@MealName, @Category, @Instructions, @MealImg, @Ingredient1, @Ingredient2, @Ingredient3, @Ingredient4, @Ingredient5, 
            @Ingredient6 , @Ingredient7 , @Ingredient8, @Ingredient9 , @Ingredient10, @Measure1, @Measure2, @Measure3 ,@Measure4, @Measure5, @Measure6, 
            @Measure7,@Measure8, @Measure9, @Measure10);";
            con.Open();
            MySqlCommand cmd = new MySqlCommand(stm, con);
            cmd.Parameters.AddWithValue("@MealName",recipe.MealName);
            cmd.Parameters.AddWithValue("@Category",recipe.Category);
            cmd.Parameters.AddWithValue("@Instructions", recipe.Instructions);
            cmd.Parameters.AddWithValue("@MealImg",recipe.MealImg);
            cmd.Parameters.AddWithValue("@Ingredient1",recipe.Ingredient1);
            cmd.Parameters.AddWithValue("@Ingredient2",recipe.Ingredient2);
            cmd.Parameters.AddWithValue("@Ingredient3",recipe.Ingredient3);
            cmd.Parameters.AddWithValue("@Ingredient4",recipe.Ingredient4);
            cmd.Parameters.AddWithValue("@Ingredient5",recipe.Ingredient5);
            cmd.Parameters.AddWithValue("@Ingredient6",recipe.Ingredient6);
            cmd.Parameters.AddWithValue("@Ingredient7",recipe.Ingredient7);
            cmd.Parameters.AddWithValue("@Ingredient8",recipe.Ingredient8);
            cmd.Parameters.AddWithValue("@Ingredient9",recipe.Ingredient9);
            cmd.Parameters.AddWithValue("@Ingredient10",recipe.Ingredient10);
            cmd.Parameters.AddWithValue("@Measure1",recipe.Measure1);
            cmd.Parameters.AddWithValue("@Measure2",recipe.Measure2);
            cmd.Parameters.AddWithValue("@Measure3",recipe.Measure3);
            cmd.Parameters.AddWithValue("@Measure4",recipe.Measure4);
            cmd.Parameters.AddWithValue("@Measure5",recipe.Measure5);
            cmd.Parameters.AddWithValue("@Measure6",recipe.Measure6);
            cmd.Parameters.AddWithValue("@Measure7",recipe.Measure7);
            cmd.Parameters.AddWithValue("@Measure8",recipe.Measure8);
            cmd.Parameters.AddWithValue("@Measure9",recipe.Measure9);
            cmd.Parameters.AddWithValue("@Measure10",recipe.Measure10);
        
           
           cmd.Prepare();
           cmd.ExecuteNonQuery();
    
            con.Close();
        }

        public void UpdateRecipe(int Id, Recipe recipe){
            Database database = new Database();
            var con = database.GetPublicConnection();
            string stm = @"UPDATE Recipes SET MealName=@MealName, Category=@Category, Instructions=@Instructions, MealImg=@MealImg, 
            Ingredient1=@Ingredient1, Ingredient2=@Ingredient2, Ingredient3=@Ingredient3, Ingredient4=@Ingredient4, Ingredient5=@Ingredient5, 
            Ingredient6=@Ingredient6 , Ingredient7=@Ingredient7 , Ingredient8=@Ingredient8, Ingredient9=@Ingredient9 , Ingredient10=@Ingredient10,
             Measure1=@Measure1, Measure2=@Measure2, Measure3=@Measure3, Measure4=@Measure4, Measure5=@Measure5, Measure6=@Measure6, 
            Measure7=@Measure7,Measure8=@Measure8, Measure9=@Measure9, Measure10=@Measure10 WHERE Id=@Id;";
            con.Open();
            MySqlCommand cmd = new MySqlCommand(stm, con);
            cmd.Parameters.AddWithValue("@Id",Id);
            cmd.Parameters.AddWithValue("@MealName",recipe.MealName);
            cmd.Parameters.AddWithValue("@Category",recipe.Category);
            cmd.Parameters.AddWithValue("@Instructions", recipe.Instructions);
            cmd.Parameters.AddWithValue("@MealImg",recipe.MealImg);
            cmd.Parameters.AddWithValue("@Ingredient1",recipe.Ingredient1);
            cmd.Parameters.AddWithValue("@Ingredient2",recipe.Ingredient2);
            cmd.Parameters.AddWithValue("@Ingredient3",recipe.Ingredient3);
            cmd.Parameters.AddWithValue("@Ingredient4",recipe.Ingredient4);
            cmd.Parameters.AddWithValue("@Ingredient5",recipe.Ingredient5);
            cmd.Parameters.AddWithValue("@Ingredient6",recipe.Ingredient6);
            cmd.Parameters.AddWithValue("@Ingredient7",recipe.Ingredient7);
            cmd.Parameters.AddWithValue("@Ingredient8",recipe.Ingredient8);
            cmd.Parameters.AddWithValue("@Ingredient9",recipe.Ingredient9);
            cmd.Parameters.AddWithValue("@Ingredient10",recipe.Ingredient10);
            cmd.Parameters.AddWithValue("@Measure1",recipe.Measure1);
            cmd.Parameters.AddWithValue("@Measure2",recipe.Measure2);
            cmd.Parameters.AddWithValue("@Measure3",recipe.Measure3);
            cmd.Parameters.AddWithValue("@Measure4",recipe.Measure4);
            cmd.Parameters.AddWithValue("@Measure5",recipe.Measure5);
            cmd.Parameters.AddWithValue("@Measure6",recipe.Measure6);
            cmd.Parameters.AddWithValue("@Measure7",recipe.Measure7);
            cmd.Parameters.AddWithValue("@Measure8",recipe.Measure8);
            cmd.Parameters.AddWithValue("@Measure9",recipe.Measure9);
            cmd.Parameters.AddWithValue("@Measure10",recipe.Measure10);
        
           
           cmd.Prepare();
           cmd.ExecuteNonQuery();
    
            con.Close();

        }


    }
}