namespace mis321_exam2_pt2
{
    public interface IGetStats
    {
        List<QBStats> GetQBStats();
        List<RBStats> GetRBStats();
        List<WRStats> GetWRStats();
    }
}