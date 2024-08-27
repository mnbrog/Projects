using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MVC_Observer_Pattern
{
    public interface IModelObserver
{
    void Update(DataModel model);
}
}