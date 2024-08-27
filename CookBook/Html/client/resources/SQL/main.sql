CREATE TABLE Recipes (
    Id INT PRIMARY KEY,
    Title NVARCHAR(100),
    Description TEXT,
    Instructions TEXT
);

CREATE TABLE Ingredients (
    Id INT PRIMARY KEY,
    Name NVARCHAR(100)
);

-- ... Other tables and relationships
-- Sample SQL query to fetch recipes with ingredients
SELECT R.Title, I.Name
FROM Recipes R
JOIN RecipeIngredients RI ON R.Id = RI.RecipeId
JOIN Ingredients I ON RI.IngredientId = I.Id;
