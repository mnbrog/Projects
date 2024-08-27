using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Adapter___Decorator_Pattern
{
    public class LoggingDecorator : IDataProcessor
    {
        private IDataProcessor wrappedProcessor;

        public LoggingDecorator(IDataProcessor processor)
        {
            wrappedProcessor = processor;
        }

        public void ProcessData(string data)
        {
            Console.WriteLine($"LoggingDecorator: Before processing {data}");
            wrappedProcessor.ProcessData(data);
            Console.WriteLine("LoggingDecorator: After processing");
        }
    }

}