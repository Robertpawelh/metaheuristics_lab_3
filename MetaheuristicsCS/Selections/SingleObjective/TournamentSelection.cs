using System.Collections.Generic;

using Optimizers.Framework.PopulationOptimizers;
using Utility;

namespace Selections.SingleObjective
{
    sealed class TournamentSelection : ASelection<double>
    {
        private readonly UniformIntegerRandom rng;
        private readonly Shuffler shuffler;

        private readonly int size;

        public TournamentSelection(int size, int? seed = null)
        {
            rng = new UniformIntegerRandom(seed);
            shuffler = new Shuffler(seed);

            this.size = size;
        }

        protected override void AddToNewPopulation<Element>(List<Individual<Element, double>> population, 
                                                            List<Individual<Element, double>> newPopulation)
        {
            List<int> indices = Utils.CreateIndexList(population.Count);

            for (int i = 0; i < population.Count; ++i)
            {
                shuffler.Shuffle(indices);

                newPopulation.Add(new Individual<Element, double>(TournamentWinner(population, indices)));
            }
        }

        private Individual<Element, double> TournamentWinner<Element>(List<Individual<Element, double>> population, List<int> indices)
        {
            Individual<Element, double> winner = population[indices[0]];
            for(int i = 1; i < size; ++i)
            {
                if (population[indices[i]].Fitness > winner.Fitness)
                {
                    winner = population[indices[i]];
                }
            }

            return winner;
        }
    }
}
