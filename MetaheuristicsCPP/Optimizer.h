#pragma once

#include "OptimizationState.h"
#include "StopCondition.h"
#include "TimeUtils.h"

#include <ctime>
#include <Evaluation.h>
#include <random>
#include <vector>

using namespace StopConditions;

using namespace Evaluations;
using namespace std;

namespace Optimizers
{
	template <typename TElement, class TOptimizationResult>
	class IOptimizer
	{
	public:
		virtual ~IOptimizer() = default;

		virtual void vInitialize() = 0;
		virtual bool bRunIteration() = 0;
		virtual bool bShouldStop() = 0;

		virtual void vRun() = 0;

		virtual TOptimizationResult *pcGetResult() = 0;
	};//class IOptimizer


	template <typename TElement, typename TEvaluationResult, class TOptimizationResult>
	class COptimizer : public IOptimizer<TElement, TOptimizationResult>
	{
	public:
		COptimizer(IEvaluation<TElement, TEvaluationResult> &cEvaluation, IStopCondition &cStopCondition, IOptimizationState<TElement, TEvaluationResult, TOptimizationResult> *pcState)
			: c_evaluation(cEvaluation), c_stop_condition(cStopCondition), pc_state(pcState)
		{

		}//COptimizer(IEvaluation<TElement, TEvaluationResult> &cEvaluation, IStopCondition &cStopCondition, IOptimizationState<TElement, TEvaluationResult, TOptimizationResult> *pcState)

		COptimizer(const COptimizer<TElement, TEvaluationResult, TOptimizationResult> &cOther) = delete;
		COptimizer(COptimizer<TElement, TEvaluationResult, TOptimizationResult> &&cOther) = delete;

		virtual ~COptimizer()
		{
			delete pc_state;
		}//virtual ~COptimizer()

		virtual void vInitialize() final
		{
			pc_state->vReset();

			i_iteration_number = 0;
			t_start_time = clock();

			v_initialize(t_start_time);
		}//virtual void vInitialize() final

		virtual bool bRunIteration() final
		{
			bool b_best_updated = b_run_iteration(i_iteration_number, t_start_time);
			i_iteration_number++;

			return b_best_updated;
		}//virtual void vRunIteration() final

		virtual bool bShouldStop() final
		{
			return pc_state->bGlobalOptimumFound() || c_stop_condition.bStop(i_iteration_number, c_evaluation.iGetFFE(), t_start_time);
		}//virtual bool bShouldStop() final

		virtual void vRun()
		{
			vInitialize();

			while (!bShouldStop())
			{
				bRunIteration();
			}//while (!bShouldStop())
		}//virtual void vRun()

		virtual TOptimizationResult *pcGetResult() { return pc_state->pcGetResult(); }

		COptimizer<TElement, TEvaluationResult, TOptimizationResult>& operator=(const COptimizer<TElement, TEvaluationResult, TOptimizationResult> &cOther) = delete;
		COptimizer<TElement, TEvaluationResult, TOptimizationResult>& operator=(COptimizer<TElement, TEvaluationResult, TOptimizationResult> &&cOther) = delete;

	protected:
		virtual void v_initialize(clock_t tStartTime) = 0;
		virtual bool b_run_iteration(long long iIterationNumber, clock_t tStartTime) = 0;
		
		bool b_update_state(const vector<TElement> &vSolution, const TEvaluationResult &tValue, bool bOnlyImprovements = true)
		{
			return pc_state->bUpdate(vSolution, tValue, i_iteration_number, c_evaluation.iGetFFE(), TimeUtils::dCalculateSeconds(t_start_time), bOnlyImprovements);
		}//bool b_update_state(const vector<TElement> &vSolution, const TEvaluationResult &tValue, bool bOnlyImprovements = true)

		IEvaluation<TElement, TEvaluationResult> &c_evaluation;
		IStopCondition &c_stop_condition;

	private:
		long long i_iteration_number;
		clock_t t_start_time;

		IOptimizationState<TElement, TEvaluationResult, TOptimizationResult> *pc_state;
	};//class COptimizer : public IOptimizer<TElement, TOptimizationResult>
}//namespace Optimizers