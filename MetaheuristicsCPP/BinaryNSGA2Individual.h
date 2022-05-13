#pragma once

#include "Individual.h"
#include "Mutation.h"

#include <Evaluation.h>
#include <utility>

using namespace Evaluations;
using namespace Mutations;

using namespace std;

namespace Optimizers
{
	class CBinaryNSGA2Individual : public CIndividual<bool, pair<double, double>>
	{
	public:
		CBinaryNSGA2Individual(const CIndividual<bool, pair<double, double>> &cOther);

		int iGetFrontIndex() { return i_front_index; }
		double dGetCrowdingDistance() { return d_crowding_distance; }
		vector<CBinaryNSGA2Individual*> &vGetIndividualsDominatedBy() { return v_individuals_dominated_by; }
		int iGetDominationCounter() { return i_domination_counter; }

		void vSetFrontIndex(int iFrontIndex) { i_front_index = iFrontIndex; }
		void vSetCrowdingDistance(double dCrowdingDistance) { d_crowding_distance = dCrowdingDistance; }
		void vSetDominationCounter(int iDominationCounter) { i_domination_counter = iDominationCounter; }

	private:
		int i_front_index;
		double d_crowding_distance;

		vector<CBinaryNSGA2Individual*> v_individuals_dominated_by;
		int i_domination_counter;
	};//class CBinaryNSGA2Individual : public CIndividual<bool, pair<double, double>>
}//namespace Optimizers