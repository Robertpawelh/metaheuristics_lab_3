#include "BinaryKnapsackSelection.h"

using namespace Selections;


CBinaryKnapsackSelection::CBinaryKnapsackSelection(mt19937 &cRandomEngine)
	: c_random_engine(cRandomEngine)
{

}//CBinaryKnapsackSelection::CBinaryKnapsackSelection(mt19937 &cRandomEngine)

void CBinaryKnapsackSelection::vSelect(vector<CBinaryKnapsackIndividual*> **ppvPopulation)
{
	vector<CBinaryKnapsackIndividual*> *pv_population = *ppvPopulation;

	vector<CBinaryKnapsackIndividual*> *pv_new_population = new vector<CBinaryKnapsackIndividual*>();
	pv_new_population->reserve(pv_population->size());

	v_add_to_new_population(*pv_population, *pv_new_population);

	VectorUtils::vClear(*pv_population);
	delete pv_population;

	*ppvPopulation = pv_new_population;
}//void CBinaryKnapsackSelection::vSelect(vector<CBinaryKnapsackIndividual*> **ppvPopulation)