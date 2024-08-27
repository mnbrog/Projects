using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace OOP
{
    public class LeadTa : TA
    {
        public void Grade(){
            System.Console.WriteLine("Grade");
        }
        public override void sayHello(){
            //sayHello();
            System.Console.WriteLine("LeadTa");
        }
    }
}