using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Strategy___Factory_Pattern
{
    // Context class to use the strategy
public class Context
{
    private IStrategy strategy;

    public Context(IStrategy strategy)
    {
        this.strategy = strategy;
    }

    public void SetStrategy(IStrategy newStrategy)
    {
        strategy = newStrategy;
    }

    public void ExecuteStrategy()
    {
        strategy.Execute();
    }
}
}