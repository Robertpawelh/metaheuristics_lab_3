#include "BinaryNSGA2Ranking.h"

using namespace Optimizers;

CBinaryNSGA2Ranking::CBinaryNSGA2Ranking(pair<double, double> &pMaxObjectiveValues, IDominationComparer &cDominationComparer)
	: p_max_objective_values(pMaxObjectiveValues), c_domination_comparer(cDominationComparer)
{

}//CBinaryNSGA2Ranking::CBinaryNSGA2Ranking(pair<double, double> &pMaxObjectiveValues, IDominationComparer &cDominationComparer)

CBinaryNSGA2Ranking::~CBinaryNSGA2Ranking()
{
	VectorUtils::vClear(v_ranking);
}//CBinaryNSGA2Ranking::~CBinaryNSGA2Ranking()

void CBinaryNSGA2Ranking::vAdd(const CIndividual<bool, pair<double, double>> &cIndividual)
{
	v_ranking.push_back(new CBinaryNSGA2Individual(cIndividual));
}//void CBinaryNSGA2Ranking::vAdd(const CIndividual<bool, pair<double, double>> &cIndividual)

void CBinaryNSGA2Ranking::vUpdateRanking()
{
	v_reset_ranking_individual_data();

	vector<CBinaryNSGA2Individual*> v_current_pareto_front;
	vector<CBinaryNSGA2Individual*> v_next_pareto_front;
	
	CBinaryNSGA2Individual* pc_individual_i, *pc_individual_j;

	int i_domination_comparison_result;

	int i_front_index = 0;

	for (size_t i = 0; i < v_ranking.size(); i++)
	{
		pc_individual_i = v_ranking[i];

		for (size_t j = 0; j < v_ranking.size(); j++)
		{
			if (i != j)
			{
				pc_individual_j = v_ranking[j];

				i_domination_comparison_result = c_domination_comparer.iCompare(pc_individual_i->tGetFitness(), pc_individual_j->tGetFitness());

				if (i_domination_comparison_result > 0)
				{
					pc_individual_i->vGetIndividualsDominatedBy().push_back(pc_individual_j);
				}//if (i_domination_comparison_result > 0)
				else if (i_domination_comparison_result < 0)
				{
					pc_individual_i->vSetDominationCounter(pc_individual_i->iGetDominationCounter() + 1);
				}//else if (i_domination_comparison_result < 0)
			}//if (i != j)
		}//for (size_t j = 0; j < v_ranking.size(); j++)

		if (pc_individual_i->iGetDominationCounter() == 0)
		{
			pc_individual_i->vSetFrontIndex(i_front_index);
			v_current_pareto_front.push_back(pc_individual_i);
		}//if (pc_individual_i->iGetDominationCounter() == 0)
	}//for (size_t i = 0; i < v_ranking.size(); i++)

	while (!v_current_pareto_front.empty())
	{
		v_set_crowding_distance(v_current_pareto_front);

		i_front_index++;

		for (size_t i = 0; i < v_current_pareto_front.size(); i++)
		{
			pc_individual_i = v_current_pareto_front[i];

			for (size_t j = 0; j < pc_individual_i->vGetIndividualsDominatedBy().size(); j++)
			{
				pc_individual_j = pc_individual_i->vGetIndividualsDominatedBy()[j];
				pc_individual_j->vSetDominationCounter(pc_individual_j->iGetDominationCounter() - 1);

				if (pc_individual_j->iGetDominationCounter() == 0)
				{
					pc_individual_j->vSetFrontIndex(i_front_index);
					v_next_pareto_front.push_back(pc_individual_j);
				}//if (pc_individual_j->iGetDominationCounter() == 0)
			}//for (size_t j = 0; j < pc_individual_i->vGetIndividualsDominatedBy().size(); j++)
		}//for (size_t i = 0; i < v_current_pareto_front.size(); i++)

		v_current_pareto_front = v_next_pareto_front;
		v_next_pareto_front.clear();
	}//while (!v_current_pareto_front.empty())

	sort(v_ranking.begin(), v_ranking.end(), [](CBinaryNSGA2Individual *pcIndividual0, CBinaryNSGA2Individual *pcIndividual1)
	{
		return pcIndividual0->iGetFrontIndex() < pcIndividual1->iGetFrontIndex() || pcIndividual0->iGetFrontIndex() == pcIndividual1->iGetFrontIndex() && pcIndividual0->dGetCrowdingDistance() > pcIndividual1->dGetCrowdingDistance();
	});//sort(v_ranking.begin(), v_ranking.end(), [](CBinaryNSGA2Individual *pcIndividual0, CBinaryNSGA2Individual *pcIndividual1)
}//void CBinaryNSGA2Ranking::vUpdateRanking()

void CBinaryNSGA2Ranking::vRemove(int iFromIndex)
{
	for (int i = iFromIndex; i < (int)v_ranking.size(); i++)
	{
		delete v_ranking[i];
	}//for (int i = iFromIndex; i < (int)v_ranking.size(); i++)

	v_ranking.erase(v_ranking.begin() + iFromIndex, v_ranking.end());
}//void CBinaryNSGA2Ranking::vRemove(int iFromIndex)

void CBinaryNSGA2Ranking::v_reset_ranking_individual_data()
{
	for (size_t i = 0; i < v_ranking.size(); i++)
	{
		v_ranking[i]->vSetDominationCounter(0);
		v_ranking[i]->vGetIndividualsDominatedBy().clear();
		v_ranking[i]->vSetCrowdingDistance(0);
	}//for (size_t i = 0; i < v_ranking.size(); i++)
}//void CBinaryNSGA2Ranking::v_reset_ranking_individual_data()

void CBinaryNSGA2Ranking::v_set_crowding_distance(vector<CBinaryNSGA2Individual*> &vParetoFront)
{
	v_set_crowding_distance_first_objective(vParetoFront);
	v_set_crowding_distance_second_objective(vParetoFront);
}//void CBinaryNSGA2Ranking::v_set_crowding_distance(vector<CBinaryNSGA2Individual*> &vParetoFront)

void CBinaryNSGA2Ranking::v_set_crowding_distance_first_objective(vector<CBinaryNSGA2Individual*> &vParetoFront)
{
	sort(vParetoFront.begin(), vParetoFront.end(), [](CBinaryNSGA2Individual *pcIndividual0, CBinaryNSGA2Individual *pcIndividual1)
	{
		return pcIndividual0->tGetFitness().first < pcIndividual1->tGetFitness().first;
	});//sort(vParetoFront.begin(), vParetoFront.end(), [](CBinaryNSGA2Individual *pcIndividual0, CBinaryNSGA2Individual *pcIndividual1)

	vParetoFront.front()->vSetCrowdingDistance(DBL_MAX / 2);
	vParetoFront.back()->vSetCrowdingDistance(DBL_MAX / 2);

	for (size_t i = 1; i + 1 < vParetoFront.size(); i++)
	{
		vParetoFront[i]->vSetCrowdingDistance((vParetoFront[i + 1]->tGetFitness().first - vParetoFront[i - 1]->tGetFitness().first) / p_max_objective_values.first);
	}//for (size_t i = 1; i + 1 < vParetoFront.size(); i++)
}//void CBinaryNSGA2Ranking::v_set_crowding_distance_first_objective(vector<CBinaryNSGA2Individual*> &vParetoFront)

void CBinaryNSGA2Ranking::v_set_crowding_distance_second_objective(vector<CBinaryNSGA2Individual*> &vParetoFront)
{
	sort(vParetoFront.begin(), vParetoFront.end(), [](CBinaryNSGA2Individual *pcIndividual0, CBinaryNSGA2Individual *pcIndividual1)
	{
		return pcIndividual0->tGetFitness().second < pcIndividual1->tGetFitness().second;
	});//sort(vParetoFront.begin(), vParetoFront.end(), [](CBinaryNSGA2Individual *pcIndividual0, CBinaryNSGA2Individual *pcIndividual1)

	vParetoFront.front()->vSetCrowdingDistance(vParetoFront.front()->dGetCrowdingDistance() + DBL_MAX / 2);
	vParetoFront.back()->vSetCrowdingDistance(vParetoFront.back()->dGetCrowdingDistance() + DBL_MAX / 2);

	for (size_t i = 1; i + 1 < vParetoFront.size(); i++)
	{
		vParetoFront[i]->vSetCrowdingDistance(vParetoFront[i]->dGetCrowdingDistance() + (vParetoFront[i + 1]->tGetFitness().second - vParetoFront[i - 1]->tGetFitness().second) / p_max_objective_values.second);
	}//for (size_t i = 1; i + 1 < vParetoFront.size(); i++)
}//void CBinaryNSGA2Ranking::v_set_crowding_distance_second_objective(vector<CBinaryNSGA2Individual*> &vParetoFront)