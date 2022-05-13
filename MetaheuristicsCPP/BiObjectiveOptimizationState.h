#pragma once

#include "BiObjectiveOptimizationResult.h"
#include "DominationComparers.h"
#include "OptimizationState.h"

#include <cfloat>
#include <cmath>
#include <utility>
#include <vector>

using namespace DominationComparers;

using namespace std;

namespace Optimizers
{
	template <typename TElement>
	class CBiObjectiveOptimizationState : public COptimizationState<TElement, pair<double, double>, CBiObjectiveOptimizationResult<TElement>>
	{
	public:
		CBiObjectiveOptimizationState(pair<double, double> &pObjectiveMaxValues, vector<pair<double, double>*> &vOptimalParetoFront)
			: p_objective_max_values(pObjectiveMaxValues), v_optimal_pareto_front(vOptimalParetoFront)
		{
			v_set_new_result();
		}//CBiObjectiveOptimizationState(pair<double, double> &pObjectiveMaxValues, vector<pair<double, double>*> &vOptimalParetoFront)

		virtual bool bUpdate(const vector<TElement> &vSolution, const pair<double, double> &tValue, long long iIterationNumber, long long iFFE, double dTime, bool bOnlyImprovements)
		{
			bool b_pareto_front_updated = this->pc_result->cGetParetoFront().bAdd(tValue);

			if (b_pareto_front_updated)
			{
				this->pc_result->vSetLastUpdateIteration(iIterationNumber);
				this->pc_result->vSetLastUpdateFFE(iFFE);
				this->pc_result->vSetLastUpdateTime(dTime);
			}//if (b_pareto_front_updated)

			return b_pareto_front_updated;
		}//virtual bool bUpdate(const vector<TElement> &vSolution, const pair<double, double> &tValue, long long iIterationNumber, long long iFFE, double dTime, bool bOnlyImprovements)

		virtual bool bGlobalOptimumFound()
		{
			return this->pc_result->cGetParetoFront().dCalculateInversedGenerationalDistance() == 0;
		}//virtual bool bGlobalOptimumFound()

		virtual void vReset()
		{
			COptimizationState<TElement, pair<double, double>, CBiObjectiveOptimizationResult<TElement>>::vReset();
			v_set_new_result();
		}//virtual void vReset()

	private:
		void v_set_new_result()
		{
			this->pc_result = new CBiObjectiveOptimizationResult<TElement>(p_objective_max_values, v_optimal_pareto_front, c_domination_comparer);
		}//CBiObjectiveOptimizationResult<TElement> *pc_create_result()

		pair<double, double> &p_objective_max_values;
		vector<pair<double, double>*> &v_optimal_pareto_front;
		CDefaultDominationComparer c_domination_comparer;
	};//class CBiObjectiveOptimizationState : public COptimizationState<TElement, pair<double, double>, CBiObjectiveOptimizationResult<TElement>>
}//namespace Optimizers