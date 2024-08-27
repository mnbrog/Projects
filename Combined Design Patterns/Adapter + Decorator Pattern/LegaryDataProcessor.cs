using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Adapter___Decorator_Pattern
{
    public class LegacyDataProcessor
{
    public void PerformDataProcessing(string data)
    {
        Console.WriteLine($"LegacyDataProcessor: Processing {data}");
    }
}

}