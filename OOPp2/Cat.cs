using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace OOPp2
{
    public class Cat : ISayHello
    {
        public string Name { get; set; }
        public int Age { get; set; }

        public void SayHello()
        {
            Console.WriteLine($"Meow my name is {Name}");
        }

        public void getName(){
            System.Console.WriteLine({Name});

        }
    }
}