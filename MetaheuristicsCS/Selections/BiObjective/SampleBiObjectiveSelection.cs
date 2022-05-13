using System;
using System.Collections.Generic;

using DominationComparers.BiObjective;
using Optimizers.Framework.PopulationOptimizers;
using Utility;

namespace Selections.BiObjective
{
    class SampleBiObjectiveSelection : ASelection<Tuple<double, double>>
    {
        private readonly Shuffler shuffler;
        private readonly IDominationComparer dominationComparer;

        public SampleBiObjectiveSelection(IDominationComparer dominationComparer, int? seed = null)
        {
            shuffler = new Shuffler(seed);
            this.dominationComparer = dominationComparer;
        }
        
        protected override void AddToNewPopulation<Element>(List<Individual<Element, Tuple<double, double>>> population, 
                                                            List<Individual<Element, Tuple<double, double>>> newPopulation)
        {
            List<int> indices = Utils.CreateIndexList(population.Count);
            shuffler.Shuffle(indices);

            for(int i = 0; i < population.Count; ++i)
            {
                Individual<Element, Tuple<double, double>> ith = population[i];
                Individual<Element, Tuple<double, double>> jth = population[indices[i]];

                Individual<Element, Tuple<double, double>> nonDominated = (dominationComparer.Compare(ith.Fitness, 
                                                                                                      jth.Fitness) >= 0) ? ith : jth;

                newPopulation.Add(new Individual<Element, Tuple<double, double>>(nonDominated));
            }
        }
    }
}
