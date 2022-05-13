#pragma once

#include "BinaryKnapsackIndividual.h"
#include "VectorUtils.h"

#include <random>
#include <vector>

using namespace Optimizers;

using namespace std;

namespace Selections
{
	class IBinaryKnapsackSelection
	{
	public:
		virtual ~IBinaryKnapsackSelection() = default;

		virtual void vSelect(vector<CBinaryKnapsackIndividual*> **ppvPopulation) = 0;
	};//class IBinaryKnapsackSelection


	class CBinaryKnapsackSelection : public IBinaryKnapsackSelection
	{
	public:
		CBinaryKnapsackSelection(mt19937 &cRandomEngine);

		virtual void vSelect(vector<CBinaryKnapsackIndividual*> **ppvPopulation) final;

	protected:
		virtual void v_add_to_new_population(vector<CBinaryKnapsackIndividual*> &vPopulation, vector<CBinaryKnapsackIndividual*> &vNewPopulation) = 0;

		mt19937 &c_random_engine;
	};//class CSelection : public ISelection<TElement>
}//namespace Selections