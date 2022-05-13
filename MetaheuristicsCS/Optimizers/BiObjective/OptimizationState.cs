using System;
using System.Collections.Generic;

using DominationComparers.BiObjective;

namespace Optimizers.BiObjective
{
    class OptimizationState<Element> : Framework.AOptimizationState<Element, Tuple<double, double>, OptimizationResult<Element>>
    {
        private readonly Tuple<double, double> objectiveMaxValues;
        private readonly List<Tuple<double, double>> optimalParetoFront;
        private readonly DefaultDominationComparer dominationComparer;

        public OptimizationState(Tuple<double, double> objectiveMaxValues, List<Tuple<double, double>> optimalParetoFront)
        {
            this.objectiveMaxValues = objectiveMaxValues;
            this.optimalParetoFront = optimalParetoFront;
            dominationComparer = new DefaultDominationComparer();

            SetNewResult();
        }

        public override void Reset()
        {
            base.Reset();

            SetNewResult();
        }

        public override bool GlobalOptimumFound()
        {
            return false;
        }

        public override bool Update(List<Element> solution, Tuple<double, double> value, long iterationNumber, long FFE, double time, 
                                    bool onlyImprovements)
        {
            if(Result.Front.Add(value))
            {
                Result.LastUpdateIteration = iterationNumber;
                Result.LastUpdateFFE = FFE;
                Result.LastUpdateTime = time;

                return true;
            }

            return false;
        }

        private void SetNewResult()
        {
            Result = new OptimizationResult<Element>(objectiveMaxValues, optimalParetoFront, dominationComparer);
        }
    }
}
