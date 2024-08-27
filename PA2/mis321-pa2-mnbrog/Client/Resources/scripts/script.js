let currentOffset = 0;
const limit = 10; // Number of Pokémon to fetch per request

async function handleOnLoad() {
    document.getElementById("app").innerHTML = '<h1></h1><ul id="pokemonList"></ul><button id="loadMore" onclick="loadMorePokemon()">Load More</button>';
    await populatePokemonList();
}

async function populatePokemonList() {
    const data = await fetchPokemonList(currentOffset, limit);
    const pokemonList = document.getElementById("pokemonList");
    
    data.results.forEach(pokemon => {
        const listItem = document.createElement('li');
        listItem.innerHTML = `<button onclick="populatePokemonInfo('${pokemon.url}')">${pokemon.name}</button>`;
        pokemonList.appendChild(listItem);
    });

    currentOffset += limit; // Updates the offset for the next load
}

async function loadMorePokemon() {
    await populatePokemonList(); // Fetch and display Pokémon
}

async function populatePokemonInfo(pokemonUrl) {
    const data = await fetchPokemonDetails(pokemonUrl);
    let html = `<h1>${data.name}</h1>
        <img src="${data.sprites.front_default}" alt="${data.name} Sprite">
        <h2>Abilities</h2><ul>`;
        
    data.abilities.forEach(ability => {
        html += `<li>${ability.ability.name}</li>`;
    });
    
    html += '</ul><button onclick="handleOnLoad()">Back to list</button>';
    document.getElementById("app").innerHTML = html;
}

async function fetchPokemonList(offset, limit) {
    const response = await fetch(`https://pokeapi.co/api/v2/pokemon?offset=${offset}&limit=${limit}`);
    return response.json();
}

async function fetchPokemonDetails(pokemonUrl) {
    const response = await fetch(pokemonUrl);
    return response.json();
}

handleOnLoad();
