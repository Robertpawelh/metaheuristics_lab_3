using System.Collections.Generic;

using Optimizers.Framework.PopulationOptimizers;
using Utility;

namespace Optimizers.Lab5
{
    sealed class KnapsackTournamentSelection : KnapsackASelection
    {
        private readonly UniformIntegerRandom rng;
        private readonly Shuffler shuffler;

        private readonly int size;

        public KnapsackTournamentSelection(int size, int? seed = null)
        {
            rng = new UniformIntegerRandom(seed);
            shuffler = new Shuffler(seed);

            this.size = size;
        }

        protected override void AddToNewPopulation(List<KnapsackIndividual> population, 
                                                            List<KnapsackIndividual> newPopulation)
        {
            List<int> indices = Utils.CreateIndexList(population.Count);

            for (int i = 0; i < population.Count; ++i)
            {
                shuffler.Shuffle(indices);

                newPopulation.Add(new KnapsackIndividual(TournamentWinner(population, indices)));
            }
        }

        private KnapsackIndividual TournamentWinner(List<KnapsackIndividual> population, List<int> indices)
        {
            KnapsackIndividual winner = population[indices[0]];
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
