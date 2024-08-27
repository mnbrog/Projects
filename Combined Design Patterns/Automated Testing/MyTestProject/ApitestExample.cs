[TestClass]
public class ApiTestExample
{
    [TestMethod]
    public async Task TestApiEndpoint()
    {
        // Arrange
        HttpClient client = new HttpClient();
        string url = "https://api.example.com/data";

        // Act
        HttpResponseMessage response = await client.GetAsync(url);

        // Assert
        Assert.IsTrue(response.IsSuccessStatusCode, "API did not return a success status code.");
    }
}
