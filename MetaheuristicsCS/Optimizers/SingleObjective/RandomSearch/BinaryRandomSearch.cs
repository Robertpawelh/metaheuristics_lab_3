using EvaluationsCLI;
using Generators;
using StopConditions;

namespace Optimizers.SingleObjective
{
    class BinaryRandomSearch : SamplingOptimizer<bool>
    {
        public BinaryRandomSearch(IEvaluation<bool, double> evaluation, IStopCondition stopCondition, int? seed = null)
            : base(evaluation, stopCondition, new BinaryRandomGenerator(evaluation.pcConstraint, seed))
        {
        }
    }
}
