using System;
using System.Collections.Generic;

using Crossovers;
using EvaluationsCLI;
using Generators;
using Mutations;
using Optimizers.Framework;
using Optimizers.SingleObjective;
using Selections;
using StopConditions;
using Utility;

namespace Optimizers.Lab5
{
    class KnapsackGeneticAlgorithm : KnapsackGeneticAlgorithmBase<OptimizationResult<bool>>
    {
        public KnapsackGeneticAlgorithm(IEvaluation<bool, double> evaluation, IStopCondition stopCondition, AGenerator<bool> generator,
                                KnapsackASelection selection, ACrossover crossover, IMutation<bool> mutation, int populationSize,
                                int? seed = null, string evaluationMethod = "default")
            : base(evaluation, stopCondition, generator, selection, crossover, mutation, populationSize,
                   new OptimizationState<bool>(evaluation.tMaxValue), seed, evaluationMethod)
        {

        }
    }



    class KnapsackGeneticAlgorithmBase<OptimizationResult> : KnapsackOptimizer<OptimizationResult>
    {
        protected ACrossover crossover;

        protected List<int> indices;
        protected readonly Shuffler shuffler;

        public KnapsackGeneticAlgorithmBase(IEvaluation<bool, double> evaluation, IStopCondition stopCondition, AGenerator<bool> generator,
                        KnapsackASelection selection, ACrossover crossover, IMutation<bool> mutation, int populationSize,
                        AOptimizationState<bool, double, OptimizationResult> state, int? seed = null, string evaluationMethod = "default")
        : base(evaluation, stopCondition, generator, selection, mutation, populationSize, state, evaluationMethod)
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

            for (int i = 0; i < population.Count - 1; i += 2)
            {
                int index1 = indices[i];
                int index2 = indices[i + 1];

                KnapsackIndividual parent1 = population[index1];
                KnapsackIndividual parent2 = population[index2];

                List<bool> offspringGenotype1 = new List<bool>(parent1.Genotype);
                List<bool> offspringGenotype2 = new List<bool>(parent2.Genotype);

                if (crossover.Crossover(parent1.Genotype, parent2.Genotype, offspringGenotype1, offspringGenotype2))
                {
                    population[index1] = CreateIndividual(offspringGenotype1);
                    population[index2] = CreateIndividual(offspringGenotype2);
                }
            }
        }
    }
}
