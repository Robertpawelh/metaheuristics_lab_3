using System;

namespace StopConditions
{
    class FFEStopCondition : IStopCondition
    {
        private readonly long maxFFE;

        public FFEStopCondition(long maxFFE)
        {
            this.maxFFE = maxFFE;
        }

        public bool Stop(long iterationNumber, long FFE, DateTime startTime)
        {
            return FFE >= maxFFE;
        }
    }
}
