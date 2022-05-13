using System.Collections.Generic;

namespace Optimizers.SingleObjective
{
    class OptimizationResult<Element>
    {
        public List<Element> BestSolution { get; }
        public double BestValue { get; }
        public long BestIteration { get; }
        public long BestFFE { get; }
        public double BestTime { get; }

        public OptimizationResult(List<Element> bestSolution, double bestValue, long bestIteration, long bestFFE, double bestTime)
        {
            BestSolution = new List<Element>(bestSolution);
            BestValue = bestValue;
            BestIteration = bestIteration;
            BestFFE = bestFFE;
            BestTime = bestTime;
        }
    }
}
