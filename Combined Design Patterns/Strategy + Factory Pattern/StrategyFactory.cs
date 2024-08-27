using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Strategy___Factory_Pattern
{
    // Factory class to create strategy instances based on a given type
    public static class StrategyFactory
{
    public static IStrategy GetStrategy(string type)
    {
        // Determine which strategy to create based on the input type
        if (type == "A")
        {
            return new ConcreteStrategyA();
        }
        else if (type == "B")
        {
            return new ConcreteStrategyB();
        }
        else
        {
            throw new ArgumentException("Invalid strategy type");
        }
    }
}
}