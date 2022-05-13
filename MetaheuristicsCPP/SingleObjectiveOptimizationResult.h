#pragma once

#include <vector>

using namespace std;

namespace Optimizers
{
	template <typename TElement>
	class CSingleObjectiveOptimizationResult
	{
	public:
		CSingleObjectiveOptimizationResult(vector<TElement> vBestSolution, double dBestValue, long long iBestIteration, long long iBestFFE, double dBestTime)
			: v_best_solution(vBestSolution), d_best_value(dBestValue), i_best_iteration(iBestIteration), i_best_ffe(iBestFFE), d_best_time(dBestTime)
		{

		}//CSingleObjectiveOptimizationResult(vector<TElement> vBestSolution, double dBestValue, long long iBestIteration, long long iBestFFE, double dBestTime)

		vector<TElement> &vGetBestSolution() { return v_best_solution; }
		double dGetBestValue() { return d_best_value; }

		long long iGetBestIteration() { return i_best_iteration; }
		long long iGetBestFFE() { return i_best_ffe; }
		double dGetBestTime() { return d_best_time; }

	private:
		double d_best_value;
		vector<TElement> v_best_solution;

		long long i_best_iteration;
		long long i_best_ffe;
		double d_best_time;
	};//class CSingleObjectiveOptimizationResult
}//namespace Optimizers
