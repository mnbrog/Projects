public class CommunicationService
{
    public void Communicate(string adapterType, string message)
    {
        var adapter = AdapterFactory.GetAdapter(adapterType);
        adapter.Send(message);
    }
}