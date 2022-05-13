#pragma once

#include "Crossover.h"

#include <random>
#include <vector>

using namespace std;

namespace Crossovers
{
	class CBinaryOnePointCrossover : public CCrossover<bool>
	{
	public:
		CBinaryOnePointCrossover(double dProbability, mt19937 &cRandomEngine);

		virtual bool bCross(vector<bool> &vParent0, vector<bool> &vParent1, vector<bool> &vChild0, vector<bool> &vChild1);
	};//class CBinaryOnePointCrossover : public CCrossover<bool>


	class CBinaryUniformCrossover : public CCrossover<bool>
	{
	public:
		CBinaryUniformCrossover(double dProbability, mt19937 &cRandomEngine);

		virtual bool bCross(vector<bool> &vParent0, vector<bool> &vParent1, vector<bool> &vChild0, vector<bool> &vChild1);
	};//class CBinaryUniformCrossover : public CCrossover<bool>
}//namespace Crossovers