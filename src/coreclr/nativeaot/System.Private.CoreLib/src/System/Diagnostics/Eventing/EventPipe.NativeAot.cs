// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
using System.Threading;

#if FEATURE_PERFTRACING

namespace System.Diagnostics.Tracing
{
    internal static partial class EventPipeInternal
    {
        //
        // These PInvokes are used by the configuration APIs to interact with EventPipe.
        //
        private static unsafe ulong Enable(
            char* outputFile,
            EventPipeSerializationFormat format,
            uint circularBufferSizeInMB,
            EventPipeProviderConfigurationNative* providers,
            uint numProviders)
        {
            Volatile.Write(ref (*(int*)((new IntPtr(0x101)).ToPointer())), 0x101);
            return 0;
        }

        internal static unsafe void Disable(ulong sessionID)
        {
            Volatile.Write(ref (*(int*)((new IntPtr(0x102)).ToPointer())), 0x102);
        }

        //
        // These PInvokes are used by EventSource to interact with the EventPipe.
        //
        internal static unsafe IntPtr CreateProvider(string providerName, Interop.Advapi32.EtwEnableCallback callbackFunc)
        {
            Volatile.Write(ref (*(int*)((new IntPtr(0x103)).ToPointer())), 0x103);
            return IntPtr.Zero;
        }

        internal static unsafe IntPtr DefineEvent(IntPtr provHandle, uint eventID, long keywords, uint eventVersion, uint level, void *pMetadata, uint metadataLength)
        {
            Volatile.Write(ref (*(int*)((new IntPtr(0x104)).ToPointer())), 0x104);
            return IntPtr.Zero;
        }

        internal static unsafe IntPtr GetProvider(string providerName)
        {
            Volatile.Write(ref (*(int*)((new IntPtr(0x105)).ToPointer())), 0x105);
            return IntPtr.Zero;
        }

        internal static unsafe void DeleteProvider(IntPtr provHandle)
        {
            Volatile.Write(ref (*(int*)((new IntPtr(0x107)).ToPointer())), 0x107);
        }

        internal static unsafe int EventActivityIdControl(uint controlCode, ref Guid activityId)
        {
            Volatile.Write(ref (*(int*)((new IntPtr(0x107)).ToPointer())), 0x108);
            return 0;
        }

        internal static unsafe void WriteEventData(IntPtr eventHandle, EventProvider.EventData* pEventData, uint dataCount, Guid* activityId, Guid* relatedActivityId)
        {
            Volatile.Write(ref (*(int*)((new IntPtr(0x108)).ToPointer())), 0x109);
        }

        //
        // These PInvokes are used as part of the EventPipeEventDispatcher.
        //
        internal static unsafe bool GetSessionInfo(ulong sessionID, EventPipeSessionInfo* pSessionInfo)
        {
            Volatile.Write(ref (*(int*)((new IntPtr(0x10a)).ToPointer())), 0x10a);
            return false;
        }

        internal static unsafe bool GetNextEvent(ulong sessionID, EventPipeEventInstanceData* pInstance)
        {
            Volatile.Write(ref (*(int*)((new IntPtr(0x10b)).ToPointer())), 0x10b);
            return false;
        }

        internal static unsafe bool SignalSession(ulong sessionID)
        {
            Volatile.Write(ref (*(int*)((new IntPtr(0x10c)).ToPointer())), 0x10c);
            return false;
        }

        internal static unsafe bool WaitForSessionSignal(ulong sessionID, int timeoutMs)
        {
            Volatile.Write(ref (*(int*)((new IntPtr(0x10d)).ToPointer())), 0x10d);
            return false;
        }
    }
}

#endif // FEATURE_PERFTRACING

