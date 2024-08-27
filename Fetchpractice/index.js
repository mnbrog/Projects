async function handleOnLoad() {
    populateTable();
}

async function populateTable() {
    let uniData = await getData();
    console.log(uniData);
    let html = `<table>
    <tr>
    <th>University Name</th>
    <th>Website</th>
    </tr>`;
    
    uniData.forEach(function(university) {
        html += `<tr>
        <td>${university.name}</td>
        <td><a href="${university.web_pages[0]}" target="_blank">${university.web_pages[0]}</a></td>
        </tr>`;
    });
    
    html += `</table>`;
    document.getElementById("app").innerHTML = html;
}

async function getData() {
    const url = 'http://universities.hipolabs.com/search?country=United+States';
    const response = await fetch(url);
    const data = await response.json();
    return data;
}
