using MVC;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
public class Program
{
public static async Task Main(string[] args)
{
    ICustomerRepository repository = new MockCustomerRepository(); // Assuming a mock repository implementation
    CustomerView view = new CustomerView();
    CustomerController controller = new CustomerController(repository, view);

    await controller.DisplayAllCustomersAsync();
    await controller.AddCustomerAsync("John Doe", "john@example.com");
}
}