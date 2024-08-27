using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace OOP
{
    public class Person : ISayHello
    {
        public string Name { get; set; }
        public int Age { get; set; }
        public virtual void sayHello(){//virtuall means it can pverride
            Console.WriteLine("Hello");
        }
    }
}