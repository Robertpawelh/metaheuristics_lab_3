using System;

using Utility;

namespace StopConditions
{
    class RunningTimeStopCondition : IStopCondition
    {
        private readonly double maxRunningTime;

        public RunningTimeStopCondition(double maxRunningTime)
        {
            this.maxRunningTime = maxRunningTime;
        }

        public bool Stop(long iterationNumber, long FFE, DateTime startTime)
        {
            return TimeUtils.DurationInSeconds(startTime) >= maxRunningTime;
        }
    }
}
