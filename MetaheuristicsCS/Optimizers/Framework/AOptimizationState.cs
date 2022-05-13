using System.Collections.Generic;

namespace Optimizers.Framework
{
    abstract class AOptimizationState<Element, EvaluationResult, OptimizationResult>
    {
        public OptimizationResult Result { get; protected set; }

        public AOptimizationState()
        {
            Reset();
        }

        public virtual void Reset()
        {
            Result = default(OptimizationResult);
        }

        public abstract bool GlobalOptimumFound();
        public abstract bool Update(List<Element> solution, EvaluationResult value, long iterationNumber, long FFE, double time,
                                    bool onlyImprovements);
    }
}
