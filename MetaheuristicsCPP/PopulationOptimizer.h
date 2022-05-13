#pragma once

#include "Generator.h"
#include "Individual.h"
#include "Mutation.h"
#include "OptimizationState.h"
#include "Optimizer.h"
#include "Selection.h"
#include "VectorUtils.h"

#include <vector>

using namespace Generators;
using namespace Mutations;
using namespace Selections;

using namespace std;

namespace Optimizers
{
	template <typename TElement, typename TEvaluationResult, class TOptimizationResult>
	class CPopulationOptimizer : public COptimizer<TElement, TEvaluationResult, TOptimizationResult>
	{
	public:
		CPopulationOptimizer(IEvaluation<TElement, TEvaluationResult> &cEvaluation, IStopCondition &cStopCondition, IOptimizationState<TElement, TEvaluationResult, TOptimizationResult> *pcState, IGenerator<TElement> &cGeneration, ISelection<TElement, TEvaluationResult> &cSelection, IMutation<TElement> &cMutation, int iPopulationSize)
			: COptimizer<TElement, TEvaluationResult, TOptimizationResult>(cEvaluation, cStopCondition, pcState), c_generation(cGeneration), c_selection(cSelection), c_mutation(cMutation), i_population_size(iPopulationSize)
		{
			pv_population = new vector<CIndividual<TElement, TEvaluationResult>*>();
		}//CPopulationOptimizer(IEvaluation<TElement, TEvaluationResult> &cEvaluation, IStopCondition &cStopCondition, COptimizationState<TElement, TEvaluationResult, TOptimizationResult> *pcState, IGenerator<TElement> &cGeneration, ISelection<TElement, TEvaluationResult> &cSelection, IMutation<TElement> &cMutation, int iPopulationSize)

		virtual ~CPopulationOptimizer()
		{
			v_clear_population();
			delete pv_population;
		}//virtual ~CPopulationOptimizer()

	protected:
		virtual void v_initialize(clock_t tStartTime)
		{
			v_clear_population();
			pv_population->reserve((size_t)i_population_size);

			for (int i = 0; i < i_population_size; i++)
			{
				pv_population->push_back(pc_create_individual());
			}//for (int i = 0; i < i_population_size; i++)

			v_evaluation();
			b_update_state();
		}//virtual void v_initialize(clock_t tStartTime)

		virtual void v_evaluation()
		{
			for (size_t i = 0; i < pv_population->size(); i++)
			{
				pv_population->at(i)->vEvaluate();
			}//for (size_t i = 0; i < pv_population->size(); i++)
		}//virtual void v_evaluation()

		virtual void v_selection()
		{
			c_selection.vSelect(&pv_population);
		}//virtual void v_selection()

		virtual void v_mutation()
		{
			for (size_t i = 0; i < pv_population->size(); i++)
			{
				pv_population->at(i)->bMutate();
			}//for (size_t i = 0; i < pv_population->size(); i++)
		}//virtual void v_mutation()

		void v_clear_population()
		{
			VectorUtils::vClear(*pv_population);
		}//void v_clear_population()

		bool b_update_state(bool bOnlyImprovements = true)
		{
			bool b_updated = false;

			for (size_t i = 0; i < pv_population->size(); i++)
			{
				CIndividual<TElement, TEvaluationResult> *pc_individual = pv_population->at(i);

				b_updated = COptimizer<TElement, TEvaluationResult, TOptimizationResult>::b_update_state(pc_individual->vGetGenotype(), pc_individual->tGetFitness(), bOnlyImprovements) || b_updated;
			}//for (size_t i = 0; i < pv_population->size(); i++)

			return b_updated;
		}//bool b_update_state(bool bOnlyImprovements = true)

		virtual CIndividual<TElement, TEvaluationResult> *pc_create_individual(vector<TElement> *pvGenotype = nullptr)
		{
			if (pvGenotype == nullptr)
			{
				pvGenotype = c_generation.pvCreate(this->c_evaluation.iGetSize());
			}//if (pvGenotype == nullptr)

			return new CIndividual<TElement, TEvaluationResult>(pvGenotype, this->c_evaluation, c_mutation);
		}//virtual CIndividual<TElement, TEvaluationResult> *pc_create_individual(vector<TElement> *pvGenotype = nullptr)

		int i_population_size;
		vector<CIndividual<TElement, TEvaluationResult>*> *pv_population;

		IGenerator<TElement> &c_generation;

		ISelection<TElement, TEvaluationResult> &c_selection;
		IMutation<TElement> &c_mutation;
	};//class CPopulationOptimizer : public COptimizer<TElement, TEvaluationResult, TOptimizationResult>
}//namespace Optimizers