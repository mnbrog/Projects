let products = JSON.parse(localStorage.getItem('products')) || [];

function saveProducts() {
    localStorage.setItem('products', JSON.stringify(products));
}

function loadProducts() {
    let app = document.getElementById('app');
    let html = `
    <table>
        <tr>
            <th>Name</th>
            <th>Category</th>
            <th>Price</th>
            <th>Delete</th>
        </tr>
    `;
    products.forEach((product, index) => {
        if (!product.deleted) {
            html += `<tr>
                <td>${product.name}</td>
                <td>${product.category}</td>
                <td>${product.price}</td>
                <td><button onclick="deleteProduct('${product.id}')">Delete</button></td>
            </tr>`;
        }
    });
    html += `</table>`;
    app.innerHTML = html;
}

function addProduct(name, category, price) {
    products.push({
        id: crypto.randomUUID(),
        name,
        category,
        price: parseInt(price, 10),
        deleted: false
    });
    saveProducts();
    loadProducts();
}

function deleteProduct(id) {
    let product = products.find(product => product.id === id);
    if (product) product.deleted = true;
    saveProducts();
    loadProducts();
}

function sortProducts() {
    products.sort((a, b) => a.price - b.price);
    loadProducts();
}

window.onload = () => {
    loadProducts();
};
