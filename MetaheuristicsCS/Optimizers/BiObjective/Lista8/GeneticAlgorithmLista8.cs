using System;
using System.Collections.Generic;
using Crossovers;
using EvaluationsCLI;
using Generators;
using Mutations;
using Optimizers.Framework;
using Optimizers.Framework.PopulationOptimizers;
using Selections;
using StopConditions;
using Utility;

namespace MetaheuristicsCS.Optimizers.BiObjective.Lista8
{
    class GeneticAlgorithmLista8<Element, EvaluationResult, OptimizationResult> : APopulationOptimizer<Element, EvaluationResult, OptimizationResult>
    {
        protected ACrossover crossover;

        protected List<int> indices;
        protected readonly Shuffler shuffler;

        public GeneticAlgorithmLista8(IEvaluation<Element, EvaluationResult> evaluation, IStopCondition stopCondition, AGenerator<Element> generator,
                                ASelection<EvaluationResult> selection, ACrossover crossover, IMutation<Element> mutation, int populationSize,
                                AOptimizationState<Element, EvaluationResult, OptimizationResult> state, int? seed = null)
            : base(evaluation, stopCondition, generator, selection, mutation, populationSize, state)
        {
            this.crossover = crossover;

            indices = Utils.CreateIndexList(populationSize);
            shuffler = new Shuffler(seed);
        }

        protected override bool RunIteration(long itertionNumber, DateTime startTime)
        {
            Select();

            Crossover();
            Evaluate();

            bool updated = UpdateState();

            Mutate();
            Evaluate();

            return UpdateState() || updated;
        }

        protected void Crossover()
        {
            shuffler.Shuffle(indices);
            Random rnd = new Random();
            for (int i = 0; i < population.Count - 1; i += 2)
            {
                int index1 = indices[rnd.Next(population.Count)];
                int index2 = indices[rnd.Next(population.Count)];

                Individual<Element, EvaluationResult> parent1 = population[index1];
                Individual<Element, EvaluationResult> parent2 = population[index2];

                List<Element> offspringGenotype1 = new List<Element>(parent1.Genotype);
                List<Element> offspringGenotype2 = new List<Element>(parent2.Genotype);

                if (crossover.Crossover(parent1.Genotype, parent2.Genotype, offspringGenotype1, offspringGenotype2))
                {
                    population[index1] = CreateIndividual(offspringGenotype1);
                    population[index2] = CreateIndividual(offspringGenotype2);
                }
            }
        }
    }
}
