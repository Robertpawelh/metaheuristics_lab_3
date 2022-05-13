#pragma once

#include "BinaryKnapsackSelection.h"
#include "Individual.h"

#include <numeric>
#include <random>
#include <vector>

using namespace Optimizers;

using namespace std;

namespace Selections
{
	class CBinaryKnapsackTournamentSelection : public CBinaryKnapsackSelection
	{
	public:
		CBinaryKnapsackTournamentSelection(int iTournamentSize, mt19937 &cRandomEngine);

	protected:
		virtual void v_add_to_new_population(vector<CBinaryKnapsackIndividual*> &vPopulation, vector<CBinaryKnapsackIndividual*> &vNewPopulation);

	private:
		CBinaryKnapsackIndividual *pc_get_tournament_winner(vector<CBinaryKnapsackIndividual*> &vPopulation, vector<size_t> &vIndexes);

		int i_tournament_size;
	};//class CTournamentSelection : public CSelection<TElement>


	class CBinaryKnapsackRouletteWheelSelection : public CBinaryKnapsackSelection
	{
	public:
		CBinaryKnapsackRouletteWheelSelection(mt19937 &cRandomEngine);

	protected:
		virtual void v_add_to_new_population(vector<CBinaryKnapsackIndividual*> &vPopulation, vector<CBinaryKnapsackIndividual*> &vNewPopulation);

	private:
		static double d_calculate_fitness_sum(vector<CBinaryKnapsackIndividual*> &vPopulation);

		static void v_fill_cumulative_probabilities(vector<CBinaryKnapsackIndividual*> &vPopulation, vector<double> &vCumulativeProbabilites);

		CBinaryKnapsackIndividual *pc_single_roulette_wheel(vector<CBinaryKnapsackIndividual*> &vPopulation, vector<double> &vCumulativeProbabilites);
	};//class CRouletteWheelSelection : public CSelection<TElement>
}//namespace Selections#pragma once
