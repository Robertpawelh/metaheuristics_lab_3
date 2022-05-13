using EvaluationsCLI;
using Generators;
using StopConditions;

namespace Optimizers.SingleObjective
{
    class RealRandomSearch : SamplingOptimizer<double>
    {
        public RealRandomSearch(IEvaluation<double, double> evaluation, IStopCondition stopCondition, int? seed = null)
            : base(evaluation, stopCondition, new RealRandomGenerator(evaluation.pcConstraint, seed))
        {
        }
    }
}
