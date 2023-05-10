// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.

using System;
using System.Diagnostics.Tracing;
using System.Threading;

namespace Tracing.Tests.Simple2
{
    public sealed class LaksDemoEventSource : EventSource
    {
        private LaksDemoEventSource() {}
        public static LaksDemoEventSource Log = new LaksDemoEventSource();
        public void MyEvent() { WriteEvent(1, "MyEvent"); }
        protected override void OnEventCommand(EventCommandEventArgs command)
        {
            Console.WriteLine($"On LaksDemoEventSource.OnEventCommand:{command.Command}");
            base.OnEventCommand(command);
        }

    }

    public class ProviderValidation2
    {
        public static int Main()
        {
            // This test (temp?) validates event behavior via dotnet-trace and perfview

            Console.WriteLine("Waiting 10 seconds to client to get the PID");
            Thread.Sleep(10*1000);

            LaksDemoEventSource.Log.MyEvent();

            Console.WriteLine("Waiting 10 seconds to EventPipe to write the data");
            Thread.Sleep(10*1000);

            Console.WriteLine("Completed");

            return 100;
        }
    }
}
