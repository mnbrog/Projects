using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Cors;
using MovieApi.Models;
using System.Configuration;

namespace MovieApi.Controllers
{
    [ApiController]
    [Route("[controller]")]
    [EnableCors("OpenPolicy")]
    public class MoviesController : ControllerBase
    {

        // GET: Retrieve all non-deleted movies ordered by rating
        [HttpGet]
        public List<Movie> Get()
        {
            MovieDataAccess movieDataAccess = new MovieDataAccess();
            return movieDataAccess.GetAllMovies();
        }

        // POST: Add a new movie
        [HttpPost]
        public Movie Post(Movie movie)
        {
            MovieDataAccess movieDataAccess = new MovieDataAccess();
            movieDataAccess.AddMovie(movie);
            // Assuming AddMovie updates the movie with an ID and returns it
            return movie;
        }         

        // PUT: Update favorite status of a movie
        [HttpPut("favorite/{id}")]
        public void UpdateFavoriteStatus(int id, [FromBody] bool favorited)
        {
            MovieDataAccess movieDataAccess = new MovieDataAccess();
            movieDataAccess.UpdateFavoriteStatus(id, favorited);
        }

        // PUT: Soft delete a movie
        [HttpDelete("delete/{id}")]
        public void SoftDeleteMovie(int id)
        {
            MovieDataAccess movieDataAccess = new MovieDataAccess();
            movieDataAccess.SoftDeleteMovie(id);
        }


    }
}
