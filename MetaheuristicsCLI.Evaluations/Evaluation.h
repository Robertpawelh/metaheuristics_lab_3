#pragma once

#include "Constraint.h"

#include <Evaluation.h>

using namespace System::Collections::Generic;

namespace EvaluationsCLI
{
	generic <typename TElement>
	public interface class IEvaluationProfile
	{
		property int iSize
		{
			int get();
		}//property int iSize

		property ConstraintsCLI::IConstraint<TElement>^ pcConstraint
		{
			ConstraintsCLI::IConstraint<TElement>^ get();
		}//property ConstraintsCLI::IConstraint<TElement>^ pcConstraint
	};//public interface class IEvaluationProfile


	generic <typename TElement, typename TResult>
	public interface class IEvaluation : public IEvaluationProfile<TElement>
	{
		TResult tEvaluate(IList<TElement> ^lSolution);

		property TResult tMaxValue
		{
			TResult get();
		}//property TResult dMaxValue

		property List<TResult>^ lOptimalParetoFront
		{
			List<TResult>^ get();
		}//property IList<TResult>^ lOptimalParetoFront

		property long long iFFE
		{
			long long get();
		}//property long long iFFE
	};//public interface class IEvaluation : public IEvaluationProfile<TElement>
}//namespace EvaluationsCLI