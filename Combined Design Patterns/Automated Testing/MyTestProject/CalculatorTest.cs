using Microsoft.VisualStudio.TestTools.UnitTesting;
//Unit Tests (Base of the Pyramid)
//Unit tests are quick to execute and test
// the smallest units of functionality in isolation,
// typically methods and functions of classes.

[TestClass]
public class CalculatorTests
{
    [TestMethod]
    public void Should_AddTwoNumbers_Correctly()
    {
        // Arrange
        var calculator = new Calculator();
        int a = 5;
        int b = 3;

        // Act
        int result = calculator.Add(a, b);

        // Assert
        Assert.AreEqual(8, result);
    }

    private class Calculator
    {
        public int Add(int a, int b)
        {
            return a + b;
        }
    }
}
