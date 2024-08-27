document.getElementById('signInForm').addEventListener('submit', function(event) {
    event.preventDefault();

    const email = document.getElementById('emailInput').value;
    const password = document.getElementById('passwordInput').value;
    
    // Here we just mock authentication for demonstration.
    if (email === "admin@email.com" && password === "password123") {
        localStorage.setItem('user', JSON.stringify({email: email, isAdmin: true}));
        alert('You are logged in as admin!');
        window.location.href = './recipes.html'; // Redirect to the home page or dashboard
    } else {
        alert('Invalid credentials!');
    }
});