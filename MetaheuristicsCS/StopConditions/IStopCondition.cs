using System;

namespace StopConditions
{
    interface IStopCondition
    {
        bool Stop(long iterationNumber, long FFE, DateTime startTime);
    }
}
