#include "BinaryNSGA2Selection.h"

using namespace Selections;

CBinaryNSGA2Selection::CBinaryNSGA2Selection(int iTournamentSize, CBinaryNSGA2Ranking &cRanking, mt19937 &cRandomEngine)
	: CSelection<bool, pair<double, double>>(cRandomEngine, false), i_tournament_size(iTournamentSize), c_ranking(cRanking)
{

}//CBinaryNSGA2Selection::CBinaryNSGA2Selection(int iTournamentSize, CBinaryNSGA2Ranking &cRanking, mt19937 &cRandomEngine)

void CBinaryNSGA2Selection::v_add_to_new_population(vector<CIndividual<bool, pair<double, double>>*> &vPopulation, vector<CIndividual<bool, pair<double, double>>*> &vNewPopulation)
{
	unordered_map<CIndividual<bool, pair<double, double>>*, int> m_ranking;

	for (size_t i = 0; i < c_ranking.vGetRanking().size(); i++)
	{
		m_ranking[c_ranking.vGetRanking()[i]] = (int)i;
	}//for (size_t i = 0; i < c_ranking.vGetRanking().size(); i++)

	vector<size_t> v_indexes(vPopulation.size());
	iota(v_indexes.begin(), v_indexes.end(), 0);

	CIndividual<bool, pair<double, double>> *pc_tournament_winner;

	for (size_t i = 0; i < vPopulation.size(); i++)
	{
		shuffle(v_indexes.begin(), v_indexes.end(), this->c_random_engine);

		pc_tournament_winner = pc_get_tournament_winner(vPopulation, v_indexes, m_ranking);

		vNewPopulation.push_back(new CIndividual<bool, pair<double, double>>(*pc_tournament_winner));
	}//for (size_t i = 0; i < vPopulation.size(); i++)
}//void CBinaryNSGA2Selection::v_add_to_new_population(vector<CIndividual<bool, pair<double, double>>*> &vPopulation, vector<CIndividual<bool, pair<double, double>>*> &vNewPopulation)

CIndividual<bool, pair<double, double>>* CBinaryNSGA2Selection::pc_get_tournament_winner(vector<CIndividual<bool, pair<double, double>>*> &vPopulation, vector<size_t> &vIndexes, unordered_map<CIndividual<bool, pair<double, double>>*, int> &mRanking)
{
	CIndividual<bool, pair<double, double>> *pc_tournament_winner = vPopulation[vIndexes.front()];

	for (int i = 1; i < i_tournament_size; i++)
	{
		if (mRanking[vPopulation[vIndexes[i]]] < mRanking[pc_tournament_winner])
		{
			pc_tournament_winner = vPopulation[vIndexes[i]];
		}//if (mRanking[vPopulation[vIndexes[i]]] < mRanking[pc_tournament_winner])
	}//for (int i = 1; i < i_tournament_size; i++)

	return pc_tournament_winner;
}//CIndividual<bool, pair<double, double>>* CBinaryNSGA2Selection::pc_get_tournament_winner(vector<CIndividual<bool, pair<double, double>>*> &vPopulation, vector<size_t> &vIndexes, unordered_map<CIndividual<bool, pair<double, double>>*, int> &mRanking)