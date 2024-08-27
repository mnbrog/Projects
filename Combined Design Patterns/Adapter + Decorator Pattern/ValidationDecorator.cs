using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Adapter___Decorator_Pattern
{
    public class ValidationDecorator : IDataProcessor
    {
        private IDataProcessor wrappedProcessor;

        public ValidationDecorator(IDataProcessor processor)
        {
            wrappedProcessor = processor;
        }

        public void ProcessData(string data)
        {
            if (string.IsNullOrEmpty(data))
            {
                Console.WriteLine("Validation Decorator: Data is invalid.");
            }
            else
            {
                wrappedProcessor.ProcessData(data);
            }
        }
    }
}