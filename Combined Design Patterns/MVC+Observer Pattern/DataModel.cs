using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MVC_Observer_Pattern
{
    public class DataModel
{
    private int value;
    public int Value
    {
        get { return value; }
        set { this.value = value; NotifyObservers(); }
    }

    private List<IModelObserver> observers = new List<IModelObserver>();

    public void Attach(IModelObserver observer)
    {
        observers.Add(observer);
    }

    private void NotifyObservers()
    {
        foreach (var observer in observers)
        {
            observer.Update(this);
        }
    }

     public void Increment()
    {
        Value++;
    }

    public void Decrement()
    {
        Value--;
    }
}
}