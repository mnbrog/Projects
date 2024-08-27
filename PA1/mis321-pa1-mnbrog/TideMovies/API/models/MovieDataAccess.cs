using Microsoft.Data.SqlClient;
using System;
using System.Collections.Generic;
using System.Data;
using MovieApi.Models;
using Microsoft.AspNetCore.Cors;
using MySql.Data.MySqlClient;
using MySql.Data;
using API;
using NuGet.Protocol.Plugins;
public class MovieDataAccess 
{
    private readonly string connectionString;

    public MovieDataAccess()
    {
        ConnectionString connection = new ConnectionString();
        connectionString = connection.cs;
    }

    public List<Movie> GetAllMovies()
    {
        var movies = new List<Movie>();
        using (var connection = new MySqlConnection(connectionString))
        {
            connection.Open();
            var command = new MySqlCommand("SELECT MovieId, MovieTitle, Rating, DateReleased, Favorited, Deleted FROM Movies WHERE Deleted = 0", connection);
            using (var reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    movies.Add(new Movie
                    {
                        MovieId = reader.GetInt32(reader.GetOrdinal("MovieId")),
                        MovieTitle = reader.IsDBNull(reader.GetOrdinal("MovieTitle")) ? null : reader.GetString(reader.GetOrdinal("MovieTitle")),
                        Rating = reader.GetInt32(reader.GetOrdinal("Rating")),
                        DateReleased = DateOnly.FromDateTime(reader.GetDateTime(reader.GetOrdinal("DateReleased"))),
                        Favorited = reader.GetBoolean(reader.GetOrdinal("Favorited")),
                        Deleted = reader.GetBoolean(reader.GetOrdinal("Deleted"))
                    });
                }
            }
            connection.Close();
        }
        return movies;
    }

    public void AddMovie(Movie movie)
    {
        using (var connection = new MySqlConnection(connectionString))
        {
            connection.Open();
            var command = new MySqlCommand("INSERT INTO Movies (MovieTitle, Rating, DateReleased, Favorited, Deleted) VALUES (@MovieTitle, @Rating, @DateReleased, @Favorited, @Deleted)", connection);
            command.Parameters.AddWithValue("@MovieTitle", movie.MovieTitle ?? (object)DBNull.Value);
            command.Parameters.AddWithValue("@Rating", movie.Rating);
            command.Parameters.AddWithValue("@DateReleased", movie.DateReleased.ToDateTime(TimeOnly.MinValue));
            command.Parameters.AddWithValue("@Favorited", movie.Favorited);
            command.Parameters.AddWithValue("@Deleted", movie.Deleted);
            command.ExecuteNonQuery();
            connection.Close();
        }
    }

    public void UpdateFavoriteStatus(int movieId, bool favorited)
    {
        using (var connection = new MySqlConnection(connectionString))
        {
            connection.Open();
            var command = new MySqlCommand("UPDATE Movies SET Favorited = @Favorited WHERE MovieId = @MovieId", connection);
            command.Parameters.AddWithValue("@MovieId", movieId);
            command.Parameters.AddWithValue("@Favorited", favorited);
            command.ExecuteNonQuery();
            connection.Close();
        }
    }

    public void SoftDeleteMovie(int movieId)
    {
        using (var connection = new MySqlConnection(connectionString))
        {
            connection.Open();
            var command = new MySqlCommand("UPDATE Movies SET Deleted = 1 WHERE MovieId = @MovieId", connection);
            command.Parameters.AddWithValue("@MovieId", movieId);
            command.ExecuteNonQuery();
            connection.Close();
        }
    }
}
