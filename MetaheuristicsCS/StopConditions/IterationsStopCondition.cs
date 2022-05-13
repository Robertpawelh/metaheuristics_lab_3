using System;

namespace StopConditions
{
    class IterationsStopCondition : IStopCondition
    {
        private readonly long maxIterationNumber;

        public IterationsStopCondition(long maxIterationNumber)
        {
            this.maxIterationNumber = maxIterationNumber;
        }

        public bool Stop(long iterationNumber, long FFE, DateTime startTime)
        {
            return iterationNumber >= maxIterationNumber;
        }
    }
}
