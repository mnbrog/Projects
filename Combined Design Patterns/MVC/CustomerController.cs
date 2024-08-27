using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MVC
{
    public class CustomerController
{
    private readonly ICustomerRepository repository;
    private readonly CustomerView view;

    public CustomerController(ICustomerRepository repo, CustomerView view)
    {
        this.repository = repo;
        this.view = view;
    }

    public async Task DisplayAllCustomersAsync()
    {
        try
        {
            var customers = await repository.GetAllCustomersAsync();
            view.DisplayAllCustomers(customers);
        }
        catch (Exception ex)
        {
            view.DisplayError("Failed to retrieve customers: " + ex.Message);
        }
    }

    public async Task AddCustomerAsync(string name, string email)
    {
        try
        {
            var customer = new Customer { Name = name, Email = email };
            await repository.AddCustomerAsync(customer);
            view.DisplayCustomer(customer);
        }
        catch (Exception ex)
        {
            view.DisplayError("Failed to add customer: " + ex.Message);
        }
    }
}

}