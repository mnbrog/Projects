using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace OOPp2
{
    public class Person : ISayHello
    {
        public string Name { get; set; }
        public int Age { get; set; }

        public void SayHello()
        {
            Console.WriteLine($"Hello, my name is {Name}");
        }

        public void getName(){
            Console.WriteLine($"Hello, my name is"{Name});

        }
    }
}