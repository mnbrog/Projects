using mis321_exam2_pt2;

//only one change should be executed on this file

IGetStats statsObj = new StatsAdapter();
Console.WriteLine("This weeks QB stats are below!");
List<QBStats> qbStats = statsObj.GetQBStats();
foreach(QBStats qb in qbStats){
    Console.WriteLine(qb.ToString());
}

Console.WriteLine("\nThis weeks WR stats are below!");
List<WRStats> wrStats = statsObj.GetWRStats();
foreach(WRStats wr in wrStats){
    Console.WriteLine(wr.ToString());
}

Console.WriteLine("\nThis weeks RB stats are below!");
List<RBStats> rbStats = statsObj.GetRBStats();
foreach(RBStats rb in rbStats){
    Console.WriteLine(rb.ToString());
}
