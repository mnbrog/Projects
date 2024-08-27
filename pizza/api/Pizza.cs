using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api
{
    public class Pizza
    {
        public string size;
        public string discription;
        public Pizza(){
discription="UN KNOWN PRODUCT"
        }
        public Pizza(string size, string discription)
        {
            this.size = size;
            this.discription = discription;
        }
        public virtual getsize { return this.size; }
        public virtual getDiscription { return this.discription; }

        public abstract double cost(){

        }
    }
}