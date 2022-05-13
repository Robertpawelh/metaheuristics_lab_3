#pragma once

#include "BiObjectiveEvaluation.h"
#include "BinaryEvaluationInstances.h"
#include "BinaryEvaluations.h"
#include "Evaluation.h"

#include <algorithm>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

using namespace std;

namespace Evaluations
{
	class CBinaryBiObjectiveEvaluation : public CBiObjectiveEvaluation<bool>
	{
	public:
		CBinaryBiObjectiveEvaluation(IEvaluation<bool, double> *pcEvaluation0, IEvaluation<bool, double> *pcEvaluation1);

		virtual IConstraint<bool> &cGetConstraint() { return c_constraint; }

	private:
		CBinaryNoConstraint c_constraint;
	};//class CBinaryEvaluation : public CBiObjectiveEvaluation<bool>


	class CBinaryZeroMaxOneMaxEvaluation : public CBinaryBiObjectiveEvaluation
	{
	public:
		CBinaryZeroMaxOneMaxEvaluation(int iSize);

	private:
		void v_fill_optimal_pareto_front();
	};//class CBinaryZeroMaxOneMaxEvaluation : public CBinaryBiObjectiveEvaluation

	
	class CBinaryTrapInvTrapEvaluation : public CBinaryBiObjectiveEvaluation
	{
	public:
		CBinaryTrapInvTrapEvaluation(int iBlockSize, int iNumberOfBlocks);

	private:
		CBinaryStandardDeceptiveConcatenationEvaluation *pc_trap;

		void v_fill_optimal_pareto_front();
	};//class CBinaryTrapInvTrapEvaluation : public CBinaryBiObjectiveEvaluation


	class CBinaryLOTZEvaluation : public CBinaryBiObjectiveEvaluation
	{
	public:
		CBinaryLOTZEvaluation(int iSize);

	private:
		void v_fill_optimal_pareto_front();
	};//class CBinaryLOTZEvaluation : public CBinaryBiObjectiveEvaluation


	class CBinaryMOKnapsackEvaluation : public CBinaryBiObjectiveEvaluation
	{
	public:
		CBinaryMOKnapsackEvaluation(EBinaryBiObjectiveKnapsackInstance eInstance);

	protected:
		virtual pair<double, double> t_evaluate(vector<bool> &vSolution);

	private:
		void v_load_optimal_pareto_front(EBinaryBiObjectiveKnapsackInstance eInstance);
		static string s_get_optimal_pareto_front_file_path(EBinaryBiObjectiveKnapsackInstance eInstance);

		void v_fill_repairing_order();
		void v_repair(CBinaryKnapsackEvaluation &cKnapsack);

		CBinaryKnapsackEvaluation *pc_knapsack_0;
		CBinaryKnapsackEvaluation *pc_knapsack_1;

		vector<int> v_repairing_order;
		vector<bool> v_repaired_solution;
	};//class CBinaryMOKnapsackEvaluation : public CBinaryBiObjectiveEvaluation


	class CBinaryMOMaxCutEvaluation : public CBinaryBiObjectiveEvaluation
	{
	public:
		CBinaryMOMaxCutEvaluation(EBinaryBiObjectiveMaxCutInstance eInstance);

	private:
		void v_load_optimal_pareto_front(EBinaryBiObjectiveMaxCutInstance eInstance);
		static string s_get_optimal_pareto_front_file_path(EBinaryBiObjectiveMaxCutInstance eInstance);
	};//class CBinaryMOMaxCutEvaluation : public CBinaryBiObjectiveEvaluation
}//namespace Evaluations