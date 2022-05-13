#include "DominationComparers.h"

using namespace DominationComparers;


int CDefaultDominationComparer::iCompare(const pair<double, double> &pObjectiveValues0, const pair<double, double> &pObjectiveValues1)
{
	bool b_at_least_one_better = pObjectiveValues0.first > pObjectiveValues1.first || pObjectiveValues0.second > pObjectiveValues1.second;
	bool b_at_least_one_worse = pObjectiveValues0.first < pObjectiveValues1.first || pObjectiveValues0.second < pObjectiveValues1.second;

	if (b_at_least_one_better && !b_at_least_one_worse) return 1;
	if (!b_at_least_one_better && b_at_least_one_worse) return -1;

	return 0;
}//int CDefaultDominationComparer::iCompare(const pair<double, double> &pObjectiveValues0, const pair<double, double> &pObjectiveValues1)