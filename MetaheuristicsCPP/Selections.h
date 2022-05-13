#pragma once

#include "Individual.h"
#include "Selection.h"

#include <numeric>
#include <random>
#include <vector>

using namespace Optimizers;

using namespace std;

namespace Selections
{
	template <typename TElement>
	class CTournamentSelection : public CSelection<TElement, double>
	{
	public:
		CTournamentSelection(int iTournamentSize, mt19937 &cRandomEngine)
			: CSelection<TElement, double>(cRandomEngine), i_tournament_size(iTournamentSize)
		{

		}//CTournamentSelection(int iTournamentSize, mt19937 &cRandomEngine)

	protected:
		virtual void v_add_to_new_population(vector<CIndividual<TElement, double>*> &vPopulation, vector<CIndividual<TElement, double>*> &vNewPopulation)
		{
			vector<size_t> v_indexes(vPopulation.size());
			iota(v_indexes.begin(), v_indexes.end(), 0);

			CIndividual<TElement, double> *pc_tournament_winner;

			for (size_t i = 0; i < vPopulation.size(); i++)
			{
				shuffle(v_indexes.begin(), v_indexes.end(), this->c_random_engine);

				pc_tournament_winner = pc_get_tournament_winner(vPopulation, v_indexes);

				vNewPopulation.push_back(new CIndividual<TElement, double>(*pc_tournament_winner));
			}//for (size_t i = 0; i < vPopulation.size(); i++)
		}//virtual void v_add_to_new_population(vector<CIndividual<TElement, double>*> &vPopulation, vector<CIndividual<TElement, double>*> &vNewPopulation)

	private:
		CIndividual<TElement, double> *pc_get_tournament_winner(vector<CIndividual<TElement, double>*> &vPopulation, vector<size_t> &vIndexes)
		{
			CIndividual<TElement, double> *pc_tournament_winner = vPopulation[vIndexes.front()];

			for (int i = 1; i < i_tournament_size; i++)
			{
				if (vPopulation[vIndexes[i]]->tGetFitness() > pc_tournament_winner->tGetFitness())
				{
					pc_tournament_winner = vPopulation[vIndexes[i]];
				}//if (vPopulation[vIndexes[i]]->tGetFitness() > pc_tournament_winner->tGetFitness())
			}//for (int i = 1; i < i_tournament_size; i++)

			return pc_tournament_winner;
		}//CIndividual<TElement, double> *pc_get_tournament_winner(vector<CIndividual<TElement, double>*> &vPopulation, vector<size_t> &vIndexes)

		int i_tournament_size;
	};//class CTournamentSelection : public CSelection<TElement, double>


	template <typename TElement>
	class CRouletteWheelSelection : public CSelection<TElement, double>
	{
	public:
		CRouletteWheelSelection(mt19937 &cRandomEngine)
			: CSelection<TElement, double>(cRandomEngine)
		{

		}//CRouletteWheelSelection(mt19937 &cRandomEngine)

	protected:
		virtual void v_add_to_new_population(vector<CIndividual<TElement, double>*> &vPopulation, vector<CIndividual<TElement, double>*> &vNewPopulation)
		{
			vector<double> v_cumulative_probabilites;
			
			v_fill_cumulative_probabilities(vPopulation, v_cumulative_probabilites);

			for (size_t i = 0; i < vPopulation.size(); i++)
			{
				vNewPopulation.push_back(new CIndividual<TElement, double>(*pc_single_roulette_wheel(vPopulation, v_cumulative_probabilites)));
			}//for (size_t i = 0; i < vPopulation.size(); i++)
		}//virtual void v_add_to_new_population(vector<CIndividual<TElement, double>*> &vPopulation, vector<CIndividual<TElement, double>*> &vNewPopulation)

	private:
		static double d_calculate_fitness_sum(vector<CIndividual<TElement, double>*> &vPopulation)
		{
			double d_fitness_sum = 0;

			for (size_t i = 0; i < vPopulation.size(); i++)
			{
				d_fitness_sum += vPopulation[i]->tGetFitness();
			}//for (size_t i = 0; i < vPopulation.size(); i++)

			return d_fitness_sum;
		}//static double d_calculate_fitness_sum(vector<CIndividual<TElement, double>*> &vPopulation)

		static void v_fill_cumulative_probabilities(vector<CIndividual<TElement, double>*> &vPopulation, vector<double> &vCumulativeProbabilites)
		{
			vCumulativeProbabilites.reserve(vPopulation.size());

			double d_fitness_sum = d_calculate_fitness_sum(vPopulation);

			double d_cumulative_probability = 0;

			for (size_t i = 0; i < vPopulation.size(); i++)
			{
				d_cumulative_probability += vPopulation[i]->tGetFitness() / d_fitness_sum;
				vCumulativeProbabilites.push_back(d_cumulative_probability);
			}//for (size_t i = 0; i < vPopulation.size(); i++)
		}//static void v_fill_cumulative_probabilities(vector<CIndividual<TElement, double>*> &vPopulation, vector<double> &vCumulativeProbabilites)

		CIndividual<TElement, double> *pc_single_roulette_wheel(vector<CIndividual<TElement, double>*> &vPopulation, vector<double> &vCumulativeProbabilites)
		{
			CIndividual<TElement, double> *pc_selected_individual = nullptr;

			uniform_real_distribution<double> c_selection_distr;

			double d_selection_value = c_selection_distr(this->c_random_engine);

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
		}//CIndividual<TElement, double> *pc_single_roulette_wheel(vector<CIndividual<TElement, double>*> &vPopulation, vector<double> &vCumulativeProbabilites)
	};//class CRouletteWheelSelection : public CSelection<TElement, double>
}//namespace Selections