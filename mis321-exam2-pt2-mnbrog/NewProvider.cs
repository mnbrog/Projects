namespace mis321_exam2_pt2
{
    public class NewProvider
    {
        public List<OffensiveStats> GetOffensiveStats()
        {
            List<OffensiveStats> oStats = new List<OffensiveStats>();
            oStats.Add(new OffensiveStats(){ID="QB1", PassingYards = 175, RushingYards=22.5, PassingTDs=1, RushingTDs=0, Position = "QB"});

            oStats.Add(new OffensiveStats(){ID="QB2", PassingYards = 305.5, RushingYards=2.5, PassingTDs=3, RushingTDs=1, Position = "QB"});

            oStats.Add(new OffensiveStats(){ID="QB3", PassingYards = 205.5, RushingYards=12.5, PassingTDs=2, RushingTDs=1, Position = "QB"});

            oStats.Add(new OffensiveStats(){ID="RB1", ReceivingYards = 25, RushingYards=72.5, ReceivingTDs=1, RushingTDs=0, Position = "RB"});

            oStats.Add(new OffensiveStats(){ID="RB1", ReceivingYards = 25, RushingYards=172.5, ReceivingTDs=0, RushingTDs=1, Position = "RB"});

            oStats.Add(new OffensiveStats(){ID="RB1", ReceivingYards = 25, RushingYards=102.0, ReceivingTDs=1, RushingTDs=2, Position = "RB"});

            oStats.Add(new OffensiveStats(){ID="WR1", ReceivingYards = 72, RushingYards=5.25, ReceivingTDs=1, RushingTDs=0, Position = "WR"});

            oStats.Add(new OffensiveStats(){ID="WR1", ReceivingYards = 25, RushingYards=0, ReceivingTDs=0, RushingTDs=0, Position = "WR"});

            oStats.Add(new OffensiveStats(){ID="WR1", ReceivingYards = 125, RushingYards=12.0, ReceivingTDs=2, RushingTDs=0, Position = "WR"});
            
            return oStats;
        }
    }
}