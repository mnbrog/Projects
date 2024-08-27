using System;
using MVC_Observer_Pattern;  // Include the namespace that contains your MVC and Observer Pattern classes

// The main class that orchestrates the MVC and Observer patterns
public class Program
{
    // Entry point of the application
    public static void Main()
    {
        // Create an instance of the DataModel which holds and manages the application data
        var model = new DataModel();
        // Create two views, each will display updates from the model in different formats
        var consoleView = new ConsoleView();           // Simpler, direct output view
        var DconsoleView = new DetailedConsoleView();   // More detailed output view

        // Register both views as observers of the model to receive updates
        model.Attach(consoleView);
        model.Attach(DconsoleView);

        // Create a controller to manage user input and manipulate the model
        var controller = new DataController(model);

        // Boolean flag to keep the application running in a loop
        bool running = true;
        while (running)
        {
            // Prompt user for a command
            Console.WriteLine("\nEnter command (set/inc/dec/exit):");
            string command = Console.ReadLine();  // Read user input from the console

            // Handle commands using a switch statement
            switch (command)
            {
                case "set":  // Set a new value to the model
                    Console.WriteLine("Enter a new value:");  // Ask for the value
                    int newValue = int.Parse(Console.ReadLine());  // Parse the input to an integer
                    controller.SetValue(newValue);  // Update the model through the controller
                    break;
                case "inc":  // Increment the model's value
                    controller.IncreaseValue();
                    break;
                case "dec":  // Decrement the model's value
                    controller.DecreaseValue();
                    break;
                case "exit":  // Exit the program
                    running = false;  // Set running to false to terminate the loop
                    break;
                default:  // Handle undefined commands
                    Console.WriteLine("Invalid command.");
                    break;
            }
        }
    }
}
