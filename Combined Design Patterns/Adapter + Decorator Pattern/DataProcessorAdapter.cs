using Adapter___Decorator_Pattern;

public class DataProcessorAdapter : IDataProcessor
{
    private LegacyDataProcessor legacyProcessor;

    public DataProcessorAdapter(LegacyDataProcessor processor)
    {
        legacyProcessor = processor;
    }

    public void ProcessData(string data)
    {
        legacyProcessor.PerformDataProcessing(data);
    }
}
