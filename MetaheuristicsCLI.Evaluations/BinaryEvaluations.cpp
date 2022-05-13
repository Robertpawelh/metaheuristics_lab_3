#include "BinaryEvaluations.h"

using namespace EvaluationsCLI;


CBinaryEvaluation::CBinaryEvaluation(Evaluations::IEvaluation<bool, double> *pcNativeBinaryEvaluation)
{
	pc_native_binary_evaluation = pcNativeBinaryEvaluation;

	l_optimal_pareto_front = gcnew List<double>((int)pc_native_binary_evaluation->vGetOptimalParetoFront().size());

	for (size_t i = 0; i < pc_native_binary_evaluation->vGetOptimalParetoFront().size(); i++)
	{
		l_optimal_pareto_front->Add(*pc_native_binary_evaluation->vGetOptimalParetoFront()[i]);
	}//for (size_t i = 0; i < pc_native_binary_evaluation->vGetOptimalParetoFront().size(); i++)
}//CBinaryEvaluation::CBinaryEvaluation(Evaluations::IEvaluation<bool, double> *pcNativeBinaryEvaluation)

CBinaryEvaluation::~CBinaryEvaluation()
{
	delete pc_native_binary_evaluation;
}//CBinaryEvaluation::~CBinaryEvaluation()

CBinaryEvaluation::!CBinaryEvaluation()
{
	delete pc_native_binary_evaluation;
}//CBinaryEvaluation::!CBinaryEvaluation()

double CBinaryEvaluation::tEvaluate(IList<bool> ^lSolution)
{
	vector<bool> v_solution(0);
	v_solution.reserve(lSolution->Count);

	for (int i = 0; i < lSolution->Count; i++)
	{
		v_solution.push_back(lSolution[i]);
	}//for (int i = 0; i < lSolution->Count; i++)

	return pc_native_binary_evaluation->tEvaluate(v_solution);
}//double CBinaryEvaluation::tEvaluate(IList<bool> ^lSolution) 


CBinaryOneMaxEvaluation::CBinaryOneMaxEvaluation(int iSize)
	: CBinaryEvaluation(new Evaluations::CBinaryOneMaxEvaluation(iSize))
{

}//CBinaryOneMaxEvaluation::CBinaryOneMaxEvaluation(int iSize)


CBinaryStandardDeceptiveConcatenationEvaluation::CBinaryStandardDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks)
	: CBinaryEvaluation(new Evaluations::CBinaryStandardDeceptiveConcatenationEvaluation(iBlockSize, iNumberOfBlocks))
{

}//CBinaryStandardDeceptiveConcatenationEvaluation::CBinaryStandardDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks)


CBinaryBimodalDeceptiveConcatenationEvaluation::CBinaryBimodalDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks)
	: CBinaryEvaluation(new Evaluations::CBinaryBimodalDeceptiveConcatenationEvaluation(iBlockSize, iNumberOfBlocks))
{

}//CBinaryBimodalDeceptiveConcatenationEvaluation::CBinaryBimodalDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks)


CBinaryIsingSpinGlassEvaluation::CBinaryIsingSpinGlassEvaluation(int iSize)
	: CBinaryEvaluation(new Evaluations::CBinaryIsingSpinGlassEvaluation(iSize))
{

}//CBinaryIsingSpinGlassEvaluation::CBinaryIsingSpinGlassEvaluation(int iSize)

CBinaryIsingSpinGlassEvaluation::CBinaryIsingSpinGlassEvaluation(int iSize, int iProblemSeed)
	: CBinaryEvaluation(new Evaluations::CBinaryIsingSpinGlassEvaluation(iSize, iProblemSeed))
{

}//CBinaryIsingSpinGlassEvaluation::CBinaryIsingSpinGlassEvaluation(int iSize, int iProblemSeed)


CBinaryMax3SatEvaluation::CBinaryMax3SatEvaluation(int iSize)
	: CBinaryEvaluation(new Evaluations::CBinaryMax3SatEvaluation(iSize))
{

}//CBinaryMax3SatEvaluation::CBinaryMax3SatEvaluation(int iSize)

CBinaryMax3SatEvaluation::CBinaryMax3SatEvaluation(int iSize, int iProblemSeed)
	: CBinaryEvaluation(new Evaluations::CBinaryMax3SatEvaluation(iSize, iProblemSeed))
{

}//CBinaryMax3SatEvaluation::CBinaryMax3SatEvaluation(int iSize, int iProblemSeed)

CBinaryMax3SatEvaluation::CBinaryMax3SatEvaluation(int iSize, int iProblemSeed, float fClauseRatio)
	: CBinaryEvaluation(new Evaluations::CBinaryMax3SatEvaluation(iSize, iProblemSeed, fClauseRatio))
{

}//CBinaryMax3SatEvaluation::CBinaryMax3SatEvaluation(int iSize, int iProblemSeed, float fClauseRatio)


CBinaryNKLandscapesEvaluation::CBinaryNKLandscapesEvaluation(int iSize)
	: CBinaryEvaluation(new Evaluations::CBinaryNKLandscapesEvaluation(iSize))
{

}//CBinaryNKLandscapesEvaluation::CBinaryNKLandscapesEvaluation(int iSize)

CBinaryNKLandscapesEvaluation::CBinaryNKLandscapesEvaluation(int iSize, int iProblemSeed)
	: CBinaryEvaluation(new Evaluations::CBinaryNKLandscapesEvaluation(iSize, iProblemSeed))
{

}//CBinaryNKLandscapesEvaluation::CBinaryNKLandscapesEvaluation(int iSize, int iProblemSeed)


CBinaryKnapsackEvaluation::CBinaryKnapsackEvaluation(EBinaryKnapsackInstance eInstance)
	: pc_native_binary_knapsack_evaluation(new Evaluations::CBinaryKnapsackEvaluation((Evaluations::EBinaryKnapsackInstance)eInstance)), CBinaryEvaluation(pc_native_binary_knapsack_evaluation)
{
	l_weights = gcnew List<double>(pc_native_binary_knapsack_evaluation->iGetSize());
	l_profits = gcnew List<double>(pc_native_binary_knapsack_evaluation->iGetSize());

	for (int i = 0; i < pc_native_binary_knapsack_evaluation->iGetSize(); i++)
	{
		l_weights->Add(pc_native_binary_knapsack_evaluation->vGetWeights()[(size_t)i]);
		l_profits->Add(pc_native_binary_knapsack_evaluation->vGetProfits()[(size_t)i]);
	}//for (int i = 0; i < pc_native_binary_knapsack_evaluation->iGetSize(); i++)
}//CBinaryKnapsackEvaluation::CBinaryKnapsackEvaluation(EBinaryKnapsackInstance eInstance)

double CBinaryKnapsackEvaluation::dCalculateWeight(IList<bool> ^lSolution)
{
	vector<bool> v_solution(0);
	v_solution.reserve((size_t)lSolution->Count);

	for (int i = 0; i < lSolution->Count; i++)
	{
		v_solution.push_back(lSolution[i]);
	}//for (int i = 0; i < lSolution->Count; i++)

	return pc_native_binary_knapsack_evaluation->dCalculateWeight(v_solution);
}//double CBinaryKnapsackEvaluation::dCalculateWeight(IList<bool> ^lSolution)