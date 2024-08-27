namespace MovieApi.Models
{
    public class Movie
    {
        public int MovieId { get; set; }
        public string MovieTitle { get; set; }
        public int Rating { get; set; }
        public DateOnly DateReleased { get; set; }
        public bool Favorited { get; set; } = false;
        public bool Deleted { get; set; } = false;
    }
}
