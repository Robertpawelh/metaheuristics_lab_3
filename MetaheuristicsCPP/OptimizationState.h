#pragma once

#include <vector>

using namespace std;

namespace Optimizers
{
	template <typename TElement, typename TEvaluationResult, class TResult>
	class IOptimizationState
	{
	public:
		IOptimizationState() = default;

		IOptimizationState(const IOptimizationState<TElement, TEvaluationResult, TResult> &cOther) = delete;
		IOptimizationState(IOptimizationState<TElement, TEvaluationResult, TResult> &&cOther) = delete;

		virtual ~IOptimizationState() = default;

		virtual bool bUpdate(const vector<TElement> &vSolution, const TEvaluationResult &tValue, long long iIterationNumber, long long iFFE, double dTime, bool bOnlyImprovements) = 0;
		
		virtual bool bGlobalOptimumFound() = 0;
		virtual void vReset() = 0;

		virtual TResult *pcGetResult() = 0;

		IOptimizationState<TElement, TEvaluationResult, TResult>& operator=(const IOptimizationState<TElement, TEvaluationResult, TResult> &cOther) = delete;
		IOptimizationState<TElement, TEvaluationResult, TResult>& operator=(IOptimizationState<TElement, TEvaluationResult, TResult> &&cOther) = delete;
	};//class IOptimizationState


	template <typename TElement, typename TEvaluationResult, class TResult>
	class COptimizationState : public IOptimizationState<TElement, TEvaluationResult, TResult>
	{
	public:
		COptimizationState()
		{
			pc_result = nullptr;
		};//COptimizationState()

		virtual ~COptimizationState()
		{
			vReset();
		};//virtual ~COptimizationState()

		virtual void vReset()
		{
			delete pc_result;
			pc_result = nullptr;
		}//virtual void vReset()

		virtual TResult *pcGetResult() { return pc_result; }

	protected:
		TResult *pc_result;
	};//class COptimizationState : public IOptimizationState<TElement, TEvaluationResult, TResult>
}//namespace Optimizers