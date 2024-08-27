using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MVC
{
    public class CustomerView
    {
        public void DisplayCustomer(Customer customer)
        {
            Console.WriteLine($"ID: {customer.Id}, Name: {customer.Name}, Email: {customer.Email}");
        }

        public void DisplayAllCustomers(List<Customer> customers)
        {
            foreach (var customer in customers)
            {
                DisplayCustomer(customer);
            }
        }

        public void DisplayError(string message)
        {
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine(message);
            Console.ResetColor();
        }
    }
}