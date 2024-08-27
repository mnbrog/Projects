using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Adapter___Factory_Pattern
{
    public interface ICommunicationAdapter
    {
        void Send(string message);
    }

}