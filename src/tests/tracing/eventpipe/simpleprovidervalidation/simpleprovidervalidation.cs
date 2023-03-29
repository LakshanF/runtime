// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.

using System;
using System.Diagnostics.Tracing;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Collections.Generic;
using Microsoft.Diagnostics.Tracing;
using Tracing.Tests.Common;
using Microsoft.Diagnostics.NETCore.Client;

namespace Tracing.Tests.SimpleProviderValidation
{
    public sealed class LaksDemoEventSource : EventSource
    {
        private LaksDemoEventSource() {}
        public static LaksDemoEventSource Log = new LaksDemoEventSource();
        public void MyEvent() { WriteEvent(1, "MyEvent"); }
    }

    public class ProviderValidation
    {
        public static int Main()
        {
            // This test validates that the rundown events are present
            // and that providers turned on that generate events are being written to
            // the stream.

            var providers = new List<EventPipeProvider>()
            {
                new EventPipeProvider("LaksDemoEventSource", EventLevel.Verbose),
                new EventPipeProvider("Microsoft-DotNETCore-SampleProfiler", EventLevel.Verbose),
                new EventPipeProvider("Microsoft-Windows-DotNETRuntime", EventLevel.Verbose, 1)
            };

            Console.WriteLine("Waiting 10 seconds to client to get the PID");
            Thread.Sleep(10*1000);

            var ret = IpcTraceTest.RunAndValidateEventCounts(_expectedEventCounts, _eventGeneratingAction, providers, 1024, enableRundownProvider:false);
            if (ret < 0)
                return ret;
            else
                return 100;
        }

        private static Dictionary<string, ExpectedEventCount> _expectedEventCounts = new Dictionary<string, ExpectedEventCount>()
        {
            { "LaksDemoEventSource", 100 },
            { "Microsoft-DotNETCore-EventPipe", 1},
            { "Microsoft-Windows-DotNETRuntime", -1 }
        };

        private static Action _eventGeneratingAction = () => 
        {
            GC.Collect();
            for (int i = 0; i < 100; i++)
            {                
                if (i % 10 == 0)
                    Console.WriteLine($"Fired MyEvent {i:N0}/100,000 times...");
                LaksDemoEventSource.Log.MyEvent();
            }
            GC.Collect();
        };
    }
}
