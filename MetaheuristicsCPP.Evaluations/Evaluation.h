#pragma once

#include "Constraint.h"

#include <utility>
#include <vector>

using namespace Constraints;

using namespace std;

namespace Evaluations
{
	template <typename TElement>
	class IEvaluationProfile
	{
	public:
		IEvaluationProfile() = default;

		IEvaluationProfile(const IEvaluationProfile<TElement> &cOther) = delete;
		IEvaluationProfile(IEvaluationProfile<TElement> &&cOther) = delete;

		virtual ~IEvaluationProfile() = default;

		virtual int iGetSize() = 0;
		virtual IConstraint<TElement> &cGetConstraint() = 0;

		IEvaluationProfile<TElement>& operator=(const IEvaluationProfile<TElement> &cOther) = delete;
		IEvaluationProfile<TElement>& operator=(IEvaluationProfile<TElement> &&cOther) = delete;
	};//class IEvaluationProfile


	template <typename TElement, typename TResult>
	class IEvaluation : public IEvaluationProfile<TElement>
	{
	public:
		virtual TResult tEvaluate(vector<TElement> &vSolution) = 0;
		virtual TResult &tGetMaxValue() = 0;

		virtual vector<TResult*> &vGetOptimalParetoFront() = 0;

		virtual long long iGetFFE() = 0;
	};//class IEvaluation : public IEvaluationProfile<TElement>


	template <typename TElement, typename TResult>
	class CEvaluation : public IEvaluation<TElement, TResult>
	{
	public:
		CEvaluation(int iSize, TResult tMaxValue) : i_size(iSize), t_max_value(tMaxValue), i_ffe(0) { }

		virtual ~CEvaluation()
		{
			for (size_t i = 0; i < v_optimal_pareto_front.size(); i++)
			{
				delete v_optimal_pareto_front[i];
			}//for (size_t i = 0; i < v_optimal_pareto_front.size(); i++)
		}//virtual ~CEvaluation()

		virtual TResult tEvaluate(vector<TElement> &vSolution) final
		{
			TResult t_value = t_evaluate(vSolution);
			i_ffe++;

			return t_value;
		}//virtual double dEvaluate(vector<TElement> &vSolution) final

		virtual int iGetSize() { return i_size; }
		virtual TResult &tGetMaxValue() { return t_max_value; }
		virtual vector<TResult*> &vGetOptimalParetoFront() { return v_optimal_pareto_front; }
		virtual long long iGetFFE() { return i_ffe; }

		CEvaluation<TElement, TResult>& operator=(const CEvaluation<TElement, TResult> &cOther) = delete;
		CEvaluation<TElement, TResult>& operator=(CEvaluation<TElement, TResult> &&cOther) = delete;

	protected:
		virtual TResult t_evaluate(vector<TElement> &vSolution) = 0;

		void v_set_size(int iSize) { i_size = iSize; }
		void v_set_max_value(TResult tMaxValue) { t_max_value = tMaxValue; }

		vector<TResult*> v_optimal_pareto_front;

	private:
		int i_size;
		TResult t_max_value;
		long long i_ffe;
	};//class CEvaluation : public IEvaluation<TElement, TResult>


	template <typename TElement, typename TResult>
	class CProxyEvaluation : public IEvaluation<TElement, TResult>
	{
	public:
		CProxyEvaluation(IEvaluation<TElement, TResult> **ppcEvaluation)
			: ppc_evaluation(ppcEvaluation)
		{

		}//CProxyEvaluation(IEvaluation<TElement, TResult> *ppcEvaluation)

		virtual TResult tEvaluate(vector<TElement> &vSolution) { return (*ppc_evaluation)->tEvaluate(vSolution); }

		virtual int iGetSize() { return (*ppc_evaluation)->iGetSize(); };
		virtual TResult &tGetMaxValue() { return (*ppc_evaluation)->tGetMaxValue(); }
		virtual vector<TResult*> &vGetOptimalParetoFront() { return (*ppc_evaluation)->vGetOptimalParetoFront(); }
		virtual IConstraint<double> &cGetConstraint() { return (*ppc_evaluation)->cGetConstraint(); }

		virtual long long iGetFFE() { return (*ppc_evaluation)->iGetFFE(); }

	private:
		IEvaluation<TElement, TResult> **ppc_evaluation;
	};//class CProxyEvaluation : public IEvaluation<TElement, TResult>


	template <typename TElement>
	class CVerticalScalingEvaluation : public CEvaluation<TElement, double>
	{
	public:
		CVerticalScalingEvaluation(IEvaluation<TElement, double> &cEvaluation, double dFactor)
			: CEvaluation<TElement, double>(cEvaluation.iGetSize(), dFactor * cEvaluation.tGetMaxValue()), c_evaluation(cEvaluation), d_factor(dFactor)
		{

		}//CVerticalScalingEvaluation(IEvaluation<TElement, double> &cEvaluation, double dFactor)

		virtual IConstraint<TElement> &cGetConstraint() { return c_evaluation.cGetConstraint(); }

	protected:
		virtual double t_evaluate(vector<TElement> &vSolution)
		{
			return d_factor * c_evaluation.tEvaluate(vSolution);
		}//virtual double t_evaluate(vector<TElement> &vSolution)

	private:
		IEvaluation<TElement, double> &c_evaluation;
		double d_factor;
	};//class CVerticalScalingEvaluation : public CEvaluation<TElement, double>
}//namespace Evaluations
