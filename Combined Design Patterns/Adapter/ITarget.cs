using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Adapter
{
    // The 'Target' interface represents the interface that our application expects to work with.

    public interface ITarget
{
    void Request();
}
}