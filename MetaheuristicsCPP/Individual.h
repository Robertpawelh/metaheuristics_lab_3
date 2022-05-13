#pragma once

#include "Mutation.h"

#include <Evaluation.h>
#include <vector>

using namespace Mutations;

using namespace Evaluations;
using namespace std;

namespace Optimizers
{
	template <typename TElement, typename TEvaluationResult>
	class CIndividual
	{
	public:
		CIndividual(vector<TElement> *pvGenotype, IEvaluation<TElement, TEvaluationResult> &cEvaluation, IMutation<TElement> &cMutation)
			: pv_genotype(pvGenotype), c_evaluation(cEvaluation), c_mutation(cMutation)
		{
			b_is_evaluated = false;
		}//CIndividual(vector<TElement> *pvGenotype, IEvaluation<TElement, TEvaluationResult> &cEvaluation, IMutation<TElement> &cMutation)

		CIndividual(const CIndividual<TElement, TEvaluationResult> &cOther)
			: c_evaluation(cOther.c_evaluation), c_mutation(cOther.c_mutation)
		{
			pv_genotype = new vector<TElement>(*cOther.pv_genotype);

			t_fitness = cOther.t_fitness;
			b_is_evaluated = cOther.b_is_evaluated;
		}//CIndividual(const CIndividual<TElement, TEvaluationResult> &cOther)

		~CIndividual()
		{
			delete pv_genotype;
		}//~CIndividual()

		void vEvaluate()
		{
			if (!b_is_evaluated)
			{
				t_fitness = c_evaluation.tEvaluate(*pv_genotype);
				b_is_evaluated = true;
			}//if (!b_is_evaluated)
		}//double dEvaluate()

		bool bMutate()
		{
			bool b_successful_mutation = c_mutation.bMutate(*pv_genotype);

			if (b_successful_mutation)
			{
				b_is_evaluated = false;
			}//if (b_successful_mutation)

			return b_successful_mutation;
		}//bool bMutate()

		vector<TElement> &vGetGenotype() { return *pv_genotype; }
		TEvaluationResult &tGetFitness() { return t_fitness; }

	private:
		vector<TElement> *pv_genotype;

		IEvaluation<TElement, TEvaluationResult> &c_evaluation;
		IMutation<TElement> &c_mutation;

		bool b_is_evaluated;
		TEvaluationResult t_fitness;
	};//class CIndividual
}//namespace Optimizers
