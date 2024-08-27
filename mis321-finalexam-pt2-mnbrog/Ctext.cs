using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace mis321_finalexam_pt2_mnbrog
{
    using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
public class Ctext
{
    private IBrew strategy;

    public Ctext(IBrew strategy)
    {
        this.strategy = strategy;
    }

    public void SetStrategy(IBrew newStrategy)
    {
        strategy = newStrategy;
    }

    public void ExecuteStrategy()
    {
        strategy.Brew();
    }
}
}
