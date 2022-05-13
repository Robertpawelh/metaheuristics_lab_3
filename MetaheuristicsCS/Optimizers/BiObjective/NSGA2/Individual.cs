using System;
using System.Collections.Generic;


namespace Optimizers.BiObjective.NSGA2
{
    class Individual<Element> : Framework.PopulationOptimizers.Individual<Element, Tuple<double, double>>
    {
        public double CrowdingDistance { get; set; }
        public int DominationCounter { get; set; }
        public int FrontIndex { get; set; }

        public List<Individual<Element>> Dominates { get; }

        public Individual(Framework.PopulationOptimizers.Individual<Element, Tuple<double, double>> other)
            : base(other)
        {
            Dominates = new List<Individual<Element>>();
        }
    }
}
