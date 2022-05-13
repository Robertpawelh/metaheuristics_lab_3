using System;
using System.Collections.Generic;

using Optimizers.Framework;

namespace Optimizers.SingleObjective
{
    class OptimizationState<Element> : AOptimizationState<Element, double, OptimizationResult<Element>>
    {
        private readonly double maxValue;
        private readonly double epsilon;

        public OptimizationState(double maxValue, double epsilon = double.Epsilon)
        {
            this.maxValue = maxValue;
            this.epsilon = epsilon;
        }

        public override bool GlobalOptimumFound()
        {
            return Result != null && Math.Abs(Result.BestValue - maxValue) <= epsilon;
        }

        public override bool Update(List<Element> solution, double value, long iterationNumber, long FFE, double time, bool onlyImprovements)
        {
            if (Result == null || value > Result.BestValue || value == Result.BestValue && !onlyImprovements)
            {
                Result = new OptimizationResult<Element>(solution, value, iterationNumber, FFE, time);

                return true;
            }

            return false;
        }
    }
}
