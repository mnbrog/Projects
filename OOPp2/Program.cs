// See https://aka.ms/new-console-template for more information
using OOPp2;

Person p = new Person(){Name="john"};
Cat myCat = new Cat(){Name="Cat"};

List<ISayHello> people = new List<ISayHello>();
people.Add(p);
people.Add(myCat);

foreach (ISayHello person in people)
{
    person.SayHello();
}

foreach (ISayHello person in people){

    person.GetName();
}