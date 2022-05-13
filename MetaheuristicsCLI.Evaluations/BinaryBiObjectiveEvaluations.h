#pragma once

#include "BinaryEvaluationInstances.h"
#include "BinaryConstraints.h"
#include "Evaluation.h"

#include <BinaryBiObjectiveEvaluations.h>
#include <utility>

using namespace std;

using namespace System;
using namespace System::Collections::Generic;

namespace EvaluationsCLI
{
	public ref class CBinaryBiObjectiveEvaluation : public IEvaluation<bool, Tuple<double, double>^>
	{
	public:
		CBinaryBiObjectiveEvaluation(Evaluations::IEvaluation<bool, pair<double, double>> *pcNativeBinaryBiObjectiveEvaluation);

		virtual ~CBinaryBiObjectiveEvaluation();
		!CBinaryBiObjectiveEvaluation();

		virtual Tuple<double, double>^ tEvaluate(IList<bool> ^lSolution);

		virtual property int iSize
		{
			int get() { return pc_native_binary_evaluation->iGetSize(); }
		}//virtual property int iSize

		virtual property Tuple<double, double>^ tMaxValue
		{
			Tuple<double, double>^ get() { return pc_map(pc_native_binary_evaluation->tGetMaxValue()); }
		}//virtual property double tMaxValue

		virtual property List<Tuple<double, double>^>^ lOptimalParetoFront
		{
			List<Tuple<double, double>^>^ get() { return l_optimal_pareto_front; }
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
		Tuple<double, double>^ pc_map(const pair<double, double> &pPair);

		Evaluations::IEvaluation<bool, pair<double, double>> *pc_native_binary_evaluation;

		List<Tuple<double, double>^>^ l_optimal_pareto_front;
	};//public ref class CBinaryBiObjectiveEvaluation : public IEvaluation<bool, Tuple<double, double>^>


	public ref class CBinaryZeroMaxOneMaxEvaluation : public CBinaryBiObjectiveEvaluation
	{
	public:
		CBinaryZeroMaxOneMaxEvaluation(int iSize);
	};//public ref class CBinaryZeroMaxOneMaxEvaluation : public CBinaryBiObjectiveEvaluation


	public ref class CBinaryTrapInvTrapEvaluation : public CBinaryBiObjectiveEvaluation
	{
	public:
		CBinaryTrapInvTrapEvaluation(int iBlockSize, int iNumberOfBlocks);
	};//public ref class CBinaryTrapInvTrapEvaluation : public CBinaryBiObjectiveEvaluation


	public ref class CBinaryLOTZEvaluation : public CBinaryBiObjectiveEvaluation
	{
	public:
		CBinaryLOTZEvaluation(int iSize);
	};//public ref class CBinaryLOTZEvaluation : public CBinaryBiObjectiveEvaluation


	public ref class CBinaryMOKnapsackEvaluation : public CBinaryBiObjectiveEvaluation
	{
	public:
		CBinaryMOKnapsackEvaluation(EBinaryBiObjectiveKnapsackInstance eInstance);
	};//public ref class CBinaryMOKnapsackEvaluation : public CBinaryBiObjectiveEvaluation


	public ref class CBinaryMOMaxCutEvaluation : public CBinaryBiObjectiveEvaluation
	{
	public:
		CBinaryMOMaxCutEvaluation(EBinaryBiObjectiveMaxCutInstance eInstance);
	};//public ref class CBinaryMaxCutEvaluation : public CBinaryBiObjectiveEvaluation
}//namespace EvaluationsCLI