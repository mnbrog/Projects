using System;
using Adapter;
public class Program
{
    // Entry point of the application
    public static void Main(string[] args)
    {
        // Create an instance of Adaptee that we need to use in our system.
        Adaptee adaptee = new Adaptee();
        
        // Create an instance of Adapter that wraps the adaptee, making it compatible with ITarget interface.
        ITarget target = new Adapt(adaptee);
        
        // The client code can now call the Request method on the target as if it was working with a standard interface.
        target.Request();
    }
}
