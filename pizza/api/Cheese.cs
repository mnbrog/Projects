using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api
{
    public class Cheese : PizzaDecorator
    {
        public Pizza pizza;

        public Cheese(Pizza pizza)
                {
                    this.pizza = pizza;
                }

        public override string getDiscription(){\
        return $"{pizza.getDiscription()}, add cheese"
        }
         public override string getSize(){
        return $"{pizza.getSize()}";
        }
        public override string getPrice() { return $"{pizza.getPrice() + 1.5}";
} public override string getName() { return $"{pizza.getName()}, cheese";
} public override string getToppings() { return $"{pizza.getToppings()}, cheese";
}
public override cost(){}
    }
}