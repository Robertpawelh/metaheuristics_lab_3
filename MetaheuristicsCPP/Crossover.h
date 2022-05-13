#pragma once

#include <random>
#include <vector>

using namespace std;

namespace Crossovers
{
	template <typename TElement>
	class ICrossover
	{
	public:
		virtual ~ICrossover() = default;

		virtual bool bCross(vector<TElement> &vParent0, vector<TElement> &vParent1, vector<TElement> &vChild0, vector<TElement> &vChild1) = 0;

		virtual double dGetProbability() = 0;

		virtual void vSetProbability(double dProbability) = 0;
	};//class ICrossover


	template <typename TElement>
	class CCrossover : public ICrossover<TElement>
	{
	public:
		CCrossover(double dProbability, mt19937 &cRandomEngine)
			: d_probability(dProbability), c_random_engine(cRandomEngine)
		{

		}//CCrossover(double dProbability, mt19937 &cRandomEngine)

		virtual double dGetProbability() { return d_probability; }

		virtual void vSetProbability(double dProbability) { d_probability = dProbability; }

	protected:
		mt19937 &c_random_engine;

	private:
		double d_probability;
	};//class CCrossover : public ICrossover<TElement>
}//namespace Crossovers