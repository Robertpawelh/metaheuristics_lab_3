#pragma once

#include "DominationComparer.h"

#include <utility>

using namespace std;

namespace DominationComparers
{
	class CDefaultDominationComparer : public IDominationComparer
	{
	public:
		virtual int iCompare(const pair<double, double> &pObjectiveValues0, const pair<double, double> &pObjectiveValues1);
	};//class CDefaultDominationComparer : public IDominationComparer
}//namespace DominationComparers