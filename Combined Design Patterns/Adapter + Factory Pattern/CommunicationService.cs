using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Adapter___Factory_Pattern
{
   public class CommunicationService
{
    public void Communicate(string adapterType, string message)
    {
        var adapter = AdapterFactory.GetAdapter(adapterType);
        adapter.Send(message);
    }
}}