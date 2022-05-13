#pragma once

#include "Individual.h"
#include "VectorUtils.h"

#include <random>
#include <vector>

using namespace Optimizers;

using namespace std;

namespace Selections
{
	template <typename TElement, typename TEvaluationResult>
	class ISelection
	{
	public:
		virtual ~ISelection() = default;

		virtual void vSelect(vector<CIndividual<TElement, TEvaluationResult>*> **ppvPopulation) = 0;
	};//class ISelection


	template <typename TElement, typename TEvaluationResult>
	class CSelection : public ISelection<TElement, TEvaluationResult>
	{
	public:
		CSelection(mt19937 &cRandomEngine, bool bClearPopulation = true)
			: c_random_engine(cRandomEngine), b_clear_population(bClearPopulation)
		{

		}//CSelection(mt19937 &cRandomEngine, bool bClearPopulation = true)

		virtual void vSelect(vector<CIndividual<TElement, TEvaluationResult>*> **ppvPopulation) final
		{
			vector<CIndividual<TElement, TEvaluationResult>*> *pv_population = *ppvPopulation;

			vector<CIndividual<TElement, TEvaluationResult>*> *pv_new_population = new vector<CIndividual<TElement, TEvaluationResult>*>();
			pv_new_population->reserve(pv_population->size());

			v_add_to_new_population(*pv_population, *pv_new_population);

			if (b_clear_population)
			{
				VectorUtils::vClear(*pv_population);
			}//if (b_clear_population)
			
			delete pv_population;

			*ppvPopulation = pv_new_population;
		}//virtual void vSelect(vector<CIndividual<TElement, TEvaluationResult>*> &vPopulation) final

	protected:
		virtual void v_add_to_new_population(vector<CIndividual<TElement, TEvaluationResult>*> &vPopulation, vector<CIndividual<TElement, TEvaluationResult>*> &vNewPopulation) = 0;

		mt19937 &c_random_engine;

	private:
		bool b_clear_population;
	};//class CSelection : public ISelection<TElement, TEvaluationResult>
}//namespace Selections