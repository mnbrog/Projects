namespace mis321_exam2_pt2
{
    public class StatsAdapter : IGetStats
    {
        private NewProvider _newProvider;

        public StatsAdapter()
        {
            _newProvider = new NewProvider();
        }

        public List<QBStats> GetQBStats()
        {
            var allStats = _newProvider.GetOffensiveStats();
            List<QBStats> qbStats = new List<QBStats>();
            foreach (var stat in allStats)
            {
                if (stat.Position == "QB")
                {
                    qbStats.Add(new QBStats
                    {
                        ID = stat.ID,
                        PassingYards = stat.PassingYards,
                        RushingYards = stat.RushingYards,
                        PassingTDs = stat.PassingTDs,
                        RushingTDs = stat.RushingTDs
                    });
                }
            }
            return qbStats;
        }

        public List<RBStats> GetRBStats()
        {
            var allStats = _newProvider.GetOffensiveStats();
            List<RBStats> rbStats = new List<RBStats>();
            foreach (var stat in allStats)
            {
                if (stat.Position == "RB")
                {
                    rbStats.Add(new RBStats
                    {
                        ID = stat.ID,
                        ReceivingYards = stat.ReceivingYards,
                        RushingYards = stat.RushingYards,
                        ReceivingTDs = stat.ReceivingTDs,
                        RushingTDs = stat.RushingTDs
                    });
                }
            }
            return rbStats;
        }

        public List<WRStats> GetWRStats()
        {
            var allStats = _newProvider.GetOffensiveStats();
            List<WRStats> wrStats = new List<WRStats>();
            foreach (var stat in allStats)
            {
                if (stat.Position == "WR")
                {
                    wrStats.Add(new WRStats
                    {
                        ID = stat.ID,
                        ReceivingYards = stat.ReceivingYards,
                        RushingYards = stat.RushingYards,
                        ReceivingTDs = stat.ReceivingTDs,
                        RushingTDs = stat.RushingTDs
                    });
                }
            }
            return wrStats;
        }
    }
}
