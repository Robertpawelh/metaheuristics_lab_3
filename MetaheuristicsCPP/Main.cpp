#include "BinaryBiObjectiveGeneticAlgorithm.h"
#include "BinaryCrossovers.h"
#include "BinaryGeneticAlgorithm.h"
#include "BinaryKnapsackGeneticAlgorithm.h"
#include "BinaryKnapsackSelections.h"
#include "BinaryMutations.h"
#include "BinaryNSGA2.h"
#include "BinaryRandomSearch.h"
#include "BiObjectiveOptimizationResult.h"
#include "BiObjectiveSelections.h"
#include "DominationComparers.h"
#include "RealCMAES.h"
#include "RealEvolutionStrategy11.h"
#include "RealMutations.h"
#include "RealMutationES11Adaptations.h"
#include "Selections.h"
#include "SingleObjectiveOptimizationResult.h"
#include "StopConditions.h"

#include <BinaryBiObjectiveEvaluations.h>
#include <BinaryEvaluationInstances.h>
#include <BinaryEvaluations.h>
#include <iostream>
#include <random>
#include <RealEvaluations.h>

using namespace Crossovers;
using namespace DominationComparers;
using namespace Mutations;
using namespace Optimizers;
using namespace Selections;
using namespace StopConditions;

using namespace Evaluations;
using namespace std;


template <typename TElement>
void v_report_optimization_result(CSingleObjectiveOptimizationResult<TElement> &cOptimizationResult)
{
	cout << "value: " << cOptimizationResult.dGetBestValue() << endl;
	cout << "\twhen (time): " << cOptimizationResult.dGetBestTime() << " s" << endl;
	cout << "\twhen (iteration): " << cOptimizationResult.iGetBestIteration() << endl;
	cout << "\twhen (FFE): " << cOptimizationResult.iGetBestFFE() << endl;
}//void v_report_optimization_result(CSingleObjectiveOptimizationResult<TElement> &cOptimizationResult)


template <typename TElement>
void v_report_bi_objective_optimization_result(CBiObjectiveOptimizationResult<TElement> &cBiObjectiveOptimizationResult)
{
	cout << "hyper volume: " << cBiObjectiveOptimizationResult.cGetParetoFront().dCalculateHyperVolume() << endl;
	cout << "IGD: " << cBiObjectiveOptimizationResult.cGetParetoFront().dCalculateInversedGenerationalDistance() << endl;
	cout << "\tlast update (time): " << cBiObjectiveOptimizationResult.dGetLastUpdateTime() << " s" << endl;
	cout << "\tlast update (iteration): " << cBiObjectiveOptimizationResult.iGetLastUpdateIteration() << endl;
	cout << "\tlast update (FFE): " << cBiObjectiveOptimizationResult.iGetLastUpdateFFE() << endl;
}//void v_report_bi_objective_optimization_result(CBiObjectiveOptimizationResult<TElement> &cBiObjectiveOptimizationResult)


void v_lab_9_zero_max_one_max_nsga2(mt19937 &cRandomEngine)
{
	CBinaryZeroMaxOneMaxEvaluation c_evaluation(10);
	CRunningTimeStopCondition c_stop_condition(5);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / c_evaluation.iGetSize(), c_evaluation, cRandomEngine);

	CBinaryNSGA2 c_nsga2(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, cRandomEngine, 100);

	c_nsga2.vRun();

	v_report_bi_objective_optimization_result(*c_nsga2.pcGetResult());
}//void v_lab_9_zero_max_one_max_nsga2(mt19937 &cRandomEngine)

void v_lab_9_trap_5_inv_trap_5_nsga2(mt19937 &cRandomEngine)
{
	CBinaryTrapInvTrapEvaluation c_evaluation(5, 10);
	CRunningTimeStopCondition c_stop_condition(5);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / c_evaluation.iGetSize(), c_evaluation, cRandomEngine);

	CBinaryNSGA2 c_nsga2(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, cRandomEngine, 100);

	c_nsga2.vRun();

	v_report_bi_objective_optimization_result(*c_nsga2.pcGetResult());
}//void v_lab_9_trap_5_inv_trap_5_nsga2(mt19937 &cRandomEngine)

void v_lab_9_lotz_nsga2(mt19937 &cRandomEngine)
{
	CBinaryLOTZEvaluation c_evaluation(10);
	CRunningTimeStopCondition c_stop_condition(5);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / c_evaluation.iGetSize(), c_evaluation, cRandomEngine);

	CBinaryNSGA2 c_nsga2(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, cRandomEngine, 100);

	c_nsga2.vRun();

	v_report_bi_objective_optimization_result(*c_nsga2.pcGetResult());
}//void v_lab_9_lotz_nsga2(mt19937 &cRandomEngine)

void v_lab_9_mo_max_cut_nsga2(mt19937 &cRandomEngine)
{
	CBinaryMOMaxCutEvaluation c_evaluation(EBinaryBiObjectiveMaxCutInstance::maxcut_instance_6);
	CRunningTimeStopCondition c_stop_condition(5);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / c_evaluation.iGetSize(), c_evaluation, cRandomEngine);

	CBinaryNSGA2 c_nsga2(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, cRandomEngine, 100);

	c_nsga2.vRun();

	v_report_bi_objective_optimization_result(*c_nsga2.pcGetResult());
}//void v_lab_9_mo_max_cut_nsga2(mt19937 &cRandomEngine)

void v_lab_9_mo_knapsack_nsga2(mt19937 &cRandomEngine)
{
	CBinaryMOKnapsackEvaluation c_evaluation(EBinaryBiObjectiveKnapsackInstance::knapsack_100);
	CRunningTimeStopCondition c_stop_condition(5);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / c_evaluation.iGetSize(), c_evaluation, cRandomEngine);

	CBinaryNSGA2 c_nsga2(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, cRandomEngine, 100);

	c_nsga2.vRun();

	v_report_bi_objective_optimization_result(*c_nsga2.pcGetResult());
}//void v_lab_9_mo_knapsack_nsga2(mt19937 &cRandomEngine)


void v_lab_8_zero_max_one_max(mt19937 &cRandomEngine)
{
	CBinaryZeroMaxOneMaxEvaluation c_evaluation(10);
	CRunningTimeStopCondition c_stop_condition(5);

	CDefaultDominationComparer c_domination_comparer;

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / c_evaluation.iGetSize(), c_evaluation, cRandomEngine);
	CSampleBiObjectiveSelection<bool> c_selection(c_domination_comparer, cRandomEngine);

	CBinaryBiObjectiveGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 100);

	c_ga.vRun();

	v_report_bi_objective_optimization_result(*c_ga.pcGetResult());
}//void v_lab_8_zero_max_one_max(mt19937 &cRandomEngine)

void v_lab_8_trap_5_inv_trap_5(mt19937 &cRandomEngine)
{
	CBinaryTrapInvTrapEvaluation c_evaluation(5, 10);
	CRunningTimeStopCondition c_stop_condition(5);

	CDefaultDominationComparer c_domination_comparer;

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / c_evaluation.iGetSize(), c_evaluation, cRandomEngine);
	CSampleBiObjectiveSelection<bool> c_selection(c_domination_comparer, cRandomEngine);

	CBinaryBiObjectiveGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 100);

	c_ga.vRun();

	v_report_bi_objective_optimization_result(*c_ga.pcGetResult());
}//void v_lab_8_trap_5_inv_trap_5(mt19937 &cRandomEngine)

void v_lab_8_lotz(mt19937 &cRandomEngine)
{
	CBinaryLOTZEvaluation c_evaluation(10);
	CRunningTimeStopCondition c_stop_condition(5);

	CDefaultDominationComparer c_domination_comparer;

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / c_evaluation.iGetSize(), c_evaluation, cRandomEngine);
	CSampleBiObjectiveSelection<bool> c_selection(c_domination_comparer, cRandomEngine);

	CBinaryBiObjectiveGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 100);

	c_ga.vRun();

	v_report_bi_objective_optimization_result(*c_ga.pcGetResult());
}//void v_lab_8_trap_5_inv_trap_5(mt19937 &cRandomEngine)

void v_lab_8_mo_max_cut(mt19937 &cRandomEngine)
{
	CBinaryMOMaxCutEvaluation c_evaluation(EBinaryBiObjectiveMaxCutInstance::maxcut_instance_6);
	CRunningTimeStopCondition c_stop_condition(5);

	CDefaultDominationComparer c_domination_comparer;

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / c_evaluation.iGetSize(), c_evaluation, cRandomEngine);
	CSampleBiObjectiveSelection<bool> c_selection(c_domination_comparer, cRandomEngine);

	CBinaryBiObjectiveGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 100);

	c_ga.vRun();

	v_report_bi_objective_optimization_result(*c_ga.pcGetResult());
}//void v_lab_8_mo_max_cut(mt19937 &cRandomEngine)

void v_lab_8_mo_knapsack(mt19937 &cRandomEngine)
{
	CBinaryMOKnapsackEvaluation c_evaluation(EBinaryBiObjectiveKnapsackInstance::knapsack_100);
	CRunningTimeStopCondition c_stop_condition(5);

	CDefaultDominationComparer c_domination_comparer;

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / c_evaluation.iGetSize(), c_evaluation, cRandomEngine);
	CSampleBiObjectiveSelection<bool> c_selection(c_domination_comparer, cRandomEngine);

	CBinaryBiObjectiveGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 100);

	c_ga.vRun();

	v_report_bi_objective_optimization_result(*c_ga.pcGetResult());
}//void v_lab_8_mo_knapsack(mt19937 &cRandomEngine)


void v_lab_5(mt19937 &cRandomEngine)
{
	CBinaryKnapsackEvaluation c_evaluation(EBinaryKnapsackInstance::knapPI_1_100_1000_1);
	CIterationsStopCondition c_stop_condition(100);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / c_evaluation.iGetSize(), c_evaluation, cRandomEngine);
	CBinaryKnapsackTournamentSelection c_selection(2, cRandomEngine);

	CBinaryKnapsackGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 50);

	c_ga.vRun();

	v_report_optimization_result(*c_ga.pcGetResult());
}//void v_lab_5(mt19937 &cRandomEngine)


void v_lab_4_max_3_sat(mt19937 &cRandomEngine)
{
	CBinaryMax3SatEvaluation c_evaluation(100);
	CIterationsStopCondition c_stop_condition(100);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / c_evaluation.iGetSize(), c_evaluation, cRandomEngine);
	CTournamentSelection<bool> c_selection(2, cRandomEngine);

	CBinaryGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 50);

	c_ga.vRun();

	v_report_optimization_result(*c_ga.pcGetResult());
}//void v_lab_4_max_3_sat(mt19937 &cRandomEngine)

void v_lab_4_trap_tournament_selection_one_point_crossover(mt19937 &cRandomEngine)
{
	CBinaryStandardDeceptiveConcatenationEvaluation c_evaluation(3, 50);
	CIterationsStopCondition c_stop_condition(100);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryOnePointCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / c_evaluation.iGetSize(), c_evaluation, cRandomEngine);
	CTournamentSelection<bool> c_selection(2, cRandomEngine);

	CBinaryGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 50);

	c_ga.vRun();

	v_report_optimization_result(*c_ga.pcGetResult());
}//void v_lab_4_trap_tournament_selection_one_point_crossover(mt19937 &cRandomEngine)

void v_lab_4_trap_roulette_wheel_selection_uniform_crossover(mt19937 &cRandomEngine)
{
	CBinaryStandardDeceptiveConcatenationEvaluation c_evaluation(3, 50);
	CIterationsStopCondition c_stop_condition(100);

	CBinaryRandomGenerator c_generation(c_evaluation.cGetConstraint(), cRandomEngine);
	CBinaryUniformCrossover c_crossover(0.5, cRandomEngine);
	CBinaryBitFlipMutation c_mutation(1.0 / c_evaluation.iGetSize(), c_evaluation, cRandomEngine);
	CRouletteWheelSelection<bool> c_selection(cRandomEngine);

	CBinaryGeneticAlgorithm c_ga(c_evaluation, c_stop_condition, c_generation, c_crossover, c_mutation, c_selection, cRandomEngine, 50);

	c_ga.vRun();

	v_report_optimization_result(*c_ga.pcGetResult());
}//void v_lab_4_trap_roulette_wheel_selection_uniform_crossover(mt19937 &cRandomEngine)


void v_lab_3_sphere_cmaes(mt19937 &cRandomEngine)
{
	CRealSphereEvaluation c_sphere_evaluation(10);

	CIterationsStopCondition c_stop_condition(1000);

	CRealCMAES c_cmaes(c_sphere_evaluation, c_stop_condition, cRandomEngine, 1);

	c_cmaes.vRun();

	v_report_optimization_result(*c_cmaes.pcGetResult());
}//void v_lab_3_sphere_cmaes(mt19937 &cRandomEngine)

void v_lab_3_sphere_10_cmaes(mt19937 &cRandomEngine)
{
	CRealSphere10Evaluation c_sphere_10_evaluation(10);

	CIterationsStopCondition c_stop_condition(1000);

	CRealCMAES c_cmaes(c_sphere_10_evaluation, c_stop_condition, cRandomEngine, 1);

	c_cmaes.vRun();

	v_report_optimization_result(*c_cmaes.pcGetResult());
}//void v_lab_3_sphere_cmaes(mt19937 &cRandomEngine)

void v_lab_3_ellipsoid_cmaes(mt19937 &cRandomEngine)
{
	CRealEllipsoidEvaluation c_ellipsoid_evaluation(10);

	CIterationsStopCondition c_stop_condition(1000);

	CRealCMAES c_cmaes(c_ellipsoid_evaluation, c_stop_condition, cRandomEngine, 1);

	c_cmaes.vRun();

	v_report_optimization_result(*c_cmaes.pcGetResult());
}//void v_lab_3_ellipsoid_cmaes(mt19937 &cRandomEngine)

void v_lab_3_step_2_sphere_cmaes(mt19937 &cRandomEngine)
{
	CRealStep2SphereEvaluation c_step_2_sphere_evaluation(10);

	CIterationsStopCondition c_stop_condition(1000);

	CRealCMAES c_cmaes(c_step_2_sphere_evaluation, c_stop_condition, cRandomEngine, 1);

	c_cmaes.vRun();

	v_report_optimization_result(*c_cmaes.pcGetResult());
}//void v_lab_3_step_2_sphere_cmaes(mt19937 &cRandomEngine)

void v_lab_3_rastrigin_cmaes(mt19937 &cRandomEngine)
{
	CRealRastriginEvaluation c_rastrigin_evaluation(10);

	CIterationsStopCondition c_stop_condition(1000);

	CRealCMAES c_cmaes(c_rastrigin_evaluation, c_stop_condition, cRandomEngine, 1);

	c_cmaes.vRun();

	v_report_optimization_result(*c_cmaes.pcGetResult());
}//void v_lab_3_rastrigin_cmaes(mt19937 &cRandomEngine)

void v_lab_3_ackley_cmaes(mt19937 &cRandomEngine)
{
	CRealAckleyEvaluation c_ackley_evaluation(10);

	CIterationsStopCondition c_stop_condition(1000);

	CRealCMAES c_cmaes(c_ackley_evaluation, c_stop_condition, cRandomEngine, 1);

	c_cmaes.vRun();

	v_report_optimization_result(*c_cmaes.pcGetResult());
}//void v_lab_3_ackley_cmaes(mt19937 &cRandomEngine)


void v_lab_2_sphere(mt19937 &cRandomEngine)
{
	CRealSphereEvaluation c_sphere_evaluation(2);

	vector<double> v_sigmas((size_t)c_sphere_evaluation.iGetSize(), 0.1);

	CIterationsStopCondition c_stop_condition(1000);
	CRealGaussianMutation c_mutation(v_sigmas, c_sphere_evaluation, cRandomEngine);
	CRealNullRealMutationES11Adaptation c_mutation_adaptation(c_mutation);

	CRealEvolutionStrategy11 c_es11(c_sphere_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	v_report_optimization_result(*c_es11.pcGetResult());
}//void v_lab_2_sphere(mt19937 &cRandomEngine)

void v_lab_2_sphere_10(mt19937 &cRandomEngine)
{
	CRealSphere10Evaluation c_sphere_10_evaluation(2);

	vector<double> v_sigmas((size_t)c_sphere_10_evaluation.iGetSize(), 0.1);

	CIterationsStopCondition c_stop_condition(1000);
	CRealGaussianMutation c_mutation(v_sigmas, c_sphere_10_evaluation, cRandomEngine);
	CRealNullRealMutationES11Adaptation c_mutation_adaptation(c_mutation);

	CRealEvolutionStrategy11 c_es11(c_sphere_10_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	v_report_optimization_result(*c_es11.pcGetResult());
}//void v_lab_2_sphere_10(mt19937 &cRandomEngine)

void v_lab_2_ellipsoid(mt19937 &cRandomEngine)
{
	CRealEllipsoidEvaluation c_ellipsoid_evaluation(2);

	vector<double> v_sigmas((size_t)c_ellipsoid_evaluation.iGetSize(), 1);

	CIterationsStopCondition c_stop_condition(1000);
	CRealGaussianMutation c_mutation(v_sigmas, c_ellipsoid_evaluation, cRandomEngine);
	CRealNullRealMutationES11Adaptation c_mutation_adaptation(c_mutation);

	CRealEvolutionStrategy11 c_es11(c_ellipsoid_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	v_report_optimization_result(*c_es11.pcGetResult());
}//void v_lab_2_ellipsoid(mt19937 &cRandomEngine)

void v_lab_2_step_2_sphere(mt19937 &cRandomEngine)
{
	CRealStep2SphereEvaluation c_step_2_sphere_evaluation(2);

	vector<double> v_sigmas((size_t)c_step_2_sphere_evaluation.iGetSize(), 0.1);

	CIterationsStopCondition c_stop_condition(1000);
	CRealGaussianMutation c_mutation(v_sigmas, c_step_2_sphere_evaluation, cRandomEngine);
	CRealNullRealMutationES11Adaptation c_mutation_adaptation(c_mutation);

	CRealEvolutionStrategy11 c_es11(c_step_2_sphere_evaluation, c_stop_condition, c_mutation_adaptation, cRandomEngine);

	c_es11.vRun();

	v_report_optimization_result(*c_es11.pcGetResult());
}//void v_lab_2_step_2_sphere(mt19937 &cRandomEngine)


void v_lab_1_one_max(mt19937 &cRandomEngine)
{
	CBinaryOneMaxEvaluation c_evaluation(5);
	CIterationsStopCondition c_stop_condition(500);
	CBinaryRandomSearch c_random_search(c_evaluation, c_stop_condition, cRandomEngine);

	c_random_search.vRun();

	v_report_optimization_result(*c_random_search.pcGetResult());
}//void v_lab_1_one_max(mt19937 &cRandomEngine)

void v_lab_1_standard_deceptive_concatenation(mt19937 &cRandomEngine)
{
	CBinaryStandardDeceptiveConcatenationEvaluation c_evaluation(5, 1);
	CIterationsStopCondition c_stop_condition(500);
	CBinaryRandomSearch c_random_search(c_evaluation, c_stop_condition, cRandomEngine);

	c_random_search.vRun();

	v_report_optimization_result(*c_random_search.pcGetResult());
}//void v_lab_1_standard_deceptive_concatenation(mt19937 &cRandomEngine)

void v_lab_1_bimodal_deceptive_concatenation(mt19937 &cRandomEngine)
{
	CBinaryBimodalDeceptiveConcatenationEvaluation c_evaluation(10, 1);
	CIterationsStopCondition c_stop_condition(500);
	CBinaryRandomSearch c_random_search(c_evaluation, c_stop_condition, cRandomEngine);

	c_random_search.vRun();

	v_report_optimization_result(*c_random_search.pcGetResult());
}//void v_lab_1_bimodal_deceptive_concatenation(mt19937 &cRandomEngine)

void v_lab_1_ising_spin_glass(mt19937 &cRandomEngine)
{
	CBinaryIsingSpinGlassEvaluation c_evaluation(25);
	CIterationsStopCondition c_stop_condition(500);
	CBinaryRandomSearch c_random_search(c_evaluation, c_stop_condition, cRandomEngine);

	c_random_search.vRun();

	v_report_optimization_result(*c_random_search.pcGetResult());
}//void v_lab_1_ising_spin_glass(mt19937 &cRandomEngine)

void v_lab_1_nk_landscapes(mt19937 &cRandomEngine)
{
	CBinaryNKLandscapesEvaluation c_evaluation(10);
	CIterationsStopCondition c_stop_condition(500);
	CBinaryRandomSearch c_random_search(c_evaluation, c_stop_condition, cRandomEngine);

	c_random_search.vRun();

	v_report_optimization_result(*c_random_search.pcGetResult());
}//void v_lab_1_nk_landscapes(mt19937 &cRandomEngine)


int main()
{
	random_device c_seed_generator;
	mt19937 c_random_engine(c_seed_generator());

	v_lab_9_zero_max_one_max_nsga2(c_random_engine);
	v_lab_9_trap_5_inv_trap_5_nsga2(c_random_engine);
	v_lab_9_lotz_nsga2(c_random_engine);
	v_lab_9_mo_max_cut_nsga2(c_random_engine);
	v_lab_9_mo_knapsack_nsga2(c_random_engine);
	
	v_lab_8_zero_max_one_max(c_random_engine);
	v_lab_8_trap_5_inv_trap_5(c_random_engine);
	v_lab_8_lotz(c_random_engine);
	v_lab_8_mo_max_cut(c_random_engine);
	v_lab_8_mo_knapsack(c_random_engine);

	v_lab_5(c_random_engine);

	v_lab_4_max_3_sat(c_random_engine);
	v_lab_4_trap_tournament_selection_one_point_crossover(c_random_engine);
	v_lab_4_trap_roulette_wheel_selection_uniform_crossover(c_random_engine);

	v_lab_3_sphere_cmaes(c_random_engine);
	v_lab_3_sphere_10_cmaes(c_random_engine);
	v_lab_3_ellipsoid_cmaes(c_random_engine);
	v_lab_3_step_2_sphere_cmaes(c_random_engine);
	v_lab_3_rastrigin_cmaes(c_random_engine);
	v_lab_3_ackley_cmaes(c_random_engine);

	v_lab_2_sphere(c_random_engine);
	v_lab_2_sphere_10(c_random_engine);
	v_lab_2_ellipsoid(c_random_engine);
	v_lab_2_step_2_sphere(c_random_engine);

	v_lab_1_one_max(c_random_engine);
	v_lab_1_standard_deceptive_concatenation(c_random_engine);
	v_lab_1_bimodal_deceptive_concatenation(c_random_engine);
	v_lab_1_ising_spin_glass(c_random_engine);
	v_lab_1_nk_landscapes(c_random_engine);

	return 0;
}//int main()