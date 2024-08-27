using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MVC
{

public class MockCustomerRepository : ICustomerRepository
{
    private List<Customer> customers = new List<Customer>();

    public MockCustomerRepository()
    {
        // Initialize with some dummy data
        customers.Add(new Customer { Id = 1, Name = "Alice Johnson", Email = "alice@example.com" });
        customers.Add(new Customer { Id = 2, Name = "Bob Smith", Email = "bob@example.com" });
    }

    public Task<List<Customer>> GetAllCustomersAsync()
    {
        // Simulate asynchronous operation
        return Task.FromResult(new List<Customer>(customers));
    }

    public Task<Customer> GetCustomerByIdAsync(int id)
    {
        // Simulate asynchronous operation and find the customer by ID
        var customer = customers.Find(c => c.Id == id);
        return Task.FromResult(customer);
    }

    public Task AddCustomerAsync(Customer customer)
    {
        // Simulate generating an ID for a new customer
        customer.Id = customers.Count + 1;
        customers.Add(customer);
        return Task.CompletedTask;  // No actual return value needed, just indicate completion
    }

    
}

}