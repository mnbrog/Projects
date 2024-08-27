using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.OpenApi.Models;
using MySql.Data.MySqlClient;
using MovieApi.Models;
using MovieApi.Controllers;


var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
// Connection string setup
var connectionString = builder.Configuration.GetConnectionString("MovieDatabase");

// Registering MovieDataAccess
//builder.Services.AddScoped<MovieDataAccess>(sp => new MovieDataAccess(connectionString));

// Adding controllers
builder.Services.AddControllers();

// Setting up CORS (if needed)
builder.Services.AddCors(options =>
{
    options.AddPolicy("OpenPolicy", policy =>
    {
        policy.AllowAnyOrigin()
              .AllowAnyMethod()
              .AllowAnyHeader();
    });
});

// Configuring Swagger/OpenAPI
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen(c =>
{
    c.SwaggerDoc("v1", new OpenApiInfo { Title = "Movie API", Version = "v1" });
});

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseDeveloperExceptionPage();
    app.UseSwagger();
    app.UseSwaggerUI(c => c.SwaggerEndpoint("/swagger/v1/swagger.json", "Movie API v1"));
}

app.UseHttpsRedirection();
app.UseAuthorization();

app.UseCors("OpenPolicy"); // Apply CORS policy

app.MapControllers(); // Map controller routes

app.Run();
