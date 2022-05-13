#include "BinaryEvaluationInstances.h"

using namespace Evaluations;

SBinaryKnapsackInstanceFilePaths * SBinaryKnapsackInstanceFilePaths::pcCreate(EBinaryKnapsackInstance eInstance)
{
	switch (eInstance)
	{
		case EBinaryKnapsackInstance::f1_l_d_kp_10_269:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\low-dimensional\\f1_l-d_kp_10_269", "EvaluationsInputs\\instances_01_KP\\low-dimensional-optimum\\f1_l-d_kp_10_269" };
		case EBinaryKnapsackInstance::f2_l_d_kp_20_878:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\low-dimensional\\f2_l-d_kp_20_878", "EvaluationsInputs\\instances_01_KP\\low-dimensional-optimum\\f2_l-d_kp_20_878" };
		case EBinaryKnapsackInstance::f3_l_d_kp_4_20:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\low-dimensional\\f3_l-d_kp_4_20", "EvaluationsInputs\\instances_01_KP\\low-dimensional-optimum\\f3_l-d_kp_4_20" };
		case EBinaryKnapsackInstance::f4_l_d_kp_4_11:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\low-dimensional\\f4_l-d_kp_4_11", "EvaluationsInputs\\instances_01_KP\\low-dimensional-optimum\\f4_l-d_kp_4_11" };
		case EBinaryKnapsackInstance::f5_l_d_kp_15_375:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\low-dimensional\\f5_l-d_kp_15_375", "EvaluationsInputs\\instances_01_KP\\low-dimensional-optimum\\f5_l-d_kp_15_375" };
		case EBinaryKnapsackInstance::f6_l_d_kp_10_60:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\low-dimensional\\f6_l-d_kp_10_60", "EvaluationsInputs\\instances_01_KP\\low-dimensional-optimum\\f6_l-d_kp_10_60" };
		case EBinaryKnapsackInstance::f7_l_d_kp_7_50:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\low-dimensional\\f7_l-d_kp_7_50", "EvaluationsInputs\\instances_01_KP\\low-dimensional-optimum\\f7_l-d_kp_7_50" };
		case EBinaryKnapsackInstance::f8_l_d_kp_23_10000:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\low-dimensional\\f8_l-d_kp_23_10000", "EvaluationsInputs\\instances_01_KP\\low-dimensional-optimum\\f8_l-d_kp_23_10000" };
		case EBinaryKnapsackInstance::f9_l_d_kp_5_80:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\low-dimensional\\f9_l-d_kp_5_80", "EvaluationsInputs\\instances_01_KP\\low-dimensional-optimum\\f9_l-d_kp_5_80" };
		case EBinaryKnapsackInstance::f10_l_d_kp_20_879:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\low-dimensional\\f10_l-d_kp_20_879", "EvaluationsInputs\\instances_01_KP\\low-dimensional-optimum\\f10_l-d_kp_20_879" };
		case EBinaryKnapsackInstance::knapPI_1_100_1000_1:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\large_scale\\knapPI_1_100_1000_1", "EvaluationsInputs\\instances_01_KP\\large_scale-optimum\\knapPI_1_100_1000_1" };
		case EBinaryKnapsackInstance::knapPI_1_200_1000_1:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\large_scale\\knapPI_1_200_1000_1", "EvaluationsInputs\\instances_01_KP\\large_scale-optimum\\knapPI_1_200_1000_1" };
		case EBinaryKnapsackInstance::knapPI_1_500_1000_1:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\large_scale\\knapPI_1_500_1000_1", "EvaluationsInputs\\instances_01_KP\\large_scale-optimum\\knapPI_1_500_1000_1" };
		case EBinaryKnapsackInstance::knapPI_1_1000_1000_1:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\large_scale\\knapPI_1_1000_1000_1", "EvaluationsInputs\\instances_01_KP\\large_scale-optimum\\knapPI_1_1000_1000_1" };
		case EBinaryKnapsackInstance::knapPI_1_2000_1000_1:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\large_scale\\knapPI_1_2000_1000_1", "EvaluationsInputs\\instances_01_KP\\large_scale-optimum\\knapPI_1_2000_1000_1" };
		case EBinaryKnapsackInstance::knapPI_1_5000_1000_1:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\large_scale\\knapPI_1_5000_1000_1", "EvaluationsInputs\\instances_01_KP\\large_scale-optimum\\knapPI_1_5000_1000_1" };
		case EBinaryKnapsackInstance::knapPI_1_10000_1000_1:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\large_scale\\knapPI_1_10000_1000_1", "EvaluationsInputs\\instances_01_KP\\large_scale-optimum\\knapPI_1_10000_1000_1" };
		case EBinaryKnapsackInstance::knapPI_2_100_1000_1:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\large_scale\\knapPI_2_100_1000_1", "EvaluationsInputs\\instances_01_KP\\large_scale-optimum\\knapPI_2_100_1000_1" };
		case EBinaryKnapsackInstance::knapPI_2_200_1000_1:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\large_scale\\knapPI_2_200_1000_1", "EvaluationsInputs\\instances_01_KP\\large_scale-optimum\\knapPI_2_200_1000_1" };
		case EBinaryKnapsackInstance::knapPI_2_500_1000_1:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\large_scale\\knapPI_2_500_1000_1", "EvaluationsInputs\\instances_01_KP\\large_scale-optimum\\knapPI_2_500_1000_1" };
		case EBinaryKnapsackInstance::knapPI_2_1000_1000_1:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\large_scale\\knapPI_2_1000_1000_1", "EvaluationsInputs\\instances_01_KP\\large_scale-optimum\\knapPI_2_1000_1000_1" };
		case EBinaryKnapsackInstance::knapPI_2_2000_1000_1:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\large_scale\\knapPI_2_2000_1000_1", "EvaluationsInputs\\instances_01_KP\\large_scale-optimum\\knapPI_2_2000_1000_1" };
		case EBinaryKnapsackInstance::knapPI_2_5000_1000_1:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\large_scale\\knapPI_2_5000_1000_1", "EvaluationsInputs\\instances_01_KP\\large_scale-optimum\\knapPI_2_5000_1000_1" };
		case EBinaryKnapsackInstance::knapPI_2_10000_1000_1:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\large_scale\\knapPI_2_10000_1000_1", "EvaluationsInputs\\instances_01_KP\\large_scale-optimum\\knapPI_2_10000_1000_1" };
		case EBinaryKnapsackInstance::knapPI_3_100_1000_1:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\large_scale\\knapPI_3_100_1000_1", "EvaluationsInputs\\instances_01_KP\\large_scale-optimum\\knapPI_3_100_1000_1" };
		case EBinaryKnapsackInstance::knapPI_3_200_1000_1:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\large_scale\\knapPI_3_200_1000_1", "EvaluationsInputs\\instances_01_KP\\large_scale-optimum\\knapPI_3_200_1000_1" };
		case EBinaryKnapsackInstance::knapPI_3_500_1000_1:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\large_scale\\knapPI_3_500_1000_1", "EvaluationsInputs\\instances_01_KP\\large_scale-optimum\\knapPI_3_500_1000_1" };
		case EBinaryKnapsackInstance::knapPI_3_1000_1000_1:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\large_scale\\knapPI_3_1000_1000_1", "EvaluationsInputs\\instances_01_KP\\large_scale-optimum\\knapPI_3_1000_1000_1" };
		case EBinaryKnapsackInstance::knapPI_3_2000_1000_1:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\large_scale\\knapPI_3_2000_1000_1", "EvaluationsInputs\\instances_01_KP\\large_scale-optimum\\knapPI_3_2000_1000_1" };
		case EBinaryKnapsackInstance::knapPI_3_5000_1000_1:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\large_scale\\knapPI_3_5000_1000_1", "EvaluationsInputs\\instances_01_KP\\large_scale-optimum\\knapPI_3_5000_1000_1" };
		case EBinaryKnapsackInstance::knapPI_3_10000_1000_1:
			return new SBinaryKnapsackInstanceFilePaths{ "EvaluationsInputs\\instances_01_KP\\large_scale\\knapPI_3_10000_1000_1", "EvaluationsInputs\\instances_01_KP\\large_scale-optimum\\knapPI_3_10000_1000_1" };
		default:
			return new SBinaryKnapsackInstanceFilePaths{ "unknown", "unknown" };
	}//switch (eInstance)
}//SBinaryKnapsackInstanceFilePaths * SBinaryKnapsackInstanceFilePaths::pcCreate(EBinaryKnapsackInstance eInstance)