#pragma once

#include "DominationComparer.h"
#include "Selection.h"

#include <utility>
#include <vector>

using namespace DominationComparers;

using namespace std;

namespace Selections
{
	template <typename TElement>
	class CSampleBiObjectiveSelection : public CSelection<TElement, pair<double, double>>
	{
	public:
		CSampleBiObjectiveSelection(IDominationComparer &cDominationComparer, mt19937 &cRandomEngine)
			: CSelection<TElement, pair<double, double>>(cRandomEngine), c_domination_comparer(cDominationComparer)
		{

		}//CSampleBiObjectiveSelection(IDominationComparer &cDominationComparer, mt19937 &cRandomEngine)

	protected:
		virtual void v_add_to_new_population(vector<CIndividual<TElement, pair<double, double>>*> &vPopulation, vector<CIndividual<TElement, pair<double, double>>*> &vNewPopulation)
		{
			vector<size_t> v_indexes(vPopulation.size());

			iota(v_indexes.begin(), v_indexes.end(), 0);
			shuffle(v_indexes.begin(), v_indexes.end(), this->c_random_engine);

			CIndividual<TElement, pair<double, double>> *pc_non_dominated_individual;

			for (size_t i = 0; i < vPopulation.size(); i++)
			{
				if (c_domination_comparer.iCompare(vPopulation[i]->tGetFitness(), vPopulation[v_indexes[i]]->tGetFitness()) >= 0)
				{
					pc_non_dominated_individual = vPopulation[i];
				}//if (c_domination_comparer.iCompare(vPopulation[i]->tGetFitness(), vPopulation[v_indexes[i]]->tGetFitness()) >= 0)
				else
				{
					pc_non_dominated_individual = vPopulation[v_indexes[i]];
				}//else if (c_domination_comparer.iCompare(vPopulation[i]->tGetFitness(), vPopulation[v_indexes[i]]->tGetFitness()) >= 0)

				vNewPopulation.push_back(new CIndividual<TElement, pair<double, double>>(*pc_non_dominated_individual));
			}//for (size_t i = 0; i < vPopulation.size(); i++)
		}//virtual void v_add_to_new_population(vector<CIndividual<TElement, pair<double, double>>*> &vPopulation, vector<CIndividual<TElement, pair<double, double>>*> &vNewPopulation)
	
	private:
		IDominationComparer &c_domination_comparer;
	};//class CSampleBiObjectiveSelection : public CSelection<TElement, vector<double>>
}//namespace Selections