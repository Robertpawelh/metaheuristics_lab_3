#pragma once

#include "Crossover.h"
#include "Mutation.h"
#include "OptimizationState.h"
#include "PopulationOptimizer.h"
#include "Selection.h"
#include "StopCondition.h"

#include <algorithm>
#include <ctime>
#include <numeric>
#include <random>

using namespace Crossovers;
using namespace Mutations;
using namespace Selections;
using namespace StopConditions;

namespace Optimizers
{
	template <typename TElement, typename TEvaluationResult, class TOptimizationResult>
	class CGeneticAlgorithm : public CPopulationOptimizer<TElement, TEvaluationResult, TOptimizationResult>
	{
	public:
		CGeneticAlgorithm(IEvaluation<TElement, TEvaluationResult> &cEvaluation,
			IStopCondition &cStopCondition,
			IOptimizationState<TElement, TEvaluationResult, TOptimizationResult> *pcState,
			IGenerator<TElement> &cGeneration,
			ICrossover<TElement> &cCrossover,
			IMutation<TElement> &cMutation,
			ISelection<TElement, TEvaluationResult> &cSelection,
			mt19937 &cRandomEngine,
			int iPopulationSize)
			: CPopulationOptimizer<TElement, TEvaluationResult, TOptimizationResult>(cEvaluation, cStopCondition, pcState, cGeneration, cSelection, cMutation, iPopulationSize), c_crossover(cCrossover), c_random_engine(cRandomEngine)
		{

		}//CGeneticAlgorithm(IEvaluation<TElement, TEvaluationResult> &cEvaluation,

	protected:
		virtual bool b_run_iteration(long long iIterationNumber, clock_t tStartTime)
		{
			this->v_selection();

			this->v_crossover();
			this->v_evaluation();

			bool b_updated = this->b_update_state();

			this->v_mutation();
			this->v_evaluation();

			return this->b_update_state() || b_updated;
		}//virtual bool b_run_iteration(long long iIterationNumber, clock_t tStartTime)

		virtual void v_crossover()
		{
			vector<size_t> v_indexes(this->pv_population->size());

			iota(v_indexes.begin(), v_indexes.end(), 0);
			shuffle(v_indexes.begin(), v_indexes.end(), c_random_engine);

			CIndividual<TElement, TEvaluationResult> *pc_parent_0, *pc_parent_1, *pc_child_0, *pc_child_1;
			vector<TElement> *pv_child_0_genotype, *pv_child_1_genotype;

			size_t i_index_0, i_index_1;

			for (size_t i = 0; i + 1 < this->pv_population->size(); i += 2)
			{
				i_index_0 = v_indexes[i + 0];
				i_index_1 = v_indexes[i + 1];

				pc_parent_0 = this->pv_population->at(i_index_0);
				pc_parent_1 = this->pv_population->at(i_index_1);

				pv_child_0_genotype = new vector<TElement>((size_t)this->c_evaluation.iGetSize());
				pv_child_1_genotype = new vector<TElement>((size_t)this->c_evaluation.iGetSize());

				if (c_crossover.bCross(pc_parent_0->vGetGenotype(), pc_parent_1->vGetGenotype(), *pv_child_0_genotype, *pv_child_1_genotype))
				{
					delete pc_parent_0;
					delete pc_parent_1;

					pc_child_0 = this->pc_create_individual(pv_child_0_genotype);
					pc_child_1 = this->pc_create_individual(pv_child_1_genotype);

					this->pv_population->at(i_index_0) = pc_child_0;
					this->pv_population->at(i_index_1) = pc_child_1;
				}//if (c_crossover.bCross(pc_parent_0->vGetGenotype(), pc_parent_1->vGetGenotype(), *pv_child_0_genotype, *pv_child_1_genotype))
				else
				{
					delete pv_child_0_genotype;
					delete pv_child_1_genotype;
				}//else if (c_crossover.bCross(pc_parent_0->vGetGenotype(), pc_parent_1->vGetGenotype(), *pv_child_0_genotype, *pv_child_1_genotype))
			}//for (size_t i = 0; i + 1 < this->pv_population->size(); i += 2)
		}//virtual void v_crossover()

		ICrossover<TElement> &c_crossover;

		mt19937 &c_random_engine;
	};//class CGeneticAlgorithm : public CPopulationOptimizer<TElement, TEvaluationResult, TOptimizationResult>
}//namespace Optimizers
