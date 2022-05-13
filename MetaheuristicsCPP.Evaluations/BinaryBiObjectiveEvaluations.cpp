#include "BinaryBiObjectiveEvaluations.h"

using namespace Evaluations;


CBinaryBiObjectiveEvaluation::CBinaryBiObjectiveEvaluation(IEvaluation<bool, double> *pcEvaluation0, IEvaluation<bool, double> *pcEvaluation1)
	: CBiObjectiveEvaluation<bool>(pcEvaluation0, pcEvaluation1)
{

}//CBinaryBiObjectiveEvaluation::CBinaryBiObjectiveEvaluation(IEvaluation<bool, double> *pcEvaluation0, IEvaluation<bool, double> *pcEvaluation1)


CBinaryZeroMaxOneMaxEvaluation::CBinaryZeroMaxOneMaxEvaluation(int iSize)
	: CBinaryBiObjectiveEvaluation(new CBinaryZeroMaxEvaluation(iSize), new CBinaryOneMaxEvaluation(iSize))
{
	v_fill_optimal_pareto_front();
}//CBinaryZeroMaxOneMaxEvaluation::CBinaryZeroMaxOneMaxEvaluation(int iSize)

void CBinaryZeroMaxOneMaxEvaluation::v_fill_optimal_pareto_front()
{
	for (int i = 0; i <= iGetSize(); i++)
	{
		v_optimal_pareto_front.push_back(new pair<double, double>(i, iGetSize() - i));
	}//for (int i = 0; i <= iGetSize(); i++)
}//void CBinaryZeroMaxOneMaxEvaluation::v_fill_optimal_pareto_front()


CBinaryTrapInvTrapEvaluation::CBinaryTrapInvTrapEvaluation(int iBlockSize, int iNumberOfBlocks)
	: CBinaryBiObjectiveEvaluation(new CBinaryStandardDeceptiveConcatenationEvaluation(iBlockSize, iNumberOfBlocks), new CBinaryInverseStandardDeceptiveConcatenationEvaluation(iBlockSize, iNumberOfBlocks))
{
	pc_trap = (CBinaryStandardDeceptiveConcatenationEvaluation*)pc_evaluation_0;

	v_fill_optimal_pareto_front();
}//CBinaryTrapInvTrapEvaluation::CBinaryTrapInvTrapEvaluation(int iBlockSize, int iNumberOfBlocks)

void CBinaryTrapInvTrapEvaluation::v_fill_optimal_pareto_front()
{
	for (int i = 0; i <= pc_trap->iGetNumberOfBlocks(); i++)
	{
		double d_objective_0 = (pc_trap->iGetNumberOfBlocks() - i) * (pc_trap->iGetBlockSize() - 1) + i * pc_trap->iGetBlockSize();
		double d_objective_1 = (pc_trap->iGetNumberOfBlocks() - i) * pc_trap->iGetBlockSize() + i * (pc_trap->iGetBlockSize() - i);

		v_optimal_pareto_front.push_back(new pair<double, double>(d_objective_0, d_objective_1));
	}//for (int i = 0; i <= pc_trap->iGetNumberOfBlocks(); i++)
}//void CBinaryTrapInvTrapEvaluation::v_fill_optimal_pareto_front()


CBinaryLOTZEvaluation::CBinaryLOTZEvaluation(int iSize)
	: CBinaryBiObjectiveEvaluation(new CBinaryLeadingOnesEvaluation(iSize), new CBinaryTrailingZerosEvaluation(iSize))
{
	v_fill_optimal_pareto_front();
}//CBinaryLOTZEvaluation::CBinaryLOTZEvaluation(int iSize)

void CBinaryLOTZEvaluation::v_fill_optimal_pareto_front()
{
	for (int i = 0; i <= iGetSize(); i++)
	{
		v_optimal_pareto_front.push_back(new pair<double, double>(i, iGetSize() - i));
	}//for (int i = 0; i <= iGetSize(); i++)
}//void CBinaryLOTZEvaluation::v_fill_optimal_pareto_front()


CBinaryMOKnapsackEvaluation::CBinaryMOKnapsackEvaluation(EBinaryBiObjectiveKnapsackInstance eInstance)
	: CBinaryBiObjectiveEvaluation(new CBinaryKnapsackEvaluation(eInstance, 0), new CBinaryKnapsackEvaluation(eInstance, 1))
{
	pc_knapsack_0 = (CBinaryKnapsackEvaluation*)pc_evaluation_0;
	pc_knapsack_1 = (CBinaryKnapsackEvaluation*)pc_evaluation_1;

	v_load_optimal_pareto_front(eInstance);

	v_fill_repairing_order();
}//CBinaryMOKnapsackEvaluation::CBinaryMOKnapsackEvaluation(EBinaryBiObjectiveKnapsackInstance eInstance)

pair<double, double> CBinaryMOKnapsackEvaluation::t_evaluate(vector<bool> &vSolution)
{
	v_repaired_solution = vSolution;

	v_repair(*pc_knapsack_0);
	v_repair(*pc_knapsack_1);

	return CBinaryBiObjectiveEvaluation::t_evaluate(v_repaired_solution);
}//pair<double, double> CBinaryMOKnapsackEvaluation::t_evaluate(vector<bool> &vSolution)

void CBinaryMOKnapsackEvaluation::v_load_optimal_pareto_front(EBinaryBiObjectiveKnapsackInstance eInstance)
{
	string s_optimal_pareto_front_file_path = s_get_optimal_pareto_front_file_path(eInstance);

	ifstream f_optimal_pareto_front_file(s_optimal_pareto_front_file_path);

	if (!f_optimal_pareto_front_file)
	{
		throw invalid_argument(s_optimal_pareto_front_file_path + " not found");
	}//if (!f_optimal_pareto_front_file)

	double d_objective_value_0, d_objective_value_1;

	while (!f_optimal_pareto_front_file.eof())
	{
		f_optimal_pareto_front_file >> d_objective_value_0;
		f_optimal_pareto_front_file >> d_objective_value_1;

		v_optimal_pareto_front.push_back(new pair<double, double>(d_objective_value_0, d_objective_value_1));
	}//while (!f_optimal_pareto_front_file.eof())

	f_optimal_pareto_front_file.close();
}//void CBinaryMOKnapsackEvaluation::v_load_optimal_pareto_front(EBinaryBiObjectiveKnapsackInstance eInstance)

string CBinaryMOKnapsackEvaluation::s_get_optimal_pareto_front_file_path(EBinaryBiObjectiveKnapsackInstance eInstance)
{
	switch (eInstance)
	{
	case EBinaryBiObjectiveKnapsackInstance::knapsack_100:
		return "EvaluationsInputs\\instances_BO_KP\\knapsack.100.2.pareto.txt";
	case EBinaryBiObjectiveKnapsackInstance::knapsack_250:
		return "EvaluationsInputs\\instances_BO_KP\\knapsack.250.2.pareto.txt";
	case EBinaryBiObjectiveKnapsackInstance::knapsack_500:
		return "EvaluationsInputs\\instances_BO_KP\\knapsack.500.2.pareto.txt";
	case EBinaryBiObjectiveKnapsackInstance::knapsack_750:
		return "EvaluationsInputs\\instances_BO_KP\\knapsack.750.2.pareto.txt";
	default:
		return "unknown";
	}//switch (eInstance)
}//string CBinaryMOKnapsackEvaluation::s_get_optimal_pareto_front_file_path(EBinaryBiObjectiveKnapsackInstance eInstance)

void CBinaryMOKnapsackEvaluation::v_fill_repairing_order()
{
	v_repairing_order.resize((size_t)iGetSize());
	iota(v_repairing_order.begin(), v_repairing_order.end(), 0);

	vector<double> v_ratios(v_repairing_order.size());

	for (size_t i = 0; i < v_ratios.size(); i++)
	{
		v_ratios[i] = pc_knapsack_0->vGetProfits()[i] / pc_knapsack_0->vGetWeights()[i] + pc_knapsack_1->vGetProfits()[i] / pc_knapsack_1->vGetWeights()[i];
	}//for (size_t i = 0; i < v_ratios.size(); i++)

	sort(v_repairing_order.begin(), v_repairing_order.end(), [&v_ratios](int iIndex0, int iIndex1)
	{
		return v_ratios[iIndex0] < v_ratios[iIndex1];
	});//sort(v_repairing_order.begin(), v_repairing_order.end(), [&v_ratios](int iIndex0, int iIndex1)
}//void CBinaryMOKnapsackEvaluation::v_fill_repairing_order()

void CBinaryMOKnapsackEvaluation::v_repair(CBinaryKnapsackEvaluation &cKnapsack)
{
	double d_capacity = cKnapsack.dGetCapacity();
	double d_weight_sum = cKnapsack.dCalculateWeight(v_repaired_solution);

	int i_index;

	for (size_t i = 0; i < v_repairing_order.size() && d_weight_sum > d_capacity; i++)
	{
		i_index = v_repairing_order[i];

		if (v_repaired_solution[i_index])
		{
			v_repaired_solution[i_index] = false;
			d_weight_sum -= cKnapsack.vGetWeights()[i_index];
		}//if (v_repaired_solution[i_index])
	}//for (size_t i = 0; i < v_repairing_order.size() && d_weight_sum > d_capacity; i++)
}//void CBinaryMOKnapsackEvaluation::v_repair(CBinaryKnapsackEvaluation &cKnapsack)


CBinaryMOMaxCutEvaluation::CBinaryMOMaxCutEvaluation(EBinaryBiObjectiveMaxCutInstance eInstance)
	: CBinaryBiObjectiveEvaluation(new CBinaryMaxCutEvaluation(eInstance, 0), new CBinaryMaxCutEvaluation(eInstance, 1))
{
	v_load_optimal_pareto_front(eInstance);
}//CBinaryMOMaxCutEvaluation::CBinaryMOMaxCut(EBinaryBiObjectiveMaxCutInstance eInstance)

void CBinaryMOMaxCutEvaluation::v_load_optimal_pareto_front(EBinaryBiObjectiveMaxCutInstance eInstance)
{
	string s_optimal_pareto_front_file_path = s_get_optimal_pareto_front_file_path(eInstance);

	ifstream f_optimal_pareto_front_file(s_optimal_pareto_front_file_path);

	if (!f_optimal_pareto_front_file)
	{
		throw invalid_argument(s_optimal_pareto_front_file_path + " not found");
	}//if (!f_optimal_pareto_front_file)

	int i_size;
	f_optimal_pareto_front_file >> i_size;

	double d_objective_value_0, d_objective_value_1;

	for (int i = 0; i < i_size; i++)
	{
		f_optimal_pareto_front_file >> d_objective_value_0;
		f_optimal_pareto_front_file >> d_objective_value_1;

		v_optimal_pareto_front.push_back(new pair<double, double>(d_objective_value_0, d_objective_value_1));
	}//for (int i = 0; i < i_size; i++)

	f_optimal_pareto_front_file.close();
}//void CBinaryMOMaxCutEvaluation::v_load_optimal_pareto_front(EBinaryBiObjectiveMaxCutInstance eInstance)

string CBinaryMOMaxCutEvaluation::s_get_optimal_pareto_front_file_path(EBinaryBiObjectiveMaxCutInstance eInstance)
{
	switch (eInstance)
	{
	case EBinaryBiObjectiveMaxCutInstance::maxcut_instance_6:
		return "EvaluationsInputs\\instances_BO_MaxCut\\maxcut_pareto_front_6.txt";
	case EBinaryBiObjectiveMaxCutInstance::maxcut_instance_12:
		return "EvaluationsInputs\\instances_BO_MaxCut\\maxcut_pareto_front_12.txt";
	case EBinaryBiObjectiveMaxCutInstance::maxcut_instance_25:
		return "EvaluationsInputs\\instances_BO_MaxCut\\maxcut_pareto_front_25.txt";
	case EBinaryBiObjectiveMaxCutInstance::maxcut_instance_50:
		return "EvaluationsInputs\\instances_BO_MaxCut\\maxcut_pareto_front_50.txt";
	case EBinaryBiObjectiveMaxCutInstance::maxcut_instance_100:
		return "EvaluationsInputs\\instances_BO_MaxCut\\maxcut_pareto_front_100.txt";
	default:
		return "unknown";
	}//switch (eInstance)
}//string CBinaryMOMaxCutEvaluation::s_get_optimal_pareto_front_file_path(EBinaryBiObjectiveMaxCutInstance eInstance)