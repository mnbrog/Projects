using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Api.Models;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace Api.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class RecipesController : ControllerBase
    {
        // GET: api/Recipes
        [HttpGet]
        public List<Recipe> Get()
        {
            return Recipe.GetAllRecipes();
        }

        // GET: api/Recipes/5
        [HttpGet("{id}", Name = "Get")]
        public string Get(int id)
        {
            return "value";
        }

        // POST: api/Recipes
        [HttpPost]
        public void Post([FromBody] Recipe value)
        {
            Recipe utility = new Recipe();
            utility.AddRecipe(value);
            //API Except id but will not be used past Addmovie method, mySQL will auto increments id
        }

        // PUT: api/Recipes/5
        [HttpPut("{id}")]
        public void Put(int id, [FromBody] Recipe value)
        {
             Recipe utility = new Recipe();
             utility.UpdateRecipe(id,value);
        }

        // DELETE: api/Recipes/5
        [HttpDelete("{id}")]
        public void Delete(int id)
        {
        }
    }
}
