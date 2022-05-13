#pragma once

#include "BinaryNSGA2Individual.h"
#include "DominationComparer.h"
#include "Individual.h"
#include "VectorUtils.h"

#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace DominationComparers;

using namespace std;

namespace Optimizers
{
	class CBinaryNSGA2Ranking
	{
	public:
		CBinaryNSGA2Ranking(pair<double, double> &pMaxObjectiveValues, IDominationComparer &cDominationComparer);

		~CBinaryNSGA2Ranking();

		void vAdd(const CIndividual<bool, pair<double, double>> &cIndividual);
		void vUpdateRanking();
		void vRemove(int iFromIndex);

		vector<CBinaryNSGA2Individual*> &vGetRanking() { return v_ranking; }

	private:
		void v_reset_ranking_individual_data();
		void v_set_crowding_distance(vector<CBinaryNSGA2Individual*> &vParetoFront);
		void v_set_crowding_distance_first_objective(vector<CBinaryNSGA2Individual*> &vParetoFront);
		void v_set_crowding_distance_second_objective(vector<CBinaryNSGA2Individual*> &vParetoFront);

		vector<CBinaryNSGA2Individual*> v_ranking;

		pair<double, double> &p_max_objective_values;
		IDominationComparer &c_domination_comparer;
	};//class CBinaryNSGA2Ranking
}//namespace Optimizers