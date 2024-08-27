// See https://aka.ms/new-console-template for more information
using OOP;
Person p = new Person();
p.Name="Mike";
p.Age=22;
TA t = new TA(){ Name="Mik", Age=22 };

Console.WriteLine(p.Name);
Console.WriteLine(p.Age);
Console.WriteLine(t.Name);
Console.WriteLine(t.Age);
t.Class="Mis";
Console.WriteLine(t.Class);
LeadTa leadTa = new LeadTa(){Name="Mike",Age=22,Class="mis"};
leadTa.ToString();
List<Person> persons = new List<Person>();
persons.Add(p);
persons.Add(t);
persons.Add(leadTa);
persons[0].ToString();
foreach (Person person in persons){
    person.sayHello();
}