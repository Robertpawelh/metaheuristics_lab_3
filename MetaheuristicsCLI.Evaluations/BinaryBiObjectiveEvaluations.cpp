#include "BinaryBiObjectiveEvaluations.h"

using namespace EvaluationsCLI;


CBinaryBiObjectiveEvaluation::CBinaryBiObjectiveEvaluation(Evaluations::IEvaluation<bool, pair<double, double>> *pcNativeBinaryEvaluation)
{
	pc_native_binary_evaluation = pcNativeBinaryEvaluation;

	l_optimal_pareto_front = gcnew List<Tuple<double, double>^>((int)pc_native_binary_evaluation->vGetOptimalParetoFront().size());

	for (size_t i = 0; i < pc_native_binary_evaluation->vGetOptimalParetoFront().size(); i++)
	{
		l_optimal_pareto_front->Add(pc_map(*pc_native_binary_evaluation->vGetOptimalParetoFront()[i]));
	}//for (size_t i = 0; i < pc_native_binary_evaluation->vGetOptimalParetoFront().size(); i++)
}//BinaryBiObjectiveEvaluation::CBinaryBiObjectiveEvaluation(Evaluations::IEvaluation<bool, double> *pcNativeBinaryEvaluation)

CBinaryBiObjectiveEvaluation::~CBinaryBiObjectiveEvaluation()
{
	delete pc_native_binary_evaluation;
}//BinaryBiObjectiveEvaluation::~BinaryBiObjectiveEvaluation()

CBinaryBiObjectiveEvaluation::!CBinaryBiObjectiveEvaluation()
{
	delete pc_native_binary_evaluation;
}//CBinaryBiObjectiveEvaluation::!CBinaryBiObjectiveEvaluation()

Tuple<double, double>^ CBinaryBiObjectiveEvaluation::tEvaluate(IList<bool> ^lSolution)
{
	vector<bool> v_solution(0);
	v_solution.reserve(lSolution->Count);

	for (int i = 0; i < lSolution->Count; i++)
	{
		v_solution.push_back(lSolution[i]);
	}//for (int i = 0; i < lSolution->Count; i++)

	return pc_map(pc_native_binary_evaluation->tEvaluate(v_solution));
}//double CBinaryBiObjectiveEvaluation::tEvaluate(IList<bool> ^lSolution)

Tuple<double, double>^ CBinaryBiObjectiveEvaluation::pc_map(const pair<double, double> &pPair)
{
	return gcnew Tuple<double, double>(pPair.first, pPair.second);
}//Tuple<double, double>^ CBinaryBiObjectiveEvaluation::pc_map(const pair<double, double> &pPair)


CBinaryZeroMaxOneMaxEvaluation::CBinaryZeroMaxOneMaxEvaluation(int iSize)
	: CBinaryBiObjectiveEvaluation(new Evaluations::CBinaryZeroMaxOneMaxEvaluation(iSize))
{

}//CBinaryZeroMaxOneMaxEvaluation::CBinaryZeroMaxOneMaxEvaluation(int iSize)


CBinaryTrapInvTrapEvaluation::CBinaryTrapInvTrapEvaluation(int iBlockSize, int iNumberOfBlocks)
	: CBinaryBiObjectiveEvaluation(new Evaluations::CBinaryTrapInvTrapEvaluation(iBlockSize, iNumberOfBlocks))
{

}//CBinaryTrapInvTrapEvaluation::CBinaryTrapInvTrapEvaluation(int iBlockSize, int iNumberOfBlocks)


CBinaryLOTZEvaluation::CBinaryLOTZEvaluation(int iSize)
	: CBinaryBiObjectiveEvaluation(new Evaluations::CBinaryLOTZEvaluation(iSize))
{

}//CBinaryLOTZEvaluation::CBinaryLOTZEvaluation(int iSize)


CBinaryMOKnapsackEvaluation::CBinaryMOKnapsackEvaluation(EBinaryBiObjectiveKnapsackInstance eInstance)
	: CBinaryBiObjectiveEvaluation(new Evaluations::CBinaryMOKnapsackEvaluation((Evaluations::EBinaryBiObjectiveKnapsackInstance)eInstance))
{

}//CBinaryMOKnapsackEvaluation::CBinaryMOKnapsackEvaluation(EBinaryBiObjectiveKnapsackInstance eInstance)


CBinaryMOMaxCutEvaluation::CBinaryMOMaxCutEvaluation(EBinaryBiObjectiveMaxCutInstance eInstance)
	: CBinaryBiObjectiveEvaluation(new Evaluations::CBinaryMOMaxCutEvaluation((Evaluations::EBinaryBiObjectiveMaxCutInstance)eInstance))
{

}//CBinaryMOMaxCutEvaluation::CBinaryMOMaxCutEvaluation(EBinaryBiObjectiveMaxCutInstance eInstance)