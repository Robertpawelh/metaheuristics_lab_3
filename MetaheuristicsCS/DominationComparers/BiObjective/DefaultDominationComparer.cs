using System;

namespace DominationComparers.BiObjective
{
    class DefaultDominationComparer : IDominationComparer
    {
        public int Compare(Tuple<double, double> objectiveValues1, Tuple<double, double> objectiveValues2)
        {
            bool atLeastOneBetter = objectiveValues1.Item1 > objectiveValues2.Item1 || objectiveValues1.Item2 > objectiveValues2.Item2;
            bool atLeastOneWorse = objectiveValues1.Item1 < objectiveValues2.Item1 || objectiveValues1.Item2 < objectiveValues2.Item2;
            
            return Convert.ToInt32(atLeastOneBetter) - Convert.ToInt32(atLeastOneWorse);
        }
    }
}
