#pragma once

#include "Crossover.h"
#include "GeneticAlgorithm.h"
#include "Mutation.h"
#include "Selection.h"
#include "SingleObjectiveOptimizationResult.h"
#include "SingleObjectiveOptimizationState.h"
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
	class CBinaryGeneticAlgorithm : public CGeneticAlgorithm<bool, double, CSingleObjectiveOptimizationResult<bool>>
	{
	public:
		CBinaryGeneticAlgorithm(IEvaluation<bool, double> &cEvaluation,
			IStopCondition &cStopCondition,
			IGenerator<bool> &cGeneration,
			ICrossover<bool> &cCrossover,
			IMutation<bool> &cMutation,
			ISelection<bool, double> &cSelection,
			mt19937 &cRandomEngine,
			int iPopulationSize);
	};//class CBinaryGeneticAlgorithm : public CGeneticAlgorithm<bool, double, CSingleObjectiveOptimizationResult<bool>>
}//namespace Optimizers