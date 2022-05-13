#pragma once

#include "DominationComparer.h"
#include "ParetoFront.h"

#include <utility>
#include <vector>

using namespace DominationComparers;

using namespace std;

namespace Optimizers
{
	template <typename TElement>
	class CBiObjectiveOptimizationResult
	{
	public:
		CBiObjectiveOptimizationResult(pair<double, double> &pObjectiveMaxValues, vector<pair<double, double>*> &vOptimalParetoFront, IDominationComparer &cDominationComparer)
			: c_pareto_front(pObjectiveMaxValues, vOptimalParetoFront, cDominationComparer)
		{

		}//CBiObjectiveOptimizationResult(pair<double, double> &pObjectiveMaxValues, vector<pair<double, double>*> &vOptimalParetoFront, IDominationComparer &cDominationComparer)

		CParetoFront &cGetParetoFront() { return c_pareto_front; }

		long long iGetLastUpdateIteration() { return i_last_update_iteration; }
		long long iGetLastUpdateFFE() { return i_last_update_ffe; }
		double dGetLastUpdateTime() { return d_last_update_time; }

		void vSetLastUpdateIteration(long long iLastUpdateIteration) { i_last_update_iteration = iLastUpdateIteration; }
		void vSetLastUpdateFFE(long long iLastUpdateFFE) { i_last_update_ffe = iLastUpdateFFE; }
		void vSetLastUpdateTime(double dLastUpdateTime) { d_last_update_time = dLastUpdateTime; }

	private:
		CParetoFront c_pareto_front;

		long long i_last_update_iteration;
		long long i_last_update_ffe;
		double d_last_update_time;
	};//class CBiObjectiveOptimizationResult
}//namespace Optimizers