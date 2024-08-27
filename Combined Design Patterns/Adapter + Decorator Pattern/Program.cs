using Adapter___Decorator_Pattern;
public class Program
{
    public static void Main()
    {
        // Original legacy processor
        var legacyProcessor = new LegacyDataProcessor();

        // Adapter to fit new interface
        var adapter = new DataProcessorAdapter(legacyProcessor);

        // Add logging via decorator
        var logger = new LoggingDecorator(adapter);

        // Add validation via another decorator
        var validator = new ValidationDecorator(logger);
        Console.WriteLine("Enter Data:");
        string read =Console.ReadLine();
        // Process data
        validator.ProcessData(read);
    }
}
