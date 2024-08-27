// let taName = 'Anne'
// console.log(taName)
// otherta ='carson'
// console.log(otherta)
// if(otherta=='carson'){
//     console.log('hey carson')
// }
// else{
//     console.log('must be anne')
// }

// var num =1
// if (num=='1'){//
// console.log('they match')
// }

// else{
// console.log('boo')
// }

// function addVariable(a= 20,b){
//     return a+b
// }

// console.log(addVariable(4,5))
let myBooks=[
    {title:'mty',
    author:' brogan',
    pages:657,
    publisher:'p0enguin'},
    {title:'ned',
    author:{firstName:'carl',
lastName:'Snaders'} ,
    pages:67,
    publisher:'p0enguin'}
]
let myBook ={
    title:'misty',
    author:'branson brogan',
    pages:657,
    publisher:'p0enguin'
}
myBooks.push(myBook)

console.log(myBook.author)
myBook.publisher='pooon'
console.log(myBook.publisher)
console.log(myBooks[0].author)

myBooks.forEach(function (book){
    console.log(book.author)
})
// myBooks.forEach((book)=>{
//     console.log(book.title)
// }) also works arrow is function
function handleOnLoad(){
    mybooks =JSON.parse(localStorage.getItem('myBooks'))
    console.log(myBooks)
    loadTable()
}
function loadTable(){
let app=document.getElementById('app')
let html=`
<table>
            <tr>
              <th>Title</th>
              <th>Author</th>
              <th>Pages</th>
            </tr>     
`
myBooks.forEach(function(book){
html += `<tr>
  <td>${book.title}</td>
  <td>${book.author}</td>
  <td>${book.pages}</td>
</tr>
`

})
html+=`</table>`
app.innerHTML=html}