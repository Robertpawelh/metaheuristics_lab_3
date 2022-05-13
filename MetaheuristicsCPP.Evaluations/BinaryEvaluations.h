#pragma once

#include "BinaryEvaluationInstances.h"
#include "BinaryConstraints.h"
#include "Constraint.h"
#include "Evaluation.h"
#include "P3Configuration.h"
#include "P3Evaluation.h"

#include <cmath>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>

using namespace Constraints;

namespace Evaluations
{
	class CBinaryEvaluation : public CEvaluation<bool, double>
	{
	public:
		CBinaryEvaluation(int iSize, double dMaxValue);

		virtual IConstraint<bool> &cGetConstraint() { return c_constraint; }

	private:
		CBinaryNoConstraint c_constraint;
	};//class CBinaryEvaluation : public IEvaluation<bool, double>


	class CBinaryOneMaxEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryOneMaxEvaluation(int iSize);

	protected:
		virtual double t_evaluate(vector<bool> &vSolution);
	};//class CBinaryOneMaxEvaluation : public CBinaryEvaluation


	class CBinaryZeroMaxEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryZeroMaxEvaluation(int iSize);

	protected:
		virtual double t_evaluate(vector<bool> &vSolution);
	};//class CBinaryZeroMaxEvaluation : public CBinaryEvaluation


	class CBinaryLeadingOnesEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryLeadingOnesEvaluation(int iSize);

	protected:
		virtual double t_evaluate(vector<bool> &vSolution);
	};//class CBinaryLeadingOnesEvaluation : public CBinaryEvaluation


	class CBinaryTrailingZerosEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryTrailingZerosEvaluation(int iSize);

	protected:
		virtual double t_evaluate(vector<bool> &vSolution);
	};//class CBinaryTrailingZerosEvaluation : public CBinaryEvaluation


	class CBinaryDeceptiveConcatenationEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks, double dMaxValue);

		int iGetBlockSize() { return i_block_size; }
		int iGetNumberOfBlocks() { return i_number_of_blocks; }

	protected:
		virtual double t_evaluate(vector<bool> &vSolution);

		virtual double d_evaluate(int iUnitation) = 0;

		int i_block_size;

	private:
		int i_number_of_blocks;
	};//class CBinaryDeceptiveConcatenationEvaluation : public CBinaryEvaluation


	class CBinaryStandardDeceptiveConcatenationEvaluation : public CBinaryDeceptiveConcatenationEvaluation
	{
	public:
		CBinaryStandardDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks);

	protected:
		virtual double d_evaluate(int iUnitation);
	};//class CBinaryStandardDeceptiveConcatenationEvaluation : public CBinaryEvaluation


	class CBinaryInverseStandardDeceptiveConcatenationEvaluation : public CBinaryDeceptiveConcatenationEvaluation
	{
	public:
		CBinaryInverseStandardDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks);

	protected:
		virtual double d_evaluate(int iUnitation);
	};//class CBinaryInverseStandardDeceptiveConcatenationEvaluation : public CBinaryEvaluation


	class CBinaryBimodalDeceptiveConcatenationEvaluation : public CBinaryDeceptiveConcatenationEvaluation
	{
	public:
		CBinaryBimodalDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks);

	protected:
		virtual double d_evaluate(int iUnitation);
	};//class CBinaryBimodalDeceptiveConcatenationEvaluation : public CBinaryDeceptiveConcatenationEvaluation


	class CBinaryIsingSpinGlassEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryIsingSpinGlassEvaluation(int iSize, int iProblemSeed = 0);

		virtual ~CBinaryIsingSpinGlassEvaluation();

	protected:
		virtual double t_evaluate(vector<bool> &vSolution);

	private:
		IsingSpinGlass *pc_p3_ising_spin_glass;
	};//class CBinaryIsingSpinGlassEvaluation : public CBinaryEvaluation


	class CBinaryMax3SatEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryMax3SatEvaluation(int iSize, int iProblemSeed = 0, float fClauseRatio = 4.27f);

		virtual ~CBinaryMax3SatEvaluation();

	protected:
		virtual double t_evaluate(vector<bool> &vSolution);

	private:
		MAXSAT *pc_p3_max_sat;
	};//class CBinaryMax3SatEvaluation : public CBinaryEvaluation


	class CBinaryNKLandscapesEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryNKLandscapesEvaluation(int iSize, int iProblemSeed = 0);

		virtual ~CBinaryNKLandscapesEvaluation();

	protected:
		virtual double t_evaluate(vector<bool> &vSolution);

	private:
		NearestNeighborNK *pc_p3_nk_landscapes;
	};//class CBinaryNKLandscapesEvaluation : public CBinaryEvaluation


	class CBinaryKnapsackEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryKnapsackEvaluation(EBinaryKnapsackInstance eInstance);
		CBinaryKnapsackEvaluation(EBinaryBiObjectiveKnapsackInstance eInstance, int iObjectiveIndex);

		double dCalculateWeight(vector<bool> &vSolution);

		vector<double> &vGetWeights() { return v_weights; }
		vector<double> &vGetProfits() { return v_profits; }
		double dGetCapacity() { return d_capacity; }

	protected:
		virtual double t_evaluate(vector<bool> &vSolution);

	private:
		void v_load(EBinaryKnapsackInstance eInstance);
		void v_load_definition_file(string &sDefinitionFilePath);
		void v_load_optimum_file(string &sOptimumFilePath);

		void v_load(EBinaryBiObjectiveKnapsackInstance eInstance, int iObjectiveIndex);
		static string s_get_definition_file_path(EBinaryBiObjectiveKnapsackInstance eInstance);

		vector<double> v_weights;
		vector<double> v_profits;
		double d_capacity;
	};//class CBinaryKnapsackEvaluation : public CBinaryEvaluation


	class CBinaryMaxCutEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryMaxCutEvaluation(EBinaryBiObjectiveMaxCutInstance eInstance, int iObjectiveIndex);

	protected:
		virtual double t_evaluate(vector<bool> &vSolution);

	private:
		void v_load(EBinaryBiObjectiveMaxCutInstance eInstance, int iObjectiveIndex);
		static string s_get_definition_file_path(EBinaryBiObjectiveMaxCutInstance eInstance, int iObjectiveIndex);

		vector<int> v_start_nodes;
		vector<int> v_end_nodes;
		vector<double> v_weights;
	};//class CBinaryMaxCutEvaluation : public CBinaryEvaluation
}//namespace Evaluations
