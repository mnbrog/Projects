using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MVC_Observer_Pattern
{
    public class ConsoleView: IModelObserver
{
     public void Update(DataModel model)
    {
        Console.WriteLine($"View updated - New Value: {model.Value}");
    }
}}