let url = 'https://api.imgflip.com/get_memes';
let bookdata = [];

async function handleOnLoad() {
    await getData();
    await populateTable(); 
}

async function populateTable() {
    console.log(bookdata);
    let html = `<table>
        <tr>
            <th>ID</th>
            <th>Name</th>
            <th>Cover Art</th>
        </tr>`;

    bookdata.forEach(function(book) {
        html += `<tr>
            <td>${book.id}</td>
            <td>${book.name}</td>
            <td><img src="${book.url}" alt="${book.name}" style="width:auto;height:100px;"></td>
        </tr>`;
    });

    html += `</table>`;
    document.getElementById("app").innerHTML = html;
}

async function getData() {
    let response = await fetch(url);
    let data = await response.json();
    if (data.success) { 
        bookdata = data.data.memes; 
    }
    console.log(bookdata);
}

document.addEventListener('DOMContentLoaded', handleOnLoad); 