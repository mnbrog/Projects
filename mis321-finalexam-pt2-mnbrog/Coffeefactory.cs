using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace mis321_finalexam_pt2_mnbrog
{
    public class Coffeefactory
    {
        public static IBrew GetStrategy(string type)
    {
        // Determine which strategy to create based on the input type
        if (type == "A")
        {
            var c= new Coffee();
            Console.WriteLine($"Your coffee is being brewed and will be done in {c.Brew()} seconds");
            return c;
        }
        else if (type == "B")
        {
            var e= new Espresso();
            Console.WriteLine($"Your coffee is being brewed and will be done in {e.Brew()} seconds");
            return e;
        }
        else if (type == "C")
        {
            var p= new Pastry();
            Console.WriteLine($"The pastry has begun to bake and will be done in {p.Brew()} seconds");
            return p;
        }
        else
        {
            throw new ArgumentException("Invalid type");
        }
    }
    }
}