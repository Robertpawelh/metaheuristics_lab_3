#include "ParetoFront.h"

using namespace Optimizers;

CParetoFront::CParetoFront(pair<double, double> &pObjectiveMaxValues, vector<pair<double, double>*> &vOptimalParetoFront, IDominationComparer &cDominationComparer)
	: p_objective_max_values(pObjectiveMaxValues), v_optimal_pareto_front(vOptimalParetoFront), c_domination_comparer(cDominationComparer)
{

}//CParetoFront::CParetoFront(pair<double, double> &vObjectiveMaxValues, IDominationComparer &cDominationComparer)

CParetoFront::~CParetoFront()
{
	VectorUtils::vClear(v_pareto_front);
}//CParetoFront::~CParetoFront()

bool CParetoFront::bAdd(const pair<double, double> &pObjectiveValues)
{
	bool b_added = false;

	bool b_dominated = false;
	
	int i_dominated_individuals = 0;
	int i_domination;

	for (size_t i = 0; i < v_pareto_front.size() && !b_dominated; i++)
	{
		i_domination = c_domination_comparer.iCompare(pObjectiveValues, *v_pareto_front[i - i_dominated_individuals]);

		if (i_domination > 0)
		{
			swap(v_pareto_front[i - i_dominated_individuals], v_pareto_front[v_pareto_front.size() - i_dominated_individuals - 1]);
			i_dominated_individuals++;
		}//if (i_domination > 0)
		else if (i_domination < 0)
		{
			b_dominated = true;
		}//else if (i_domination > 0)
	}//for (size_t i = 0; i < v_pareto_front.size() && !b_dominated; i++)

	if (!b_dominated)
	{
		if (i_dominated_individuals > 0)
		{
			VectorUtils::vErase(v_pareto_front, v_pareto_front.size() - i_dominated_individuals);
		}//if (i_dominated_individuals > 0)

		v_sort();
		b_added = b_insert(pObjectiveValues);
	}//if (!b_dominated)

	return b_added;
}//bool CParetoFront::bAdd(const pair<double, double> &pObjectiveValues)

double CParetoFront::dCalculateHyperVolume()
{
	double d_hyper_volume = 0;

	if (!v_pareto_front.empty())
	{
		d_hyper_volume += (v_pareto_front.front()->first - 0) * (p_objective_max_values.second - v_pareto_front.front()->second);

		for (size_t i = 1; i < v_pareto_front.size(); i++)
		{
			d_hyper_volume += (v_pareto_front[i]->first - v_pareto_front[i - 1]->first) * (p_objective_max_values.second - v_pareto_front[i]->second);
		}//for (size_t i = 1; i < v_pareto_front.size(); i++)

		d_hyper_volume += (p_objective_max_values.first - v_pareto_front.back()->first) * (p_objective_max_values.second - 0);
	}//if (!v_pareto_front.empty())

	return d_hyper_volume;
}//double CParetoFront::dCalculateHyperVolume()

double CParetoFront::dCalculateInversedGenerationalDistance()
{
	double d_igd = DBL_MAX;

	if (!v_pareto_front.empty() && !v_optimal_pareto_front.empty())
	{
		d_igd = 0;

		for (size_t i = 0; i < v_optimal_pareto_front.size(); i++)
		{
			d_igd += d_calculate_min_distance(*v_optimal_pareto_front[i], v_pareto_front);
		}//for (size_t i = 0; i < v_optimal_pareto_front.size(); i++)

		d_igd /= v_optimal_pareto_front.size();
	}//if (!v_pareto_front.empty() && !v_optimal_pareto_front.empty())

	return d_igd;
}//double CParetoFront::dCalculateInversedGenerationalDistance()

bool CParetoFront::b_insert(const pair<double, double> &pObjectiveValues)
{
	bool b_found = false;

	pair<double, double> *pp_objective_values = new pair<double, double>(pObjectiveValues);

	if (v_pareto_front.empty())
	{
		v_pareto_front.push_back(pp_objective_values);
	}//if (v_pareto_front.empty())
	else
	{
		bool b_inserted = false;

		for (size_t i = 0; i < v_pareto_front.size() && !b_inserted; i++)
		{
			if (pp_objective_values->first < v_pareto_front[i]->first)
			{
				v_pareto_front.insert(v_pareto_front.begin() + i, pp_objective_values);
				b_inserted = true;
			}//if (pp_objective_values->first < v_pareto_front[i]->first)
			else if (pp_objective_values->first == v_pareto_front[i]->first)
			{
				if (pp_objective_values->second == v_pareto_front[i]->second)
				{
					b_inserted = true;
					b_found = true;
				}//if (pp_objective_values->second == v_pareto_front[i]->second)
				else if (pp_objective_values->second > v_pareto_front[i]->second)
				{
					v_pareto_front.insert(v_pareto_front.begin() + i, pp_objective_values);
					b_inserted = true;
				}//else if (pp_objective_values->second > v_pareto_front[i]->second)
			}//else if (pp_objective_values->first == v_pareto_front[i]->first)
		}//for (size_t i = 0; i < v_pareto_front.size() && !b_inserted; i++)

		if (!b_inserted)
		{
			v_pareto_front.push_back(pp_objective_values);
		}//if (!b_inserted)
	}//else if (v_pareto_front.empty())

	return !b_found;
}//bool CParetoFront::b_insert(const pair<double, double> &pObjectiveValues)

void CParetoFront::v_sort()
{
	sort(v_pareto_front.begin(), v_pareto_front.end(), [](pair<double, double> *ppObjectiveValues0, pair<double, double> *ppObjectiveValues1)
	{
		return ppObjectiveValues0->first < ppObjectiveValues1->first || ppObjectiveValues0->first == ppObjectiveValues1->first && ppObjectiveValues0->second > ppObjectiveValues1->second;
	});//sort(v_pareto_front.begin(), v_pareto_front.end(), [](pair<double, double> *ppObjectiveValues0, pair<double, double> *ppObjectiveValues1)
}//void CParetoFront::v_sort()

double CParetoFront::d_calculate_square_distance(pair<double, double> &pObjectiveValues0, pair<double, double> &pObjectiveValues1, double dMaxValue)
{
	double d_square_distance = (pObjectiveValues0.first - pObjectiveValues1.first) * (pObjectiveValues0.first - pObjectiveValues1.first);

	if (d_square_distance < dMaxValue)
	{
		d_square_distance += (pObjectiveValues0.second - pObjectiveValues1.second) * (pObjectiveValues0.second - pObjectiveValues1.second);
	}//if (d_square_distance < dMaxValue)

	return d_square_distance <= dMaxValue ? d_square_distance : dMaxValue;
}//double CParetoFront::d_calculate_distance(pair<double, double> &pObjectiveValues0, pair<double, double> &pObjectiveValues1, double dMaxValue)

double CParetoFront::d_calculate_min_distance(pair<double, double> &pObjectiveValues, vector<pair<double, double>*> &vParetoFront)
{
	double d_min_square_distance = DBL_MAX;

	for (size_t i = 0; i < vParetoFront.size(); i++)
	{
		d_min_square_distance = d_calculate_square_distance(pObjectiveValues, *vParetoFront[i], d_min_square_distance);
	}//for (size_t i = 0; i < vParetoFront.size(); i++)

	return sqrt(d_min_square_distance);
}//double CParetoFront::d_calculate_min_distance(pair<double, double> &pObjectiveValues, vector<pair<double, double>*> &vParetoFront)