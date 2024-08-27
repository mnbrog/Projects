[TestClass]
public class UnitTestExample
{
    [TestMethod]
    public void TestAddFunction()
    {
        // Arrange
        Calculator calculator = new Calculator();

        // Act
        int result = calculator.Add(1, 2);

        // Assert
        Assert.AreEqual(3, result, "The add function did not return the expected result.");
    }
}

public class Calculator
{
    public int Add(int numberOne, int numberTwo)
    {
        return numberOne + numberTwo;
    }
}
