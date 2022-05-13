using System.Collections.Generic;

using Optimizers.Framework.PopulationOptimizers;
using Utility;

namespace Selections.SingleObjective
{
    sealed class RouletteWheelSelection : ASelection<double>
    {
        private readonly UniformRealRandom rng;

        public RouletteWheelSelection(int? seed = null)
        {
            rng = new UniformRealRandom(seed);
        }

        protected override void AddToNewPopulation<Element>(List<Individual<Element, double>> population, 
                                                            List<Individual<Element, double>> newPopulation)
        {
            List<double> accumulatedProbabilities = CreateAccumulatedProbabilities(population);

            for (int i = 0; i < population.Count; ++i)
            {
                newPopulation.Add(new Individual<Element, double>(SingleRouletteWheel(population, accumulatedProbabilities)));
            }
        }

        private Individual<Element, double> SingleRouletteWheel<Element>(List<Individual<Element, double>> population, 
                                                                         List<double> accumulatedProbabilities)
        {
            double probability = rng.Next();

            int selectedIndex = 0;
            for (; selectedIndex < accumulatedProbabilities.Count - 1 && accumulatedProbabilities[selectedIndex] <= probability; ++selectedIndex) ;

            return population[selectedIndex];
        }

        private static List<double> CreateAccumulatedProbabilities<Element>(List<Individual<Element, double>> population)
        {
            List<double> accumulatedProbabilities = new List<double>(population.Count);

            double fitnessSum = CalculateFitnessSum(population);

            double probabilitySum = 0.0;
            foreach(Individual<Element, double> individual in population)
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

        private static double CalculateFitnessSum<Element>(List<Individual<Element, double>> population)
        {
            double sum = 0.0;
            foreach(Individual<Element, double> individual in population)
            {
                sum += individual.Fitness;
            }

            return sum;
        }
    }
}
