using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace mis321_finalexam_pt2_mnbrog
{
    public class Coffee : IBrew
    {
        public int Brew(){
            return 45;
        }
    }
}