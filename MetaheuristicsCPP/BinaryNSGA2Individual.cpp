#include "BinaryNSGA2Individual.h"

using namespace Optimizers;

CBinaryNSGA2Individual::CBinaryNSGA2Individual(const CIndividual<bool, pair<double, double>> &cOther)
	: CIndividual<bool, pair<double, double>>(cOther)
{

}//CBinaryNSGA2Individual(const CIndividual<bool, pair<double, double>> &cOther)