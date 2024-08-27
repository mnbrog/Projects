namespace mis321_exam2_pt2
{
    public class WRStats
    {
        public string ID {get; set;}
        
        public double ReceivingYards {get; set;}
        public double RushingYards {get; set;}
        public int ReceivingTDs {get; set;}
        public int RushingTDs {get; set;}

        public override string ToString(){
            return ($"WR {ID}\tReceiving Yards\t{ReceivingYards}\tReceiving TDs\t{ReceivingTDs}\tRushingYards\t{RushingYards}\tRushing TDs\t{RushingTDs}");
        }
    }
}