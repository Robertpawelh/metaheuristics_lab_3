#include "BinaryEvaluations.h"

using namespace Evaluations;


CBinaryEvaluation::CBinaryEvaluation(int iSize, double dMaxValue)
	: CEvaluation<bool, double>(iSize, dMaxValue)
{

}//CBinaryEvaluation::CBinaryEvaluation(int iSize, double dMaxValue)


CBinaryOneMaxEvaluation::CBinaryOneMaxEvaluation(int iSize)
	: CBinaryEvaluation(iSize, iSize)
{

}//CBinaryOneMaxEvaluation::CBinaryOneMaxEvaluation(int iSize)

double CBinaryOneMaxEvaluation::t_evaluate(vector<bool> &vSolution)
{
	double d_value = 0;

	for (int i = 0; i < iGetSize(); i++)
	{
		if (vSolution[i])
		{
			d_value++;
		}//if (vSolution[i])
	}//for (int i = 0; i < iGetSize(); i++)

	return d_value;
}//double CBinaryOneMaxEvaluation::t_evaluate(vector<bool> &cCoding)


CBinaryZeroMaxEvaluation::CBinaryZeroMaxEvaluation(int iSize)
	: CBinaryEvaluation(iSize, iSize)
{

}//CBinaryZeroMaxEvaluation::CBinaryZeroMaxEvaluation(int iSize)

double CBinaryZeroMaxEvaluation::t_evaluate(vector<bool>& vSolution)
{
	double d_value = 0;

	for (int i = 0; i < iGetSize(); i++)
	{
		if (!vSolution[i])
		{
			d_value++;
		}//if (vSolution[i])
	}//for (int i = 0; i < iGetSize(); i++)

	return d_value;
}//double CBinaryZeroMaxEvaluation::t_evaluate(vector<bool>& vSolution)


CBinaryLeadingOnesEvaluation::CBinaryLeadingOnesEvaluation(int iSize)
	: CBinaryEvaluation(iSize, iSize)
{

}//CBinaryLeadingOnesEvaluation::CBinaryLeadingOnesEvaluation(int iSize)

double CBinaryLeadingOnesEvaluation::t_evaluate(vector<bool> &vSolution)
{
	double d_value = 0;

	for (int i = 0; i < iGetSize() && vSolution[i]; i++)
	{
		d_value++;
	}//for (int i = 0; i < iGetSize() && vSolution[i]; i++)

	return d_value;
}//double CBinaryLeadingOnesEvaluation::t_evaluate(vector<bool> &vSolution)


CBinaryTrailingZerosEvaluation::CBinaryTrailingZerosEvaluation(int iSize)
	: CBinaryEvaluation(iSize, iSize)
{

}//CBinaryTrailingZerosEvaluation::CBinaryTrailingZerosEvaluation(int iSize)

double CBinaryTrailingZerosEvaluation::t_evaluate(vector<bool> &vSolution)
{
	double d_value = 0;

	for (int i = iGetSize() - 1; i >= 0 && !vSolution[i]; i--)
	{
		d_value++;
	}//for (int i = iGetSize() - 1; i >= 0 && !vSolution[i]; i--)

	return d_value;
}//double CBinaryTrailingZerosEvaluation::t_evaluate(vector<bool> &vSolution)


CBinaryDeceptiveConcatenationEvaluation::CBinaryDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks, double dMaxValue)
	: CBinaryEvaluation(iBlockSize * iNumberOfBlocks, dMaxValue), i_block_size(iBlockSize), i_number_of_blocks(iNumberOfBlocks)
{

}//CBinaryDeceptiveConcatenationEvaluation::CBinaryDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks, double dMaxValue)

double CBinaryDeceptiveConcatenationEvaluation::t_evaluate(vector<bool> &vSolution)
{
	double d_value = 0;

	int i_unitation;

	for (int i = 0; i < i_number_of_blocks; i++)
	{
		i_unitation = 0;

		for (int j = 0; j < i_block_size; j++)
		{
			if (vSolution[i * i_block_size + j])
			{
				i_unitation++;
			}//if (vSolution[i * i_block_size + j])
		}//for (int j = 0; j < i_block_size; j++)

		d_value += d_evaluate(i_unitation);
	}//for (int i = 0; i < i_number_of_blocks; i++)

	return d_value;
}//double CBinaryDeceptiveConcatenationEvaluation::t_evaluate(vector<bool> &vSolution)


CBinaryStandardDeceptiveConcatenationEvaluation::CBinaryStandardDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks)
	: CBinaryDeceptiveConcatenationEvaluation(iBlockSize, iNumberOfBlocks, iBlockSize * iNumberOfBlocks)
{

}//CBinaryStandardDeceptiveConcatenationEvaluation::CBinaryStandardDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks)

double CBinaryStandardDeceptiveConcatenationEvaluation::d_evaluate(int iUnitation)
{
	double d_value;

	if (iUnitation == i_block_size)
	{
		d_value = i_block_size;
	}//if (iUnitation == i_block_size)
	else
	{
		d_value = i_block_size - 1 - iUnitation;
	}//else if (iUnitation == i_block_size)

	return d_value;
}//double CBinaryStandardDeceptiveConcatenationEvaluation::d_evaluate(int iUnitation)


CBinaryInverseStandardDeceptiveConcatenationEvaluation::CBinaryInverseStandardDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks)
	: CBinaryDeceptiveConcatenationEvaluation(iBlockSize, iNumberOfBlocks, iBlockSize * iNumberOfBlocks)
{

}//CBinaryInverseStandardDeceptiveConcatenationEvaluation::CBinaryInverseStandardDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks)

double CBinaryInverseStandardDeceptiveConcatenationEvaluation::d_evaluate(int iUnitation)
{
	double d_value;

	if (iUnitation == 0)
	{
		d_value = i_block_size;
	}//if (iUnitation == 0)
	else
	{
		d_value = i_block_size - 1;
	}//else if (iUnitation == 0)

	return d_value;
}//double CBinaryInverseStandardDeceptiveConcatenationEvaluation::d_evaluate(int iUnitation)


CBinaryBimodalDeceptiveConcatenationEvaluation::CBinaryBimodalDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks)
	: CBinaryDeceptiveConcatenationEvaluation(iBlockSize, iNumberOfBlocks, iBlockSize * iNumberOfBlocks / 2.0)
{

}//CBinaryBimodalDeceptiveConcatenationEvaluation::CBinaryStandardDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks)

double CBinaryBimodalDeceptiveConcatenationEvaluation::d_evaluate(int iUnitation)
{
	double d_value;

	if (iUnitation == i_block_size || iUnitation == 0)
	{
		d_value = i_block_size / 2.0;
	}//if (iUnitation == i_block_size)
	else
	{
		d_value = i_block_size / 2.0 - abs(iUnitation - i_block_size / 2.0) - 1;
	}//else if (iUnitation == i_block_size)

	return d_value;
}//double CBinaryBimodalDeceptiveConcatenationEvaluation::d_evaluate(int iUnitation)


CBinaryIsingSpinGlassEvaluation::CBinaryIsingSpinGlassEvaluation(int iSize, int iProblemSeed)
	: CBinaryEvaluation(iSize, 1.0)
{
	Configuration c_config;

	c_config.set("length", iSize);
	c_config.set("precision", 65536);
	c_config.set("problem_seed", iProblemSeed);
	c_config.set("problem_folder", string("EvaluationsInputs\\"));
	c_config.set("ising_type", string("pm"));

	pc_p3_ising_spin_glass = new IsingSpinGlass(c_config, 0);
}//CBinaryIsingSpinGlassEvaluation::CBinaryIsingSpinGlassEvaluation(int iSize, int iProblemSeed)

CBinaryIsingSpinGlassEvaluation::~CBinaryIsingSpinGlassEvaluation()
{
	delete pc_p3_ising_spin_glass;
}//CBinaryIsingSpinGlassEvaluation::~CBinaryIsingSpinGlassEvaluation()

double CBinaryIsingSpinGlassEvaluation::t_evaluate(vector<bool> &vSolution)
{
	return pc_p3_ising_spin_glass->evaluate(vSolution);
}//double CBinaryIsingSpinGlassEvaluation::t_evaluate(vector<bool> &vSolution)


CBinaryMax3SatEvaluation::CBinaryMax3SatEvaluation(int iSize, int iProblemSeed, float fClauseRatio)
	: CBinaryEvaluation(iSize, 1.0)
{
	Configuration c_config;

	c_config.set("length", iSize);
	c_config.set("precision", 65536);
	c_config.set("problem_seed", iProblemSeed);
	c_config.set("clause_ratio", fClauseRatio);

	pc_p3_max_sat = new MAXSAT(c_config, 0);
}//CBinaryMax3SatEvaluation::CBinaryMax3SatEvaluation(int iSize, int iProblemSeed, float fClauseRatio)

CBinaryMax3SatEvaluation::~CBinaryMax3SatEvaluation()
{
	delete pc_p3_max_sat;
}//CBinaryMax3SatEvaluation::~CBinaryMax3SatEvaluation()

double CBinaryMax3SatEvaluation::t_evaluate(vector<bool> &vSolution)
{
	return pc_p3_max_sat->evaluate(vSolution);
}//double CBinaryMax3SatEvaluation::t_evaluate(vector<bool> &vSolution)


CBinaryNKLandscapesEvaluation::CBinaryNKLandscapesEvaluation(int iSize, int iProblemSeed)
	: CBinaryEvaluation(iSize, 1.0)
{
	Configuration c_config;

	c_config.set("length", iSize);
	c_config.set("precision", 65536);
	c_config.set("problem_seed", iProblemSeed);
	c_config.set("k", 5);
	c_config.set("problem_folder", string("EvaluationsInputs\\"));

	pc_p3_nk_landscapes = new NearestNeighborNK(c_config, 0);
}//CBinaryNKLandscapesEvaluation::CBinaryNKLandscapesEvaluation(int iSize, int iProblemSeed)

CBinaryNKLandscapesEvaluation::~CBinaryNKLandscapesEvaluation()
{
	delete pc_p3_nk_landscapes;
}//CBinaryNKLandscapesEvaluation::~CBinaryNKLandscapesEvaluation()

double CBinaryNKLandscapesEvaluation::t_evaluate(vector<bool> &vSolution)
{
	return pc_p3_nk_landscapes->evaluate(vSolution);
}//double CBinaryNKLandscapesEvaluation::t_evaluate(vector<bool> &vSolution)


CBinaryKnapsackEvaluation::CBinaryKnapsackEvaluation(EBinaryKnapsackInstance eInstance)
	: CBinaryEvaluation(0, 0)
{
	v_load(eInstance);
}//CBinaryKnapsackEvaluation::CBinaryKnapsackEvaluation(EBinaryKnapsackInstance eInstance)

CBinaryKnapsackEvaluation::CBinaryKnapsackEvaluation(EBinaryBiObjectiveKnapsackInstance eInstance, int iObjectiveIndex)
	: CBinaryEvaluation(0, 0)
{
	v_load(eInstance, iObjectiveIndex);
}//CBinaryKnapsackEvaluation::CBinaryKnapsackEvaluation(EBinaryBiObjectiveKnapsackInstance eInstance, int iObjectiveIndex)

double CBinaryKnapsackEvaluation::dCalculateWeight(vector<bool> &vSolution)
{
	double d_weight = 0;

	for (int i = 0; i < iGetSize(); i++)
	{
		if (vSolution[i])
		{
			d_weight += v_weights[i];
		}//if (vSolution[i])
	}//for (int i = 0; i < iGetSize(); i++)

	return d_weight;
}//double CBinaryKnapsackEvaluation::dCalculateWeight(vector<bool> &vSolution)

double CBinaryKnapsackEvaluation::t_evaluate(vector<bool> &vSolution)
{
	double d_value = 0;

	for (int i = 0; i < iGetSize(); i++)
	{
		if (vSolution[i])
		{
			d_value += v_profits[i];
		}//if (vSolution[i])
	}//for (int i = 0; i < iGetSize(); i++)

	return d_value;
}//double CBinaryKnapsackEvaluation::t_evaluate(vector<bool> &vSolution)

void CBinaryKnapsackEvaluation::v_load(EBinaryKnapsackInstance eInstance)
{
	SBinaryKnapsackInstanceFilePaths *pc_file_paths = SBinaryKnapsackInstanceFilePaths::pcCreate(eInstance);

	v_load_definition_file(pc_file_paths->sDefinitionFilePath);
	v_load_optimum_file(pc_file_paths->sOptimumFilePath);

	delete pc_file_paths;
}//void CBinaryKnapsackEvaluation::v_load(EBinaryKnapsackInstance eInstance)

void CBinaryKnapsackEvaluation::v_load_definition_file(string &sDefinitionFilePath)
{
	ifstream f_definition_file(sDefinitionFilePath);

	if (!f_definition_file)
	{
		throw invalid_argument(sDefinitionFilePath + " not found");
	}//if (!f_definition_file)

	int i_size;
	f_definition_file >> i_size;
	v_set_size(i_size);

	f_definition_file >> d_capacity;

	double d_profit, d_weight;

	v_profits.clear();
	v_profits.reserve((size_t)i_size);

	v_weights.clear();
	v_weights.reserve((size_t)i_size);

	for (int i = 0; i < i_size; i++)
	{
		f_definition_file >> d_profit;
		f_definition_file >> d_weight;

		v_profits.push_back(d_profit);
		v_weights.push_back(d_weight);
	}//for (int i = 0; i < i_size; i++)

	f_definition_file.close();
}//void CBinaryKnapsackEvaluation::v_load_definition_file(string &sDefinitionFilePath)

void CBinaryKnapsackEvaluation::v_load_optimum_file(string &sOptimumFilePath)
{
	ifstream f_optimum_file(sOptimumFilePath);

	if (!f_optimum_file)
	{
		throw invalid_argument(sOptimumFilePath + " not found");
	}//if (!f_optimum_file)

	double d_max_value;
	f_optimum_file >> d_max_value;
	v_set_max_value(d_max_value);

	f_optimum_file.close();
}//void CBinaryKnapsackEvaluation::v_load_optimum_file(string &sOptimumFilePath)

void CBinaryKnapsackEvaluation::v_load(EBinaryBiObjectiveKnapsackInstance eInstance, int iObjectiveIndex)
{
	string s_definition_file_path = s_get_definition_file_path(eInstance);

	ifstream f_definition_file(s_definition_file_path);

	if (!f_definition_file)
	{
		throw invalid_argument(s_definition_file_path + " not found");
	}//if (!f_definition_file)

	int i_number_of_objectives;
	f_definition_file >> i_number_of_objectives;

	int i_size;
	f_definition_file >> i_size;
	v_set_size(i_size);

	int i_item_index;
	double d_profit, d_weight;

	for (int i = 0; i <= iObjectiveIndex; i++)
	{
		f_definition_file >> d_capacity;

		v_profits.clear();
		v_profits.reserve((size_t)i_size);

		v_weights.clear();
		v_weights.reserve((size_t)i_size);

		for (int j = 0; j < i_size; j++)
		{
			f_definition_file >> i_item_index;
			f_definition_file >> d_weight;
			f_definition_file >> d_profit;

			v_profits.push_back(d_profit);
			v_weights.push_back(d_weight);
		}//for (int j = 0; j < i_size; j++)
	}//for (int i = 0; i <= iObjectiveIndex; i++)

	f_definition_file.close();

	double d_max_value = accumulate(v_profits.begin(), v_profits.end(), 0.0);
	v_set_max_value(d_max_value);
}//void CBinaryKnapsackEvaluation::v_load(EBinaryBiObjectiveKnapsackInstance eInstance, int iObjectiveIndex)

string CBinaryKnapsackEvaluation::s_get_definition_file_path(EBinaryBiObjectiveKnapsackInstance eInstance)
{
	switch (eInstance)
	{
	case EBinaryBiObjectiveKnapsackInstance::knapsack_100:
		return "EvaluationsInputs\\instances_BO_KP\\knapsack.100.2.txt";
	case EBinaryBiObjectiveKnapsackInstance::knapsack_250:
		return "EvaluationsInputs\\instances_BO_KP\\knapsack.250.2.txt";
	case EBinaryBiObjectiveKnapsackInstance::knapsack_500:
		return "EvaluationsInputs\\instances_BO_KP\\knapsack.500.2.txt";
	case EBinaryBiObjectiveKnapsackInstance::knapsack_750:
		return "EvaluationsInputs\\instances_BO_KP\\knapsack.750.2.txt";
	default:
		return "unknown";
	}//switch (eInstance)
}//string CBinaryKnapsackEvaluation::s_get_definition_file_path(EBinaryBiObjectiveKnapsackInstance eInstance)


CBinaryMaxCutEvaluation::CBinaryMaxCutEvaluation(EBinaryBiObjectiveMaxCutInstance eInstance, int iObjectiveIndex)
	: CBinaryEvaluation(0, 0)
{
	v_load(eInstance, iObjectiveIndex);
}//CBinaryMaxCutEvaluation::CBinaryMaxCutEvaluation(EBinaryBiObjectiveMaxCutInstance eInstance, int iObjectiveIndex)

double CBinaryMaxCutEvaluation::t_evaluate(vector<bool> &vSolution)
{
	double d_value = 0;

	for (size_t i = 0; i < v_weights.size(); i++)
	{
		if (vSolution[v_start_nodes[i]] != vSolution[v_end_nodes[i]])
		{
			d_value += v_weights[i];
		}//if (vSolution[v_start_nodes[i]] != vSolution[v_end_nodes[i]])
	}//for (size_t i = 0; i < v_weights.size(); i++)

	return d_value;
}//double CBinaryMaxCutEvaluation::t_evaluate(vector<bool> &vSolution)

void CBinaryMaxCutEvaluation::v_load(EBinaryBiObjectiveMaxCutInstance eInstance, int iObjectiveIndex)
{
	string s_definition_file_path = s_get_definition_file_path(eInstance, iObjectiveIndex);

	ifstream f_definition_file(s_definition_file_path);

	if (!f_definition_file)
	{
		throw invalid_argument(s_definition_file_path + " not found");
	}//if (!f_definition_file)

	int i_size;
	f_definition_file >> i_size;
	v_set_size(i_size);

	int i_number_of_edges;
	f_definition_file >> i_number_of_edges;

	v_start_nodes.clear();
	v_start_nodes.reserve((size_t)i_number_of_edges);

	v_end_nodes.clear();
	v_end_nodes.reserve((size_t)i_number_of_edges);

	v_weights.clear();
	v_weights.reserve((size_t)i_number_of_edges);

	int i_start_node, i_end_node;
	double d_weight;

	for (int i = 0; i < i_number_of_edges; i++)
	{
		f_definition_file >> i_start_node;
		i_start_node--;

		f_definition_file >> i_end_node;
		i_end_node--;

		f_definition_file >> d_weight;

		v_start_nodes.push_back(i_start_node);
		v_end_nodes.push_back(i_end_node);
		v_weights.push_back(d_weight);
	}//for (int i = 0; i < i_number_of_edges; i++)

	f_definition_file.close();

	double d_max_value = accumulate(v_weights.begin(), v_weights.end(), 0.0);
	v_set_max_value(d_max_value);
}//void CBinaryMaxCutEvaluation::v_load(EBinaryBiObjectiveMaxCutInstance eInstance, int iObjectiveIndex)

string CBinaryMaxCutEvaluation::s_get_definition_file_path(EBinaryBiObjectiveMaxCutInstance eInstance, int iObjectiveIndex)
{
	switch (eInstance)
	{
	case EBinaryBiObjectiveMaxCutInstance::maxcut_instance_6:
		return "EvaluationsInputs\\instances_BO_MaxCut\\maxcut_instance_6_" + to_string(iObjectiveIndex) + ".txt";
	case EBinaryBiObjectiveMaxCutInstance::maxcut_instance_12:
		return "EvaluationsInputs\\instances_BO_MaxCut\\maxcut_instance_12_" + to_string(iObjectiveIndex) + ".txt";
	case EBinaryBiObjectiveMaxCutInstance::maxcut_instance_25:
		return "EvaluationsInputs\\instances_BO_MaxCut\\maxcut_instance_25_" + to_string(iObjectiveIndex) + ".txt";
	case EBinaryBiObjectiveMaxCutInstance::maxcut_instance_50:
		return "EvaluationsInputs\\instances_BO_MaxCut\\maxcut_instance_50_" + to_string(iObjectiveIndex) + ".txt";
	case EBinaryBiObjectiveMaxCutInstance::maxcut_instance_100:
		return "EvaluationsInputs\\instances_BO_MaxCut\\maxcut_instance_100_" + to_string(iObjectiveIndex) + ".txt";
	default:
		return "unknown";
	}//switch (eInstance)
}//string CBinaryMaxCutEvaluation::s_get_definition_file_path(EBinaryBiObjectiveMaxCutInstance eInstance, int iObjectiveIndex)