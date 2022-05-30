using System.Collections.Generic;

using Utility;

namespace Optimizers.Lab5
{
    sealed class KnapsackRouletteWheelSelection : KnapsackASelection
    {
        private readonly UniformRealRandom rng;

        public KnapsackRouletteWheelSelection(int? seed = null)
        {
            rng = new UniformRealRandom(seed);
        }

        protected override void AddToNewPopulation(List<KnapsackIndividual> population, 
                                                            List<KnapsackIndividual> newPopulation)
        {
            List<double> accumulatedProbabilities = CreateAccumulatedProbabilities(population);

            for (int i = 0; i < population.Count; ++i)
            {
                newPopulation.Add(new KnapsackIndividual(SingleRouletteWheel(population, accumulatedProbabilities)));
            }
        }

        private KnapsackIndividual SingleRouletteWheel(List<KnapsackIndividual> population, 
                                                                         List<double> accumulatedProbabilities)
        {
            double probability = rng.Next();

            int selectedIndex = 0;
            for (; selectedIndex < accumulatedProbabilities.Count - 1 && accumulatedProbabilities[selectedIndex] <= probability; ++selectedIndex) ;

            return population[selectedIndex];
        }

        private static List<double> CreateAccumulatedProbabilities(List<KnapsackIndividual> population)
        {
            List<double> accumulatedProbabilities = new List<double>(population.Count);

            double fitnessSum = CalculateFitnessSum(population);

            double probabilitySum = 0.0;
            foreach(KnapsackIndividual individual in population)
            {
                probabilitySum += individual.Fitness / fitnessSum;
                accumulatedProbabilities.Add(probabilitySum);
            }

            if(accumulatedProbabilities.Count > 0)
            {
                accumulatedProbabilities[accumulatedProbabilities.Count - 1] = 1.0;
            }

            return accumulatedProbabilities;
        }

        private static double CalculateFitnessSum(List<KnapsackIndividual> population)
        {
            double sum = 0.0;
            foreach(KnapsackIndividual individual in population)
            {
                sum += individual.Fitness;
            }

            return sum;
        }
    }
}
