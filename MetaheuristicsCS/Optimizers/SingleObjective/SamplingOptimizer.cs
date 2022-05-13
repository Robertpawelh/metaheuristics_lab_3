using System;
using System.Collections.Generic;

using Generators;
using EvaluationsCLI;
using Optimizers.Framework;
using StopConditions;

namespace Optimizers.SingleObjective
{
    class SamplingOptimizer<Element> : AOptimizer<Element, double, OptimizationResult<Element>>
    {
        private readonly AGenerator<Element> generator;

        public SamplingOptimizer(IEvaluation<Element, double> evaluation, IStopCondition stopCondition, AGenerator<Element> generator)
            : base(evaluation, stopCondition, new OptimizationState<Element>(evaluation.tMaxValue))
        {
            this.generator = generator;
        }

        protected override void Initialize(DateTime startTime)
        {
        }

        protected override bool RunIteration(long itertionNumber, DateTime startTime)
        {
            List<Element> solution = generator.Create(evaluation.iSize);

            return UpdateState(solution, evaluation.tEvaluate(solution));
        }
    }
}
