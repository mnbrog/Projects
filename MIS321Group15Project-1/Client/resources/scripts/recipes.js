document.addEventListener('DOMContentLoaded', function() {
    const recipesContainer = document.querySelector('.container');
    const recipeModal = new bootstrap.Modal(document.getElementById('recipeModal'));
    const modalTitle = document.getElementById('recipeModalLabel');
    const modalBody = document.querySelector('.modal-body');
    const buyButton = document.getElementById('buyRecipe');
    const editButton = document.getElementById('editRecipe');
    const isAdmin = false; // This should be replaced with actual logic to determine if the user is an admin
    let allLoadedRecipes = [];

    function displayRecipes(recipes) {
        if (recipes.length === 0) {
            recipesContainer.innerHTML = '<p>No recipes found.</p>';
            return;
        }

        const recipesHtml = recipes.map(recipe => `
            <div class="card recipe-card" style="width: 18rem;" data-recipe-id="${recipe.id}">
                <img src="${recipe.imageUrl}" class="card-img-top" alt="${recipe.name}">
                <div class="card-body">
                    <h5 class="card-title">${recipe.name}</h5>
                    <p class="card-text">${recipe.description}</p>
                    <button class="btn btn-primary view-recipe">View Recipe</button>
                </div>
            </div>
        `).join('');

        recipesContainer.innerHTML = `<div class="row">${recipesHtml}</div>`;

        document.querySelectorAll('.recipe-card').forEach(card => {
            card.addEventListener('click', function() {
                const recipeId = this.getAttribute('data-recipe-id');
                loadRecipeDetails(recipeId);
                editButton.style.display = isAdmin ? 'block' : 'none';
                recipeModal.show();
            });
        });
    }
    
    function loadRecipeDetails(id) {
        // Construct the URL to fetch a single recipe by its ID
        const recipeDetailUrl = `https://www.themealdb.com/api/json/v1/1/lookup.php?i=${id}`;
    
        fetch(recipeDetailUrl)
            .then(response => response.json())
            .then(data => {
                // Assuming the API returns an array and we're interested in the first item
                const meal = data.meals[0];
    
                // Extracting ingredients and measures dynamically
                const ingredients = [];
                for (let i = 1; i <= 20; i++) {
                    const ingredient = meal[`strIngredient${i}`];
                    const measure = meal[`strMeasure${i}`];
                    if (ingredient && measure && ingredient.trim() !== '' && measure.trim() !== '') {
                        ingredients.push(`${ingredient}: ${measure}`);
                    }
                }
    
                // Preparing the recipe details
                const recipeDetails = {
                    title: meal.strMeal,
                    instructions: meal.strInstructions,
                    imageUrl: meal.strMealThumb,
                    ingredients: ingredients // This is now an array of strings
                };
    
                // Updating the modal content
                modalTitle.textContent = recipeDetails.title;
                modalBody.innerHTML = `
                    <img src="${recipeDetails.imageUrl}" class="img-fluid mb-2" alt="${recipeDetails.title}">
                    <h5>Ingredients</h5>
                    <ul>
                        ${recipeDetails.ingredients.map(ingredient => `<li>${ingredient}</li>`).join('')}
                    </ul>
                    <h5>Instructions</h5>
                    <p>${recipeDetails.instructions}</p>
                `;

            })
            .catch(error => {
                console.error('Error loading recipe details:', error);
                modalBody.innerHTML = '<p>Error loading recipe details. Please try again later.</p>';
            });
    }    

    buyButton.addEventListener('click', function() {
        // Get all list items in the modal which contain ingredients
        const ingredientListItems = document.querySelectorAll('.modal-body ul li');
        const ingredients = Array.from(ingredientListItems).map(li => {
            const parts = li.textContent.split(':');
            return {
                ingredient: parts[0].trim(),
                measure: parts[1].trim()
            };
        });
    
        // Store in localStorage
        localStorage.setItem('selectedRecipeIngredients', JSON.stringify(ingredients));
    
        alert('Ingredients for the recipe have been added to your cart.');
        recipeModal.hide();
        window.location.href = './cart.html';  // Use the correct relative or absolute URL

    });
    

    if (isAdmin) {
        editButton.addEventListener('click', function() {
            // Implement editing functionality
            console.log('Edit process for the recipe');
        });
    }

    
    function fetchRecipes(letter) {
        const apiUrl = `https://www.themealdb.com/api/json/v1/1/search.php?f=${letter}`;
        return fetch(apiUrl)
            .then(response => response.json())
            .then(data => {
                if (data.meals) {
                    const recipes = data.meals.map(meal => ({
                        id: meal.idMeal,
                        name: meal.strMeal,
                        description: meal.strInstructions.substring(0, 100) + '...',
                        imageUrl: meal.strMealThumb,
                        // Other mappings...
                    }));
                    allLoadedRecipes = allLoadedRecipes.concat(recipes); // Accumulate recipes in the global list
                    return recipes; // Return fetched recipes
                } else {
                    return [];
                }
            })
            .catch(error => {
                console.error(`Error fetching recipes for letter ${letter}:`, error);
                return [];
            });
    }
    
    const searchByNameBtn = document.getElementById('searchByName');
    const listByLetterBtn = document.getElementById('listByLetter');
    const randomMealBtn = document.getElementById('randomMeal');
    const listCategoriesBtn = document.getElementById('listCategories');

    // Event handlers for buttons
    searchByNameBtn.addEventListener('click', () => searchMealByName(prompt("Enter meal name:")));
    listByLetterBtn.addEventListener('click', () => listMealsByFirstLetter(prompt("Enter first letter (A-Z):")));
    randomMealBtn.addEventListener('click', fetchRandomMeal);
    listCategoriesBtn.addEventListener('click', listAllCategories);

    function searchMealByName(name) {
        const apiUrl = `https://www.themealdb.com/api/json/v1/1/search.php?s=${name}`;
        return fetch(apiUrl)
            .then(response => response.json())
            .then(data => {
                if (data.meals) {
                    const recipes = data.meals.map(meal => ({
                        id: meal.idMeal,
                        name: meal.strMeal,
                        description: meal.strInstructions.substring(0, 100) + '...',
                        imageUrl: meal.strMealThumb
                    }));
                    allLoadedRecipes = allLoadedRecipes.concat(recipes);
                    displayRecipes(recipes); // Directly display recipes
                    return recipes;
                } else {
                    displayRecipes([]); // Update UI to show no recipes found
                    return [];
                }
            })
            .catch(error => {
                console.error(`Error fetching meals by name '${name}':`, error);
                return [];
            });
    }

    function listMealsByFirstLetter(letter) {
        const apiUrl = `https://www.themealdb.com/api/json/v1/1/search.php?f=${letter}`;
        return fetch(apiUrl)
            .then(response => response.json())
            .then(data => {
                if (data.meals) {
                    const recipes = data.meals.map(meal => ({
                        id: meal.idMeal,
                        name: meal.strMeal,
                        description: meal.strInstructions.substring(0, 100) + '...',
                        imageUrl: meal.strMealThumb
                    }));
                    allLoadedRecipes = allLoadedRecipes.concat(recipes);
                    displayRecipes(recipes);
                    return recipes;
                } else {
                    displayRecipes([]);
                    return [];
                }
            })
            .catch(error => {
                console.error(`Error fetching meals by first letter '${letter}':`, error);
                return [];
            });
    }

    function fetchRandomMeal() {
        const apiUrl = 'https://www.themealdb.com/api/json/v1/1/random.php';
        return fetch(apiUrl)
            .then(response => response.json())
            .then(data => {
                if (data.meals) {
                    const recipes = data.meals.map(meal => ({
                        id: meal.idMeal,
                        name: meal.strMeal,
                        description: meal.strInstructions.substring(0, 100) + '...',
                        imageUrl: meal.strMealThumb
                    }));
                    allLoadedRecipes = allLoadedRecipes.concat(recipes);
                    displayRecipes(recipes);
                    return recipes;
                } else {
                    displayRecipes([]);
                    return [];
                }
            })
            .catch(error => {
                console.error('Error fetching a random meal:', error);
                return [];
            });
    }

    function listAllCategories() {
        const apiUrl = 'https://www.themealdb.com/api/json/v1/1/categories.php';
        fetch(apiUrl)
            .then(response => response.json())
            .then(data => {
                const categories = data.categories.map(cat => `
                    <button class="category-btn btn btn-info m-2" onclick="filterByCategory('${cat.strCategory}')">${cat.strCategory}</button>
                `);
                const categoriesContainer = document.createElement('div');
                categoriesContainer.innerHTML = categories.join('');
                recipesContainer.insertBefore(categoriesContainer, recipesContainer.firstChild);
            })
            .catch(error => {
                console.error('Failed to list categories:', error);
                recipesContainer.innerHTML = '<p>Error loading categories. Please try again later.</p>';
            });
    }

    window.filterByCategory = function(category) {
        const apiUrl = `https://www.themealdb.com/api/json/v1/1/filter.php?c=${category}`;
        fetch(apiUrl)
            .then(response => response.json())
            .then(data => {
                const recipes = data.meals.map(meal => ({
                    id: meal.idMeal,
                    name: meal.strMeal,
                    imageUrl: meal.strMealThumb,
                    description: '' // Category filter often doesn't include descriptions
                }));
                displayRecipes(recipes);
            })
            .catch(error => {
                console.error(`Error fetching meals by category '${category}':`, error);
                recipesContainer.innerHTML = '<p>No recipes found for this category.</p>';
            });
    }


    function fetchRecipesByLetter(letter) {
        const apiUrl = `https://www.themealdb.com/api/json/v1/1/search.php?f=${letter}`;
        return fetch(apiUrl)
            .then(response => response.json())
            .then(data => {
                if (data.meals) {
                    return data.meals;
                } else {
                    return []; // Return an empty array if no meals are found for this letter
                }
            })
            .catch(error => {
                console.error('Error fetching recipes:', error);
                return []; // Return an empty array in case of an error
            });
    }
    
    async function fetchAllRecipes() {
        const letters = 'abcdefghijklmnopqrstuvwxyz'.split('');
        let allRecipes = [];
    
        for (let letter of letters) {
            const recipesForLetter = await fetchRecipes(letter);
            allRecipes = allRecipes.concat(recipesForLetter);
        }
        displayRecipes(allLoadedRecipes); // Display all accumulated recipes

    }
    
    //fetchAllRecipes();
});

function addToCart(meal) {
    const cartKey = 'cart';
    let cart = JSON.parse(localStorage.getItem(cartKey)) || [];

    for (let i = 1; i <= 20; i++) {
        const ingredientKey = `strIngredient${i}`;
        const measureKey = `strMeasure${i}`;
        const name = meal[ingredientKey];
        const quantity = meal[measureKey];

        if (!name || !quantity) break; // Stop if there are no more ingredients

        const existingItem = cart.find(item => item.name === name);
        if (existingItem) {
            existingItem.quantity += ` + ${quantity}`; // Append quantity for clarity
        } else {
            cart.push({ name, quantity });
        }
    }

    localStorage.setItem(cartKey, JSON.stringify(cart));
    alert('Ingredients added to your cart.');
}



