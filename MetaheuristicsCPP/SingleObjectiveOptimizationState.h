#pragma once

#include "OptimizationState.h"
#include "SingleObjectiveOptimizationResult.h"

#include <cfloat>
#include <cmath>

namespace Optimizers
{
	template <typename TElement>
	class CSingleObjectiveOptimizationState : public COptimizationState<TElement, double, CSingleObjectiveOptimizationResult<TElement>>
	{
	public:
		CSingleObjectiveOptimizationState(double dMaxValue, double dEpsilon = DBL_EPSILON)
		{
			d_max_value = dMaxValue;
			d_epsilon = dEpsilon;
		}//CSingleObjectiveOptimizationState(double dMaxValue, double dEpsilon = DBL_EPSILON)

		virtual bool bUpdate(const vector<TElement> &vSolution, const double &tValue, long long iIterationNumber, long long iFFE, double dTime, bool bOnlyImprovements)
		{
			bool b_best_updated = false;

			if (this->pc_result == nullptr || tValue > this->pc_result->dGetBestValue() || tValue == this->pc_result->dGetBestValue() && !bOnlyImprovements)
			{
				delete this->pc_result;
				this->pc_result = new CSingleObjectiveOptimizationResult<TElement>(vSolution, tValue, iIterationNumber, iFFE, dTime);

				b_best_updated = true;
			}//if (this->pc_result == nullptr || tValue > this->pc_result->dGetBestValue() || tValue == this->pc_result->dGetBestValue() && !bOnlyImprovements)

			return b_best_updated;
		}//virtual bool bUpdate(const vector<TElement> &vSolution, const double &tValue, long long iIterationNumber, long long iFFE, double dTime, bool bOnlyImprovements)

		virtual bool bGlobalOptimumFound()
		{
			return this->pc_result != nullptr && abs(this->pc_result->dGetBestValue() - d_max_value) <= d_epsilon;
		}//virtual bool bGlobalOptimumFound()

	private:
		double d_max_value;
		double d_epsilon;
	};//class CSingleObjectiveOptimizationState : public COptimizationState<TElement, double, CSingleObjectiveOptimizationResult<TElement>>
}//namespace Optimizers