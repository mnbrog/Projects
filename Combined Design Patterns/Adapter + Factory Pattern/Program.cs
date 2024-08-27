using Adapter___Factory_Pattern;

    public class Program
    {
        public static void Main()
        {
            // Arrange
            var communicationService = new CommunicationService();
            var f = "FTP";
            var h = "HTTP";
            var message = "Hello World!";
        // Act
        communicationService.Communicate(h, message);

        // Assert
        // Verify that the correct adapter was used to communicate the message.
    }
}