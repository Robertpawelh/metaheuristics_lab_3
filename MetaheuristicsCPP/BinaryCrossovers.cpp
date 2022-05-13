#include "BinaryCrossovers.h"

using namespace Crossovers;


CBinaryOnePointCrossover::CBinaryOnePointCrossover(double dProbability, mt19937 &cRandomEngine)
	: CCrossover<bool>(dProbability, cRandomEngine)
{

}//CBinaryOnePointCrossover::CBinaryOnePointCrossover(double dProbability, mt19937 &cRandomEngine)

bool CBinaryOnePointCrossover::bCross(vector<bool> &vParent0, vector<bool> &vParent1, vector<bool> &vChild0, vector<bool> &vChild1)
{
	bool b_successful_crossover = false;

	uniform_real_distribution<double> c_uniform_distr;

	if (c_uniform_distr(c_random_engine) <= dGetProbability())
	{
		uniform_int_distribution<size_t> c_cross_point_distr(0, vParent0.size());
		size_t i_cross_point = c_cross_point_distr(c_random_engine);

		for (size_t i = 0; i < i_cross_point; i++)
		{
			vChild0[i] = vParent0[i];
			vChild1[i] = vParent1[i];
		}//for (size_t i = 0; i < i_cross_point; i++)

		for (size_t i = i_cross_point; i < vParent0.size(); i++)
		{
			vChild0[i] = vParent1[i];
			vChild1[i] = vParent0[i];
		}//for (size_t i = i_cross_point; i < vParent0.size(); i++)

		b_successful_crossover = true;
	}//if (c_uniform_distr(c_random_engine) <= dGetProbability())

	return b_successful_crossover;
}//bool CBinaryOnePointCrossover::bCross(vector<bool> &vParent0, vector<bool> &vParent1, vector<bool> &vChild0, vector<bool> &vChild1)


CBinaryUniformCrossover::CBinaryUniformCrossover(double dProbability, mt19937 &cRandomEngine)
	: CCrossover<bool>(dProbability, cRandomEngine)
{

}//CBinaryUniformCrossover::CBinaryUniformCrossover(double dProbability, mt19937 &cRandomEngine)

bool CBinaryUniformCrossover::bCross(vector<bool> &vParent0, vector<bool> &vParent1, vector<bool> &vChild0, vector<bool> &vChild1)
{
	bool b_successful_crossover = false;

	uniform_real_distribution<double> c_uniform_distr;

	if (c_uniform_distr(c_random_engine) <= dGetProbability())
	{
		bernoulli_distribution c_parent_distr;

		for (size_t i = 0; i < vParent0.size(); i++)
		{
			if (c_parent_distr(c_random_engine))
			{
				vChild0[i] = vParent0[i];
				vChild1[i] = vParent1[i];
			}//if (c_parent_distr(c_random_engine))
			else
			{
				vChild0[i] = vParent1[i];
				vChild1[i] = vParent0[i];
			}//else if (c_parent_distr(c_random_engine))
		}//for (size_t i = i_cross_point; i < vParent0.size(); i++)

		b_successful_crossover = true;
	}//if (c_uniform_distr(c_random_engine) <= dGetProbability())

	return b_successful_crossover;
}//bool CBinaryUniformCrossover::bCross(vector<bool> &vParent0, vector<bool> &vParent1, vector<bool> &vChild0, vector<bool> &vChild1)