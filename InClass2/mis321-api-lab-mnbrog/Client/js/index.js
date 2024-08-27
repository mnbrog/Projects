let url = 'http://openlibrary.org/subjects/%7Bfantasy%7D.json?limit=10';
let bookdata =[]


async function handleOnLoad() {
getData()
populateTable()
}

async function populateTable() {
    let uniData = await getData();
    console.log(uniData);
    let html = `<table>
    <tr>
    <th>Title</th>
    <th>Author</th>
    <th>Publish Date</th>
    <th>Cover Art</th>
    </tr>`;
    
    bookdata.forEach(function(book) {
        html += `<tr>
        <td>${book.title}</td>
        <td>${book.authors[0].name}</td>
        <td>${book.first_publish_year}</td>
        <td><img src="https://covers.openlibrary.org/b/id/${book.cover_id}-M.jpg
        " alt="Book Cover" ></img></th>
        </tr>`;
    });
    
    html += `</table>`;
    document.getElementById("app").innerHTML = html;
}

async function getData() {
    let response = await fetch(url);
    let data = await response.json();
    bookdata = data.works
    console.log(bookdata)
}
