document.addEventListener('DOMContentLoaded', init);
let movies = []

function init() {
  fetchAllMovies();
  document.getElementById('add-movie-form').addEventListener('submit', addMovie);
}

async function fetchAllMovies() {
  let response = await fetch('http://localhost:5030/movies');
  movies = await response.json();
  displayMovies(movies);
}
//dotnet aspnet-codegenerator controller -name movies -async -api --readWriteActions -outDir Controllers Substitute books for movies
function displayMovies(movies) {
  const movieList = document.getElementById('movie-list');
  movieList.innerHTML = ''; // Clear the list
  
  movies.forEach(movie => {
    const movieEl = document.importNode(document.getElementById('movie-template').content, true);
    movieEl.querySelector('[data-movie-name]').textContent = movie.movieTitle;
    movieEl.querySelector('[data-movie-rating]').textContent = `Rating: ${movie.rating}`;
    movieEl.querySelector('[data-movie-date-released]').textContent = `Released: ${movie.dateReleased}`;
    
    const favoriteButton = movieEl.querySelector('[data-favorite-button]');
    favoriteButton.textContent = movie.favorited ? 'Unfavorite' : 'Favorite';
    favoriteButton.addEventListener('click', () => toggleFavorite(movie.movieId, movie.favorited));
  
    const watchButton = movieEl.querySelector('[data-watch-button]');
    watchButton.href = `https://hdtoday.cc/search/${encodeURIComponent(movie.movieTitle.split(' ').join('-'))}`;
    watchButton.textContent = 'Watch';
  
    const deleteButton = movieEl.querySelector('[data-delete-button]');
    deleteButton.addEventListener('click', () => deleteMovie(movie.movieId));
  
    movieList.appendChild(movieEl);
  });
}

function addMovie(event) {
  event.preventDefault();
  const name = document.getElementById('movie-name').value;
  const rating = document.getElementById('movie-rating').value;
  const dateReleased = document.getElementById('movie-date-released').value;

  fetch('http://localhost:5030/movies', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify({
      movieTitle: name,
      rating: parseInt(rating, 10),
      dateReleased: dateReleased,
    }),
  })
  .then(response => response.json())
  .then(() => {
    fetchAllMovies();
    event.target.reset(); // Reset form fields
  })
  .catch(error => console.error('Error adding movie:', error));
}

function toggleFavorite(movieId, isFavorited) {
  fetch(`http://localhost:5030/movies/favorite/${movieId}`, {
    method: 'PUT',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify( !isFavorited ),
  })
  .then(() => {
    fetchAllMovies();
  })
  .catch(error => console.error('Error toggling favorite:', error));
}

function deleteMovie(movieId) {
  fetch(`http://localhost:5030/movies/delete/${movieId}`, {
    method: 'DELETE', 
    headers: {
      'Content-Type': 'application/json', // Appropriate headers
    }
  })
  .then(() => {
    fetchAllMovies(); // Re-fetch the movies list to update
  })
  .catch(error => {
    console.error('Error deleting movie:', error); // Error handling
  });
}






function scrollToTop() {
  window.scrollTo({top: 0, behavior: 'smooth'});
}
