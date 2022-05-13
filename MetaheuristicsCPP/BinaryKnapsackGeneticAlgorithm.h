#pragma once

#include "BinaryKnapsackIndividual.h"
#include "BinaryKnapsackSelection.h"
#include "Crossover.h"
#include "Mutation.h"
#include "PopulationOptimizer.h"
#include "SingleObjectiveOptimizationResult.h"
#include "SingleObjectiveOptimizationState.h"
#include "StopCondition.h"
#include "VectorUtils.h"

#include <algorithm>
#include <BinaryEvaluations.h>
#include <ctime>
#include <numeric>
#include <random>

using namespace Crossovers;
using namespace Evaluations;
using namespace Mutations;
using namespace Selections;
using namespace StopConditions;

namespace Optimizers
{
	class CBinaryKnapsackGeneticAlgorithm : public COptimizer<bool, double, CSingleObjectiveOptimizationResult<bool>>
	{
	public:
		CBinaryKnapsackGeneticAlgorithm(CBinaryKnapsackEvaluation &cBinaryKnapsackEvaluation,
			IStopCondition &cStopCondition,
			IGenerator<bool> &cGenerator,
			ICrossover<bool> &cCrossover,
			IMutation<bool> &cMutation,
			IBinaryKnapsackSelection &cBinaryKnapsackSelection,
			mt19937 &cRandomEngine,
			int iPopulationSize);

		virtual ~CBinaryKnapsackGeneticAlgorithm();

	protected:
		virtual void v_initialize(clock_t tStartTime);
		virtual bool b_run_iteration(long long iIterationNumber, clock_t tStartTime);

	private:
		void v_evaluation();

		void v_selection();
		void v_crossover();
		void v_mutation();

		bool b_update_state(bool bOnlyImprovements = true);

		CBinaryKnapsackIndividual *pc_create_individual(vector<bool> *pvGenotype = nullptr);

		CBinaryKnapsackEvaluation &c_binary_knapsack_evaluation;

		int i_population_size;
		vector<CBinaryKnapsackIndividual*> *pv_population;

		IGenerator<bool> &c_generator;
		IBinaryKnapsackSelection &c_binary_knapsack_selection;
		ICrossover<bool> &c_crossover;
		IMutation<bool> &c_mutation;

		mt19937 &c_random_engine;
	};//class CBinaryKnapsackGeneticAlgorithm : public COptimizer<bool, double, CSingleObjectiveOptimizationResult<bool>>
}//namespace Optimizers