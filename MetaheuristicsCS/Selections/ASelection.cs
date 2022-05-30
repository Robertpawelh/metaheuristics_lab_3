using System.Collections.Generic;

using Optimizers.Framework.PopulationOptimizers;
using Optimizers.Lab5;

namespace Selections
{
    abstract class ASelection<EvaluationResult>
    {
        public void Select<Element>(ref List<Individual<Element, EvaluationResult>> population)
        {
            List<Individual<Element, EvaluationResult>> newPopulation = new List<Individual<Element, EvaluationResult>>(population.Count);

            AddToNewPopulation(population, newPopulation);
            population = newPopulation;
        }

        protected abstract void AddToNewPopulation<Element>(List<Individual<Element, EvaluationResult>> population, 
                                                            List<Individual<Element, EvaluationResult>> newPopulation);
    }
}
