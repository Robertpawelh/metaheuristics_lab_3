#pragma once

#include "BinaryEvaluationInstances.h"
#include "BinaryConstraints.h"
#include "Evaluation.h"

#include <BinaryEvaluations.h>
#include <BinaryEvaluationInstances.h>

using namespace System::Collections::Generic;

namespace EvaluationsCLI
{
	public ref class CBinaryEvaluation : public IEvaluation<bool, double>
	{
	public:
		CBinaryEvaluation(Evaluations::IEvaluation<bool, double> *pcNativeBinaryEvaluation);

		virtual ~CBinaryEvaluation();
		!CBinaryEvaluation();

		virtual double tEvaluate(IList<bool> ^lSolution);

		virtual property int iSize
		{
			int get() { return pc_native_binary_evaluation->iGetSize(); }
		}//virtual property int iSize

		virtual property double tMaxValue
		{
			double get() { return pc_native_binary_evaluation->tGetMaxValue(); }
		}//virtual property double tMaxValue

		virtual property List<double>^ lOptimalParetoFront
		{
			List<double>^ get() { return l_optimal_pareto_front; }
		}//virtual property IList<double>^ lOptimalParetoFront

		virtual property ConstraintsCLI::IConstraint<bool>^ pcConstraint
		{
			ConstraintsCLI::IConstraint<bool>^ get() { return gcnew ConstraintsCLI::CBinaryConstraint(pc_native_binary_evaluation->cGetConstraint()); }
		}//virtual property ConstraintsCLI::IConstraint<bool>^ pcConstraint

		virtual property long long iFFE
		{
			long long get() { return pc_native_binary_evaluation->iGetFFE(); }
		}//virtual property long long iFFE

	private:
		Evaluations::IEvaluation<bool, double> *pc_native_binary_evaluation;

		List<double>^ l_optimal_pareto_front;
	};//public ref class CBinaryEvaluation : public IEvaluation<bool, double>


	public ref class CBinaryOneMaxEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryOneMaxEvaluation(int iSize);
	};//public ref class CBinaryOneMaxEvaluation : public CBinaryEvaluation


	public ref class CBinaryStandardDeceptiveConcatenationEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryStandardDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks);
	};//public ref class CBinaryStandardDeceptiveConcatenationEvaluation : public CBinaryEvaluation


	public ref class CBinaryBimodalDeceptiveConcatenationEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryBimodalDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks);
	};//public ref class CBinaryBimodalDeceptiveConcatenationEvaluation : public CBinaryEvaluation


	public ref class CBinaryIsingSpinGlassEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryIsingSpinGlassEvaluation(int iSize);
		CBinaryIsingSpinGlassEvaluation(int iSize, int iProblemSeed);
	};//public ref class CBinaryIsingSpinGlassEvaluation : public CBinaryEvaluation


	public ref class CBinaryMax3SatEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryMax3SatEvaluation(int iSize);
		CBinaryMax3SatEvaluation(int iSize, int iProblemSeed);
		CBinaryMax3SatEvaluation(int iSize, int iProblemSeed, float fClauseRatio);
	};//public ref class CBinaryMax3SatEvaluation : public CBinaryEvaluation


	public ref class CBinaryNKLandscapesEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryNKLandscapesEvaluation(int iSize);
		CBinaryNKLandscapesEvaluation(int iSize, int iProblemSeed);
	};//public ref class CBinaryNKLandscapesEvaluation : public CBinaryEvaluation


	public ref class CBinaryKnapsackEvaluation : public CBinaryEvaluation
	{
	public:
		CBinaryKnapsackEvaluation(EBinaryKnapsackInstance eInstance);

		double dCalculateWeight(IList<bool> ^lSolution);

		property IList<double> ^lWeights
		{
			IList<double> ^get() { return l_weights; }
		}//property IList<double> ^lWeights

		property IList<double> ^lProfits
		{
			IList<double> ^get() { return l_profits; }
		}//property IList<double> ^lProfits

		property double dCapacity
		{
			double get() { return pc_native_binary_knapsack_evaluation->dGetCapacity(); }
		}//property double dCapacity

	private:
		Evaluations::CBinaryKnapsackEvaluation *pc_native_binary_knapsack_evaluation;

		IList<double> ^l_weights;
		IList<double> ^l_profits;
	};//public ref class CBinaryKnapsackEvaluation : public CBinaryEvaluation
}//namespace EvaluationsCLI