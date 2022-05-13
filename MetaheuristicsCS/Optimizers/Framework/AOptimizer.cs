using System;
using System.Collections.Generic;

using EvaluationsCLI;
using StopConditions;
using Utility;

namespace Optimizers.Framework
{
    abstract class AOptimizer<Element, EvaluationResult, OptimizationResult>
    {
        protected IEvaluation<Element, EvaluationResult> evaluation;
        protected IStopCondition stopCondition;

        private long iterationNumber;
        private DateTime startTime;

        private readonly AOptimizationState<Element, EvaluationResult, OptimizationResult> state;

        public AOptimizer(IEvaluation<Element, EvaluationResult> evaluation, IStopCondition stopCondition, 
                          AOptimizationState<Element, EvaluationResult, OptimizationResult> state)
        {
            this.evaluation = evaluation;
            this.stopCondition = stopCondition;
            this.state = state;
        }

        public void Initialize()
        {
            state.Reset();

            iterationNumber = 0;
            startTime = DateTime.UtcNow;

            Initialize(startTime);
        }

        public bool RunIteration()
		{
			return RunIteration(iterationNumber++, startTime);
		}

        public bool ShouldStop()
        {
            return state.GlobalOptimumFound() || stopCondition.Stop(iterationNumber, evaluation.iFFE, startTime);
        }

        public void Run()
        {
            Initialize();

            while (!ShouldStop())
            {
                RunIteration();
            }
        }

        public OptimizationResult Result
        {
            get { return state.Result; }
        }

        protected abstract void Initialize(DateTime startTime);
        protected abstract bool RunIteration(long itertionNumber, DateTime startTime);

        protected bool UpdateState(List<Element> solution, EvaluationResult value, bool onlyImprovements = true)
        {
            return state.Update(solution, value, iterationNumber, evaluation.iFFE, TimeUtils.DurationInSeconds(startTime), onlyImprovements);
        }
    }
}
