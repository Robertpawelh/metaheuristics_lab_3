#include "BinaryBiObjectiveGeneticAlgorithm.h"

using namespace Optimizers;

CBinaryBiObjectiveGeneticAlgorithm::CBinaryBiObjectiveGeneticAlgorithm(IEvaluation<bool, pair<double, double>> &cEvaluation, IStopCondition &cStopCondition, IGenerator<bool> &cGeneration, ICrossover<bool> &cCrossover, IMutation<bool> &cMutation, ISelection<bool, pair<double, double>> &cSelection, mt19937 &cRandomEngine, int iPopulationSize)
	: CGeneticAlgorithm<bool, pair<double, double>, CBiObjectiveOptimizationResult<bool>>(cEvaluation, cStopCondition, new CBiObjectiveOptimizationState<bool>(cEvaluation.tGetMaxValue(), cEvaluation.vGetOptimalParetoFront()), cGeneration, cCrossover, cMutation, cSelection, cRandomEngine, iPopulationSize)
{

}//CBinaryBiObjectiveGeneticAlgorithm::CBinaryBiObjectiveGeneticAlgorithm(IEvaluation<bool, pair<double, double>> &cEvaluation, IStopCondition &cStopCondition, IGenerator<bool> &cGeneration, ICrossover<bool> &cCrossover, IMutation<bool> &cMutation, ISelection<bool, pair<double, double>> &cSelection, mt19937 &cRandomEngine, int iPopulationSize)