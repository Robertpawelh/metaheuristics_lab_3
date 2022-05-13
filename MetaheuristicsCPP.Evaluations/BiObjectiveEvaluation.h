#pragma once

#include "Evaluation.h"

#include <utility>
#include <vector>

using namespace std;

namespace Evaluations
{
	template <typename TElement>
	class CBiObjectiveEvaluation : public CEvaluation<TElement, pair<double, double>>
	{
	public:
		CBiObjectiveEvaluation(IEvaluation<TElement, double> *pcEvaluation0, IEvaluation<TElement, double> *pcEvaluation1)
			: CEvaluation<TElement, pair<double, double>>(pcEvaluation0->iGetSize(), make_pair(pcEvaluation0->tGetMaxValue(), pcEvaluation1->tGetMaxValue()))
		{
			pc_evaluation_0 = pcEvaluation0;
			pc_evaluation_1 = pcEvaluation1;
		}//CBiObjectiveEvaluation(IEvaluation<TElement, double> *pcEvaluation0, IEvaluation<TElement, double> *pcEvaluation1)

		virtual ~CBiObjectiveEvaluation()
		{
			delete pc_evaluation_0;
			delete pc_evaluation_1;
		}//virtual ~CBiObjectiveEvaluation()

	protected:
		virtual pair<double, double> t_evaluate(vector<TElement> &vSolution)
		{
			return make_pair(pc_evaluation_0->tEvaluate(vSolution), pc_evaluation_1->tEvaluate(vSolution));
		}//virtual pair<double, double> t_evaluate(vector<TElement> &vSolution)

	protected:
		IEvaluation<TElement, double> *pc_evaluation_0;
		IEvaluation<TElement, double> *pc_evaluation_1;
	};//class CBiObjectiveEvaluation : public CEvaluation<TElement, vector<double>>
}//namespace Evaluations