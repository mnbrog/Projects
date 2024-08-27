document.addEventListener('DOMContentLoaded', function() {
    const cartItemsContainer = document.getElementById('cartItems');
    const storeSelect = document.getElementById('storeSelect');

    function displayCartItems() {
        const cartItems = JSON.parse(localStorage.getItem('selectedRecipeIngredients')) || [];
        if (cartItems.length === 0) {
            cartItemsContainer.innerHTML = '<p class="text-center">Your cart is empty.</p>';
            return;
        }

        cartItemsContainer.innerHTML = cartItems.map((item, index) => `
            <div class="list-group-item list-group-item-action flex-column align-items-start" data-index="${index}">
                <div class="d-flex w-100 justify-content-between">
                    <div>
                        <h5 class="mb-1">${item.ingredient}</h5>
                        <small>Quantity: ${item.measure}</small>
                    </div>
                    <div class="button-group">
                        <button class="btn btn-primary btn-sm edit-btn" data-index="${index}">Edit</button>
                        <button class="btn btn-danger btn-sm delete-btn" data-index="${index}">Delete</button>
                        <a href="${storeSelect.value}${encodeURIComponent(item.ingredient)}" target="_blank" class="btn btn-success btn-sm buy-btn">Buy</a>
                    </div>
                </div>
            </div>
        `).join('');

        attachEventListeners();
    }

    function attachEventListeners() {
        document.querySelectorAll('.edit-btn, .delete-btn').forEach(button => {
            button.addEventListener('click', function() {
                const index = this.getAttribute('data-index');
                if (this.classList.contains('edit-btn')) {
                    editItem(index);
                } else {
                    deleteItem(index);
                }
            });
        });

        // Refresh items when store selection changes
        storeSelect.addEventListener('change', displayCartItems);
    }


    function attachEventListeners() {
        document.querySelectorAll('.edit-btn').forEach(button => {
            button.addEventListener('click', function() {
                const index = this.getAttribute('data-index');
                editItem(index);
            });
        });

        document.querySelectorAll('.delete-btn').forEach(button => {
            button.addEventListener('click', function() {
                const index = this.getAttribute('data-index');
                deleteItem(index);
            });
        });
    }

    function editItem(index) {
        const cartItems = JSON.parse(localStorage.getItem('selectedRecipeIngredients'));
        const item = cartItems[index];
        const newMeasure = prompt("Edit the quantity", item.measure);
        if (newMeasure !== null) {
            cartItems[index].measure = newMeasure;
            localStorage.setItem('selectedRecipeIngredients', JSON.stringify(cartItems));
            displayCartItems();
        }
    }

    function deleteItem(index) {
        const cartItems = JSON.parse(localStorage.getItem('selectedRecipeIngredients'));
        cartItems.splice(index, 1);
        localStorage.setItem('selectedRecipeIngredients', JSON.stringify(cartItems));
        displayCartItems();
    }

    displayCartItems();
});


    function calculateTotal() {
        const total = cartItems.reduce((sum, item) => sum + (item.price * item.quantity), 0);
        cartContainer.innerHTML += `<h3>Total: $${total.toFixed(2)}</h3>`;
    }

    function attachEventListeners() {
        document.querySelectorAll('.change-qty').forEach(button => {
            button.addEventListener('click', function() {
                const id = parseInt(this.closest('.card').getAttribute('data-id'));
                const change = parseInt(this.getAttribute('data-change'));
                updateItemQuantity(id, change);
            });
        });

        document.querySelectorAll('.remove-item').forEach(button => {
            button.addEventListener('click', function() {
                const id = parseInt(this.closest('.card').getAttribute('data-id'));
                removeItemFromCart(id);
            });
        });
    }

    //displayCartItems();

function initMap() {
	var myMapCenter = {lat: 33.215775, lng: -87.538261};

	// Create a map object and specify the DOM element for display.
	var map = new google.maps.Map(document.getElementById('map'), {
		center: myMapCenter,
		zoom: 14
	});


	function markStore(storeInfo){

		// Create a marker and set its position.
		var marker = new google.maps.Marker({
			map: map,
			position: storeInfo.location,
			title: storeInfo.name
		});

		// show store info when marker is clicked
		marker.addListener('click', function(){
			showStoreInfo(storeInfo);
		});
	}

	// show store info in text box
	function showStoreInfo(storeInfo){
		var info_div = document.getElementById('info_div');
		info_div.innerHTML = 'Store name: '
			+ storeInfo.name
			+ '<br>Hours: ' + storeInfo.hours;
	}

	var stores = [
		{
			name: 'Store 1',
			location: {lat: 40.785091, lng: -73.968285},
			hours: '8AM to 10PM'
		},
		{
			name: 'Store 2',
			location: {lat: 40.790091, lng: -73.968285},
			hours: '9AM to 9PM'
		}
	];

	stores.forEach(function(store){
		markStore(store);
	});

}