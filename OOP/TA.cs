using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace OOP
{
    public class TA : Person
    {
        public string Class { get; set; }
        public override void sayHello(){
           // sayHello();
            Console.WriteLine("Dont Bther em");
        }
    }
}