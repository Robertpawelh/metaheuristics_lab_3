#include "BinaryKnapsackSelections.h"

using namespace Selections;


CBinaryKnapsackTournamentSelection::CBinaryKnapsackTournamentSelection(int iTournamentSize, mt19937 &cRandomEngine)
	: CBinaryKnapsackSelection(cRandomEngine), i_tournament_size(iTournamentSize)
{

}//CBinaryKnapsackTournamentSelection::CBinaryKnapsackTournamentSelection(int iTournamentSize, mt19937 &cRandomEngine)

void CBinaryKnapsackTournamentSelection::v_add_to_new_population(vector<CBinaryKnapsackIndividual*> &vPopulation, vector<CBinaryKnapsackIndividual*> &vNewPopulation)
{
	vector<size_t> v_indexes(vPopulation.size());
	iota(v_indexes.begin(), v_indexes.end(), 0);

	CBinaryKnapsackIndividual *pc_tournament_winner;

	for (size_t i = 0; i < vPopulation.size(); i++)
	{
		shuffle(v_indexes.begin(), v_indexes.end(), c_random_engine);

		pc_tournament_winner = pc_get_tournament_winner(vPopulation, v_indexes);

		vNewPopulation.push_back(new CBinaryKnapsackIndividual(*pc_tournament_winner));
	}//for (size_t i = 0; i < vPopulation.size(); i++)
}//void CBinaryKnapsackTournamentSelection::v_add_to_new_population(vector<CBinaryKnapsackIndividual*> &vPopulation, vector<CBinaryKnapsackIndividual*> &vNewPopulation)

CBinaryKnapsackIndividual * CBinaryKnapsackTournamentSelection::pc_get_tournament_winner(vector<CBinaryKnapsackIndividual*> &vPopulation, vector<size_t> &vIndexes)
{
	CBinaryKnapsackIndividual *pc_tournament_winner = vPopulation[vIndexes.front()];

	for (int i = 1; i < i_tournament_size; i++)
	{
		if (vPopulation[vIndexes[i]]->dGetFitness() > pc_tournament_winner->dGetFitness())
		{
			pc_tournament_winner = vPopulation[vIndexes[i]];
		}//if (vPopulation[vIndexes[i]]->dGetFitness() > pc_tournament_winner->dGetFitness())
	}//for (int i = 1; i < i_tournament_size; i++)

	return pc_tournament_winner;
}//CBinaryKnapsackIndividual * CBinaryKnapsackTournamentSelection::pc_get_tournament_winner(vector<CBinaryKnapsackIndividual*> &vPopulation, vector<size_t> &vIndexes)


CBinaryKnapsackRouletteWheelSelection::CBinaryKnapsackRouletteWheelSelection(mt19937 &cRandomEngine)
	: CBinaryKnapsackSelection(cRandomEngine)
{

}//CBinaryKnapsackRouletteWheelSelection::CBinaryKnapsackRouletteWheelSelection(mt19937 &cRandomEngine)

void CBinaryKnapsackRouletteWheelSelection::v_add_to_new_population(vector<CBinaryKnapsackIndividual*> &vPopulation, vector<CBinaryKnapsackIndividual*> &vNewPopulation)
{
	vector<double> v_cumulative_probabilites;

	v_fill_cumulative_probabilities(vPopulation, v_cumulative_probabilites);

	for (size_t i = 0; i < vPopulation.size(); i++)
	{
		vNewPopulation.push_back(new CBinaryKnapsackIndividual(*pc_single_roulette_wheel(vPopulation, v_cumulative_probabilites)));
	}//for (size_t i = 0; i < vPopulation.size(); i++)
}//void CBinaryKnapsackRouletteWheelSelection::v_add_to_new_population(vector<CBinaryKnapsackIndividual*> &vPopulation, vector<CBinaryKnapsackIndividual*> &vNewPopulation)

double CBinaryKnapsackRouletteWheelSelection::d_calculate_fitness_sum(vector<CBinaryKnapsackIndividual*> &vPopulation)
{
	double d_fitness_sum = 0;

	for (size_t i = 0; i < vPopulation.size(); i++)
	{
		d_fitness_sum += vPopulation[i]->dGetFitness();
	}//for (size_t i = 0; i < vPopulation.size(); i++)

	return d_fitness_sum;
}//double CBinaryKnapsackRouletteWheelSelection::d_calculate_fitness_sum(vector<CBinaryKnapsackIndividual*> &vPopulation)

void CBinaryKnapsackRouletteWheelSelection::v_fill_cumulative_probabilities(vector<CBinaryKnapsackIndividual*> &vPopulation, vector<double> &vCumulativeProbabilites)
{
	vCumulativeProbabilites.reserve(vPopulation.size());

	double d_fitness_sum = d_calculate_fitness_sum(vPopulation);

	double d_cumulative_probability = 0;

	for (size_t i = 0; i < vPopulation.size(); i++)
	{
		d_cumulative_probability += vPopulation[i]->dGetFitness() / d_fitness_sum;
		vCumulativeProbabilites.push_back(d_cumulative_probability);
	}//for (size_t i = 0; i < vPopulation.size(); i++)
}//void CBinaryKnapsackRouletteWheelSelection::v_fill_cumulative_probabilities(vector<CBinaryKnapsackIndividual*> &vPopulation, vector<double> &vCumulativeProbabilites)

CBinaryKnapsackIndividual * CBinaryKnapsackRouletteWheelSelection::pc_single_roulette_wheel(vector<CBinaryKnapsackIndividual*> &vPopulation, vector<double> &vCumulativeProbabilites)
{
	CBinaryKnapsackIndividual *pc_selected_individual = nullptr;

	uniform_real_distribution<double> c_selection_distr;

	double d_selection_value = c_selection_distr(c_random_engine);

	for (size_t i = 0; i < vCumulativeProbabilites.size() && pc_selected_individual == nullptr; i++)
	{
		if (d_selection_value <= vCumulativeProbabilites[i])
		{
			pc_selected_individual = vPopulation[i];
		}//if (d_selection_value <= vCumulativeProbabilites[i])
	}//for (size_t i = 0; i < vCumulativeProbabilites.size() && pc_selected_individual == nullptr; i++)

	if (pc_selected_individual == nullptr)
	{
		pc_selected_individual = vPopulation.back();
	}//if (pc_selected_individual == nullptr)

	return pc_selected_individual;
}//CBinaryKnapsackIndividual * CBinaryKnapsackRouletteWheelSelection::pc_single_roulette_wheel(vector<CBinaryKnapsackIndividual*> &vPopulation, vector<double> &vCumulativeProbabilites)