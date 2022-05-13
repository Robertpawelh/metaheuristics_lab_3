using System;
using System.Collections.Generic;

using DominationComparers.BiObjective;

namespace Optimizers.BiObjective
{
    class OptimizationResult<Element>
    {
        public ParetoFront Front { get; }

        public long LastUpdateIteration { get; set; }
        public long LastUpdateFFE { get; set; }
        public double LastUpdateTime { get; set; }

        public OptimizationResult(Tuple<double, double> objectiveMaxValues, List<Tuple<double, double>> optimalParetoFront, 
                                  IDominationComparer dominationComparer)
        {
            Front = new ParetoFront(objectiveMaxValues, optimalParetoFront, dominationComparer);
        }
    }
}
