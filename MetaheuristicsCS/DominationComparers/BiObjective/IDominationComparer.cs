using System;

namespace DominationComparers.BiObjective
{
    interface IDominationComparer
    {
        int Compare(Tuple<double, double> objectiveValues1, Tuple<double, double> objectiveValues2);
    }
}
