using System;
using System.Collections.Generic;

using EvaluationsCLI;
using Generators;
using Mutations;
using Optimizers.Framework;
using Selections;
using StopConditions;

namespace Optimizers.Lab5
{
    abstract class KnapsackOptimizer<OptimizationResult>
        : AOptimizer<bool, double, OptimizationResult>
    {
        protected readonly AGenerator<bool> generator;
        protected readonly KnapsackASelection selection;
        protected readonly IMutation<bool> mutation;

        protected readonly int populationSize;
        protected List<KnapsackIndividual> population;

        protected string EvaluationMethod;

        public KnapsackOptimizer(IEvaluation<bool, double> evaluation, IStopCondition stopCondition, AGenerator<bool> generator,
                                    KnapsackASelection selection, IMutation<bool> mutation, int populationSize,
                                    AOptimizationState<bool, double, OptimizationResult> state, string evaluationMethod)
            : base(evaluation, stopCondition, state)
        {
            this.generator = generator;
            this.selection = selection;
            this.mutation = mutation;

            this.populationSize = populationSize;
            population = new List<KnapsackIndividual>();

            EvaluationMethod = evaluationMethod;
        }

        protected override sealed void Initialize(DateTime startTime)
        {
            population.Clear();
            for (int i = 0; i < populationSize; ++i)
            {
                population.Add(CreateIndividual());
            }

            Evaluate();
            UpdateState();
        }

        protected void Evaluate()
        {
            foreach (KnapsackIndividual individual in population)
            {
                individual.Evaluate(evaluation, EvaluationMethod);
            }
        }

        protected void Select()
        {
            selection.Select(ref population);
        }

        protected void Mutate()
        {
            foreach (KnapsackIndividual individual in population)
            {
                individual.Mutate(mutation);
            }
        }

        protected bool UpdateState(bool onlyImprovements = true)
        {
            bool updated = false;

            foreach (KnapsackIndividual individual in population)
            {
                updated = UpdateState(individual.Genotype, individual.Fitness, onlyImprovements) || updated;
            }

            return updated;
        }

        protected KnapsackIndividual CreateIndividual(List<bool> genotype = null)
        {
            if (genotype == null)
            {
                genotype = generator.Create(evaluation.iSize);
            }

            return new KnapsackIndividual (genotype);
        }
    }
}
