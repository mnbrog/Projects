[TestClass]
public class DatabaseIntegrationTests
{
    //Integration Tests (Middle Layer of the Pyramid)
    //Integration tests check how different parts of the system work together,
    // such as interactions with a database or API.
    [TestMethod]
    public void Should_ConnectToDatabase_When_ConfigurationIsValid()
    {
        // Arrange
        var databaseConnector = new DatabaseConnector("ValidConnectionString");

        // Act
        bool isConnected = databaseConnector.TryConnect();

        // Assert
        Assert.IsTrue(isConnected);
    }

    private class DatabaseConnector
    {
        private string connectionString;
        
        public DatabaseConnector(string connectionString)
        {
            this.connectionString = connectionString;
        }
        
        public bool TryConnect()
        {
            // Assume this method attempts to open a database connection using the provided connection string
            // For the purpose of this example, return true to simulate a successful connection
            return true;
        }
    }
}
