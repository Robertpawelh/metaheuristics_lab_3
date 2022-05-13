#pragma once

#include "BiObjectiveOptimizationResult.h"
#include "BiObjectiveOptimizationState.h"
#include "Crossover.h"
#include "GeneticAlgorithm.h"
#include "Mutation.h"
#include "Selection.h"
#include "StopCondition.h"

#include <algorithm>
#include <ctime>
#include <numeric>
#include <random>
#include <utility>

using namespace Crossovers;
using namespace Mutations;
using namespace Selections;
using namespace StopConditions;

namespace Optimizers
{
	class CBinaryBiObjectiveGeneticAlgorithm : public CGeneticAlgorithm<bool, pair<double, double>, CBiObjectiveOptimizationResult<bool>>
	{
	public:
		CBinaryBiObjectiveGeneticAlgorithm(IEvaluation<bool, pair<double, double>> &cEvaluation,
			IStopCondition &cStopCondition,
			IGenerator<bool> &cGeneration,
			ICrossover<bool> &cCrossover,
			IMutation<bool> &cMutation,
			ISelection<bool, pair<double, double>> &cSelection,
			mt19937 &cRandomEngine,
			int iPopulationSize);
	};//class CBinaryBiObjectiveGeneticAlgorithm : public CGeneticAlgorithm<bool, pair<double, double>, CBiObjectiveOptimizationResult<bool>>
}//namespace Optimizers