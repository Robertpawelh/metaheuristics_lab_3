#pragma once

#include "BinaryNSGA2Ranking.h"
#include "Individual.h"
#include "Selection.h"

#include <numeric>
#include <random>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

namespace Selections
{
	class CBinaryNSGA2Selection : public CSelection<bool, pair<double, double>>
	{
	public:
		CBinaryNSGA2Selection(int iTournamentSize, CBinaryNSGA2Ranking &cRanking, mt19937 &cRandomEngine);

	protected:
		virtual void v_add_to_new_population(vector<CIndividual<bool, pair<double, double>>*> &vPopulation, vector<CIndividual<bool, pair<double, double>>*> &vNewPopulation);

	private:
		CIndividual<bool, pair<double, double>> *pc_get_tournament_winner(vector<CIndividual<bool, pair<double, double>>*> &vPopulation, 
			vector<size_t> &vIndexes, 
			unordered_map<CIndividual<bool, pair<double, double>>*, int> &mRanking);

		int i_tournament_size;
		CBinaryNSGA2Ranking &c_ranking;
	};//class CBinaryNSGA2Selection : public ISelection<bool, pair<double, double>>
}//namespace Selections