#pragma once

#include <utility>

using namespace std;

namespace DominationComparers
{
	class IDominationComparer
	{
	public:
		virtual int iCompare(const pair<double, double> &pObjectiveValues0, const pair<double, double> &pObjectiveValues1) = 0;
	};//class IDominationComparer
}//namespace DominationComparers