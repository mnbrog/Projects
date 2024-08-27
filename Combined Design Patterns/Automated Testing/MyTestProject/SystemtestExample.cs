[TestClass]
public class SystemTestExample
{
    [TestMethod]
    public void TestEntireApplicationWorkflow()
    {
        // Arrange
        ApplicationWorkflow workflow = new ApplicationWorkflow();

        // Act
        bool success = workflow.RunCompleteWorkflow();

        // Assert
        Assert.IsTrue(success, "The complete application workflow did not run successfully.");
    }
}
