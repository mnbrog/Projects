// See https://aka.ms/new-console-template for more information
using System;
using CompounddesignPatterns;
class Program
{
    static void Main(string[] args)
    {
        Simulate();
    }

    public static void Simulate()
    {
        IQuackable mallardDuck = new MallerDuck();
        IQuackable redHeadDuck = new RedHeadDuck();
        IQuackable duckCall = new DuckCall();
        IQuackable rubberDuck = new RubberDuck();

        Console.WriteLine("\nDuck simulator");

        Simulate(mallardDuck);
        Simulate(redHeadDuck);
        Simulate(duckCall);
        Simulate(rubberDuck);
    }

    public static void Simulate(IQuackable duck)
    {
        duck.Quack();
    }
}