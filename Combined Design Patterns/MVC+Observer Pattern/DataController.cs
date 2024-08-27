using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MVC_Observer_Pattern
{
    public class DataController
{
   private DataModel model;

    public DataController(DataModel model)
    {
        this.model = model;
    }

    public void SetValue(int newValue)
    {
        model.Value = newValue;
    }

    public void IncreaseValue()
    {
        model.Increment();
    }

    public void DecreaseValue()
    {
        model.Decrement();
    }
}
}