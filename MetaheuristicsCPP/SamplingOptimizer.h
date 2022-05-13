#pragma once

#include "Generator.h"
#include "Optimizer.h"
#include "SingleObjectiveOptimizationResult.h"
#include "SingleObjectiveOptimizationState.h"

#include <vector>

using namespace Generators;

using namespace std;

namespace Optimizers
{
	template <typename TElement>
	class CSamplingOptimizer : public COptimizer<TElement, double, CSingleObjectiveOptimizationResult<TElement>>
	{
	public:
		CSamplingOptimizer(IEvaluation<TElement, double> &cEvaluation, IStopCondition &cStopCondition, IGenerator<TElement> &cGeneration)
			: COptimizer<TElement, double, CSingleObjectiveOptimizationResult<TElement>>(cEvaluation, cStopCondition, new CSingleObjectiveOptimizationState<TElement>(cEvaluation.tGetMaxValue())), c_generation(cGeneration)
		{

		}//CSamplingOptimizer(IEvaluation<TElement, double> &cEvaluation, IStopCondition &cStopCondition, IGenerator<TElement> &cGeneration)

	protected:
		virtual void v_initialize(clock_t tStartTime) { }

		virtual bool b_run_iteration(long long iIterationNumber, clock_t tStartTime)
		{
			vector<TElement> *pv_solution = c_generation.pvCreate(this->c_evaluation.iGetSize());
			double d_value = this->c_evaluation.tEvaluate(*pv_solution);

			bool b_updated = this->b_update_state(*pv_solution, d_value);

			delete pv_solution;

			return b_updated;
		}//virtual bool b_run_iteration(long long iIterationNumber, clock_t tStartTime)

	private:
		IGenerator<TElement> &c_generation;
	};//class CSamplingOptimizer : public COptimizer<TElement, double, CSingleObjectiveOptimizationResult<TElement>>
}//namespace Optimizers
