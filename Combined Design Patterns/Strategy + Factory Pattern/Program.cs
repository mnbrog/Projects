using System;
using Strategy___Factory_Pattern;


public class Program
{
    // Entry point of the application
    public static void Main(string[] args)
    {
        // Prompt user for the type of strategy to use
        Console.WriteLine("Enter Strategy Type (A/B):");
        string strategyType = Console.ReadLine().ToUpper();

        // Use the factory to get the appropriate strategy based on user input
        IStrategy strategy = StrategyFactory.GetStrategy(strategyType);

        // Set up the context with the chosen strategy
        Context context = new Context(strategy);

        // Execute the strategy
        context.ExecuteStrategy();
    }
}
