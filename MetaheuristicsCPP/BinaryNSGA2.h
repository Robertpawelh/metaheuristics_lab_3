#pragma once

#include "BinaryNSGA2Ranking.h"
#include "BinaryNSGA2Selection.h"
#include "BiObjectiveOptimizationResult.h"
#include "BiObjectiveOptimizationState.h"
#include "Crossover.h"
#include "DominationComparers.h"
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
using namespace DominationComparers;
using namespace Mutations;
using namespace Selections;
using namespace StopConditions;

namespace Optimizers
{
	class CBinaryNSGA2 : public CGeneticAlgorithm<bool, pair<double, double>, CBiObjectiveOptimizationResult<bool>>
	{
	public:
		CBinaryNSGA2(IEvaluation<bool, pair<double, double>> &cEvaluation,
			IStopCondition &cStopCondition,
			IGenerator<bool> &cGeneration,
			ICrossover<bool> &cCrossover,
			IMutation<bool> &cMutation,
			mt19937 &cRandomEngine,
			int iPopulationSize);

	protected:
		virtual void v_selection();

	private:
		CDefaultDominationComparer c_domination_comparer;
		CBinaryNSGA2Selection c_selection;
		CBinaryNSGA2Ranking c_ranking;
	};//class CBinaryNSGA2 : public CGeneticAlgorithm<bool, pair<double, double>, CBiObjectiveOptimizationResult<bool>>
}//namespace Optimizers