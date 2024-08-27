using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api
{
    public class ChicageStyle: Pizza
    {
        public ChicageStyle(){
            discription="Chicago Style";
        }

        public override void prepare()
        {
            Console.WriteLine("Preparing " + discription);
        }

        public override double cost()
                {
                    double cost=0.0;
                    switch(size){
                    case"small": cost+=10.5;
                    case"medium": cost+=10.5;
                    case"large": cost+=10.5;
                    case"XL": cost+=10.5;
                    break;                    
                    }
            return "13.5";}
    
    }

}