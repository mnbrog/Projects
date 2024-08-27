using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Adapter
{
   // The 'Adapt' class makes the Adaptee's interface compatible with the Target's interface.
public class Adapt : ITarget
{
    private Adaptee adaptee;

    public Adapt(Adaptee adaptee)
    {
        this.adaptee = adaptee;
    }

    // This method calls the specific request on the adaptee when the client expects a standard request.
    public void Request()
    {
        adaptee.SpecificRequest();
    }
}

}