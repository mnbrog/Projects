[TestClass]
public class IntegrationTestExample
{
    [TestMethod]
    public void TestDatabaseConnection()
    {
        // Arrange
        DatabaseConnector dbConnector = new DatabaseConnector(connectionString: "YourConnectionString");

        // Act & Assert
        Assert.IsTrue(dbConnector.Connect(), "Unable to connect to the database.");
    }
}
