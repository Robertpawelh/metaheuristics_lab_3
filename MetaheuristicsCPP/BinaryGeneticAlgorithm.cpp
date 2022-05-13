#include "BinaryGeneticAlgorithm.h"

using namespace Optimizers;

CBinaryGeneticAlgorithm::CBinaryGeneticAlgorithm(IEvaluation<bool, double> &cEvaluation, IStopCondition &cStopCondition, IGenerator<bool> &cGeneration, ICrossover<bool> &cCrossover, IMutation<bool> &cMutation, ISelection<bool, double> &cSelection, mt19937 &cRandomEngine, int iPopulationSize)
	: CGeneticAlgorithm<bool, double, CSingleObjectiveOptimizationResult<bool>>(cEvaluation, cStopCondition, new CSingleObjectiveOptimizationState<bool>(cEvaluation.tGetMaxValue()), cGeneration, cCrossover, cMutation, cSelection, cRandomEngine, iPopulationSize)
{

}//CBinaryGeneticAlgorithm::CBinaryGeneticAlgorithm(IEvaluation<bool, double> &cEvaluation, IStopCondition &cStopCondition, IGenerator<bool> &cGeneration, ICrossover<bool> &cCrossover, IMutation<bool> &cMutation, ISelection<bool, double> &cSelection, mt19937 &cRandomEngine, int iPopulationSize)
