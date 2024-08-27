document.addEventListener('DOMContentLoaded', init);

function init() {
    fetchAndDisplayCategories();
    initializeLocalStorage();
    document.getElementById('add-recipe-form').addEventListener('submit', addRecipe);
    document.getElementById('add-ingredient-btn').addEventListener('click', addIngredientField);
    closeModalEvents();
}

function fetchAndDisplayCategories() {
    fetch('https://www.themealdb.com/api/json/v1/1/categories.php')
        .then(response => response.json())
        .then(data => displayCategories(data.categories))
        .catch(error => console.error('Error fetching categories:', error));
}

function displayCategories(categories) {
  const recipeList = document.getElementById('recipe-list');
  recipeList.innerHTML = ''; // Clear existing content

  categories.forEach(category => {
      const categoryEl = document.createElement('div');
      categoryEl.className = 'category-card';

      const image = document.createElement('img');
      image.src = category.strCategoryThumb;
      image.alt = category.strCategory;
      categoryEl.appendChild(image);

      const title = document.createElement('h3');
      title.textContent = category.strCategory;
      categoryEl.appendChild(title);

      const description = document.createElement('p');
      description.textContent = category.strCategoryDescription;
      categoryEl.appendChild(description);

      // Adjusted button creation
      const viewRecipesBtn = document.createElement('button');
      viewRecipesBtn.textContent = 'View Recipes';
      viewRecipesBtn.className = 'view-recipes-btn'; // For styling
      viewRecipesBtn.onclick = function() {
          // Navigate to a new page with the category name as a query parameter
          window.location.href = `recipes.html?category=${encodeURIComponent(category.strCategory)}`;
      };
      categoryEl.appendChild(viewRecipesBtn);

      recipeList.appendChild(categoryEl);
  });
}


function fetchAndDisplayRecipesForCategory(categoryName) {
  const url = `https://www.themealdb.com/api/json/v1/1/filter.php?c=${categoryName}`;
  // Fetch recipes for the category and implement the display logic
  console.log(`Fetching recipes for category: ${categoryName}`);
  // Placeholder for fetching and displaying logic
}


// Rest of your functions: initializeLocalStorage, addIngredientField, closeModalEvents, etc., remain unchanged.

// These updates adjust the JavaScript to fetch category data from TheMealDB API and display it within the specified 'recipe-list' element on your page.
// Remember to style '.category-card' in your CSS to match the visual layout you prefer for these category cards.

function initializeLocalStorage() {
  if (!localStorage.getItem('recipes')) {
    localStorage.setItem('recipes', JSON.stringify([]));
  }
}

function getRecipesFromStorage() {
  return JSON.parse(localStorage.getItem('recipes'));
}
function addIngredientField() {
    const ingredientsContainer = document.getElementById('ingredients-container');
    const newInputGroup = document.createElement('div');
    newInputGroup.classList.add('input-group');
    
    const newInput = document.createElement('input');
    newInput.setAttribute('type', 'text');
    newInput.setAttribute('name', 'ingredients[]');
    newInput.placeholder = 'Ingredient';
    newInput.classList.add('input-field', 'ingredient-input');
    
    const removeButton = document.createElement('button');
    removeButton.type = 'button';
    removeButton.textContent = '-';
    removeButton.classList.add('remove-ingredient-btn');
    removeButton.onclick = function() {
      ingredientsContainer.removeChild(newInputGroup);
    };
  
    newInputGroup.appendChild(newInput);
    newInputGroup.appendChild(removeButton);
  
    ingredientsContainer.appendChild(newInputGroup);
  }
  
  function closeModalEvents() {
    // Close modals when the close button is clicked
    document.querySelectorAll('.close-button').forEach(button => {
      button.addEventListener('click', function() {
        this.closest('.modal').style.display = 'none';
      });
    });
  
    // Close modals when clicking outside of the modal content
    window.addEventListener('click', function(event) {
      if (event.target.classList.contains('modal')) {
        event.target.style.display = 'none';
      }
    });
  }

function displayRecipes() {
  const recipeList = document.getElementById('recipe-list');
  recipeList.innerHTML = '';
  const recipes = getRecipesFromStorage();
  recipes.forEach(recipe => {
    if (!recipe.deleted) {
      const recipeEl = document.importNode(document.getElementById('recipe-template').content, true);
      recipeEl.querySelector('[data-recipe-name]').textContent = recipe.name;
      recipeEl.querySelector('[data-recipe-rating]').textContent = `Rating: ${recipe.rating}`;
      recipeEl.querySelector('[data-recipe-date-added]').textContent = `Added: ${recipe.dateAdded}`;

      const favoriteButton = recipeEl.querySelector('[data-favorite-button]');
      favoriteButton.textContent = recipe.favorited ? 'Unfavorite' : 'Favorite';
      favoriteButton.addEventListener('click', () => toggleFavorite(recipe.id));

      const cookButton = recipeEl.querySelector('[data-cook-button]');
      cookButton.addEventListener('click', () => showRecipeInstructions(recipe.id));

      const buyButton = recipeEl.querySelector('[data-buy-button]');
      buyButton.addEventListener('click', () => showIngredientsList(recipe.id));

      const deleteButton = recipeEl.querySelector('[data-delete-button]');
      deleteButton.addEventListener('click', () => deleteRecipe(recipe.id));

      recipeList.appendChild(recipeEl);
    }
  });
}

function addRecipe(event) {
    event.preventDefault();
    const name = document.getElementById('recipe-name').value;
    const rating = document.getElementById('recipe-rating').value;
    const dateAdded = document.getElementById('recipe-date-added').value;
    const ingredients = Array.from(document.querySelectorAll('.ingredient-input'))
                             .map(input => input.value)
                             .filter(value => value.trim() !== '');
    const instructions = document.getElementById('recipe-instructions').value; // Capture instructions
    
    // Ensure instructions are provided
    if (!instructions.trim()) {
      alert("Please provide instructions for the recipe.");
      return;
    }
  
    const newRecipe = {
      id: Date.now(),
      name,
      rating: parseInt(rating, 10),
      dateAdded,
      ingredients,
      instructions, // Include instructions in the new recipe object
      favorited: false,
      deleted: false
    };
  
    const recipes = getRecipesFromStorage();
    recipes.push(newRecipe);
    localStorage.setItem('recipes', JSON.stringify(recipes));
    displayRecipes();
    event.target.reset(); // Optionally, clear the form fields after submission
  }
  


function toggleFavorite(recipeId) {
  const recipes = getRecipesFromStorage();
  const recipe = recipes.find(r => r.id === recipeId);
  recipe.favorited = !recipe.favorited;
  localStorage.setItem('recipes', JSON.stringify(recipes));
  displayRecipes();
}

function showRecipeInstructions(recipeId) {
  const recipes = getRecipesFromStorage();
  const recipe = recipes.find(r => r.id === recipeId);
  // Implement logic to display recipe instructions in a popup/modal
  alert(recipe.instructions || "No instructions provided.");
}

function showIngredientsList(recipeId) {
  const recipes = getRecipesFromStorage();
  const recipe = recipes.find(r => r.id === recipeId);
  // Implement logic to display ingredients list in a popup/modal
  alert(recipe.ingredients.join('\n') || "No ingredients listed.");
}

function deleteRecipe(recipeId) {
  const recipes = getRecipesFromStorage();
  const recipe = recipes.find(r => r.id === recipeId);
  recipe.deleted = true;
  localStorage.setItem('recipes', JSON.stringify(recipes));
  displayRecipes();
}

function scrollToTop() {
  window.scrollTo({top: 0, behavior: 'smooth'});
}


function showRecipeInstructions(recipeId) {
    const recipes = getRecipesFromStorage();
    const recipe = recipes.find(r => r.id === recipeId);
    const modal = document.getElementById('recipe-instructions-modal');
    const instructionsText = document.getElementById('instructions-text');
    instructionsText.textContent = recipe.instructions || "No instructions provided.";
    modal.style.display = "block";
  }
  
  function showIngredientsList(recipeId) {
    const recipes = getRecipesFromStorage();
    const recipe = recipes.find(r => r.id === recipeId);
    const modal = document.getElementById('ingredients-list-modal');
    const ingredientsList = document.getElementById('ingredients-list');
    ingredientsList.innerHTML = ''; // Clear previous ingredients
    recipe.ingredients.forEach(ingredient => {
      let li = document.createElement('li');
      li.textContent = ingredient;
      ingredientsList.appendChild(li);
    });
    modal.style.display = "block";
  }
  
  // Close the modal when the user clicks on <span> (x)
  document.querySelectorAll('.close-button').forEach(button => {
    button.onclick = function() {
      button.parentElement.parentElement.style.display = "none";
    }
  });
  
  // Close the modal when the user clicks anywhere outside of the modal
  window.onclick = function(event) {
    if (event.target.className === 'modal') {
      event.target.style.display = "none";
    }
  }
  