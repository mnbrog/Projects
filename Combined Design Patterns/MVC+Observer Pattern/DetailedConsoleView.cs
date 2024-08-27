using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MVC_Observer_Pattern
{
    public class DetailedConsoleView : IModelObserver
{
    public void Update(DataModel model)
    {
        Console.WriteLine($"Detailed View: The current model value is now {model.Value}.");
    }
}
}