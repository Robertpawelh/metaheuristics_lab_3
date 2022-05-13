using System;
using System.Collections.Generic;

using EvaluationsCLI;
using Generators;
using Mutations;
using Optimizers.Framework;
using StopConditions;

namespace Optimizers.SingleObjective
{
    class RealEvolutionStrategy11 : AOptimizer<double, double, OptimizationResult<double>>
    {
        private readonly ARealMutationES11Adaptation mutationAdaptation;
        private readonly RealRandomGenerator randomGeneration;

        public RealEvolutionStrategy11(IEvaluation<double, double> evaluation, IStopCondition stopCondition, 
                                       ARealMutationES11Adaptation mutationAdaptation, int? seed = null)
            : base(evaluation, stopCondition, new OptimizationState<double>(evaluation.tMaxValue))
        {
            this.mutationAdaptation = mutationAdaptation;
            randomGeneration = new RealRandomGenerator(evaluation.pcConstraint, seed);
        }

        protected override void Initialize(DateTime startTime)
        {
            List<double> initialSolution = randomGeneration.Create(evaluation.iSize);

            UpdateState(initialSolution, evaluation.tEvaluate(initialSolution));
        }

        protected override bool RunIteration(long itertionNumber, DateTime startTime)
        {
            List<double> candidateSolution = new List<double>(Result.BestSolution);

            mutationAdaptation.Mutation.Mutate(candidateSolution);
            double candidateValue = evaluation.tEvaluate(candidateSolution);

            mutationAdaptation.Adapt(Result.BestValue, Result.BestSolution, candidateValue, candidateSolution);

            return UpdateState(candidateSolution, candidateValue);
        }
    }
}
