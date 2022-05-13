#include "BinaryNSGA2.h"

using namespace Optimizers;

CBinaryNSGA2::CBinaryNSGA2(IEvaluation<bool, pair<double, double>> &cEvaluation, IStopCondition &cStopCondition, IGenerator<bool> &cGeneration, ICrossover<bool> &cCrossover, IMutation<bool> &cMutation, mt19937 &cRandomEngine, int iPopulationSize)
	: CGeneticAlgorithm<bool, pair<double, double>, CBiObjectiveOptimizationResult<bool>>(cEvaluation, cStopCondition, new CBiObjectiveOptimizationState<bool>(cEvaluation.tGetMaxValue(), cEvaluation.vGetOptimalParetoFront()), cGeneration, cCrossover, cMutation, c_selection, cRandomEngine, iPopulationSize), c_ranking(cEvaluation.tGetMaxValue(), c_domination_comparer), c_selection(2, c_ranking, cRandomEngine)
{

}//CBinaryNSGA2::CBinaryNSGA2(IEvaluation<bool, pair<double, double>> &cEvaluation, IStopCondition &cStopCondition, IGenerator<bool> &cGeneration, ICrossover<bool> &cCrossover, IMutation<bool> &cMutation, mt19937 &cRandomEngine, int iPopulationSize)

void CBinaryNSGA2::v_selection()
{
	for (size_t i = 0; i < pv_population->size(); i++)
	{
		c_ranking.vAdd(*pv_population->at(i));
	}//for (size_t i = 0; i < pv_population->size(); i++)

	v_clear_population();

	c_ranking.vUpdateRanking();
	c_ranking.vRemove(i_population_size);

	for (int i = 0; i < i_population_size; i++)
	{
		pv_population->push_back(c_ranking.vGetRanking()[i]);
	}//for (int i = 0; i < i_population_size; i++)

	c_selection.vSelect(&pv_population);
}//void CBinaryNSGA2::v_selection()