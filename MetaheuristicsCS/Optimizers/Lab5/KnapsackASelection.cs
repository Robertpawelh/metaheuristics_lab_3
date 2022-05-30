using System.Collections.Generic;

using Optimizers.Lab5;

namespace Optimizers.Lab5
{
    abstract class KnapsackASelection
    {
        public void Select(ref List<KnapsackIndividual> population)
        {
            List<KnapsackIndividual> newPopulation = new List<KnapsackIndividual>(population.Count);

            AddToNewPopulation(population, newPopulation);
            population = newPopulation;
        }

        protected abstract void AddToNewPopulation(List<KnapsackIndividual> population, 
                                                            List<KnapsackIndividual> newPopulation);
    }
}
