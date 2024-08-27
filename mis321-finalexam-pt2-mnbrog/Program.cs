using System;
using mis321_finalexam_pt2_mnbrog;

public class Program
{
    // Entry point of the application
    public static void Main(string[] args)
    {
        // Prompt user for the type of strategy to use
        Console.WriteLine("Enter Strategy Type (A/B/C) (Black Coffee/Espresso/Pastry):");
        string strategyType = Console.ReadLine().ToUpper();

        // Use the factory to get the appropriate strategy based on user input
        IBrew strategy = Coffeefactory.GetStrategy(strategyType);

        // Set up the context with the chosen strategy
        Ctext context = new Ctext(strategy);

        // Execute the strategy
        context.ExecuteStrategy();
    }
}
