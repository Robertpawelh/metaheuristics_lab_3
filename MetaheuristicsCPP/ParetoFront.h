#pragma once

#include "DominationComparer.h"
#include "VectorUtils.h"

#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>

using namespace DominationComparers;

using namespace std;

namespace Optimizers
{
	class CParetoFront
	{
	public:
		CParetoFront(pair<double, double> &pObjectiveMaxValues, vector<pair<double, double>*> &vOptimalParetoFront, IDominationComparer &cDominationComparer);

		~CParetoFront();

		bool bAdd(const pair<double, double> &pObjectiveValues);

		double dCalculateHyperVolume();
		double dCalculateInversedGenerationalDistance();

		vector<pair<double, double>*> &vGetParetoFrontObjectiveValues() { return v_pareto_front; }

	private:
		bool b_insert(const pair<double, double> &pObjectiveValues);
		void v_sort();

		static double d_calculate_square_distance(pair<double, double> &pObjectiveValues0, pair<double, double> &pObjectiveValues1, double dMaxValue);
		static double d_calculate_min_distance(pair<double, double> &pObjectiveValues, vector<pair<double, double>*> &vParetoFront);

		vector<pair<double, double>*> v_pareto_front;
		
		pair<double, double> &p_objective_max_values;
		vector<pair<double, double>*> &v_optimal_pareto_front;

		IDominationComparer &c_domination_comparer;
	};//class CParetoFront
}//namespace Optimizers