using System;
using System.Collections.Generic;

using EvaluationsCLI;
using Generators;
using Mutations;
using Selections;
using StopConditions;

namespace Optimizers.Framework.PopulationOptimizers
{
    abstract class APopulationOptimizer<Element, EvaluationResult, OptimizationResult> 
        : AOptimizer<Element, EvaluationResult, OptimizationResult>
    {
        protected readonly AGenerator<Element> generator;
        protected readonly ASelection<EvaluationResult> selection;
        protected readonly IMutation<Element> mutation;

        protected readonly int populationSize;
        protected List<Individual<Element, EvaluationResult>> population;

        public APopulationOptimizer(IEvaluation<Element, EvaluationResult> evaluation, IStopCondition stopCondition, AGenerator<Element> generator, 
                                    ASelection<EvaluationResult> selection, IMutation<Element> mutation, int populationSize, 
                                    AOptimizationState<Element, EvaluationResult, OptimizationResult> state)
            : base(evaluation, stopCondition, state)
        {
            this.generator = generator;
            this.selection = selection;
            this.mutation = mutation;

            this.populationSize = populationSize;
            population = new List<Individual<Element, EvaluationResult>>();
        }

        protected override sealed void Initialize(DateTime startTime)
        {
            population.Clear();
            for(int i = 0; i < populationSize; ++i)
            {
                population.Add(CreateIndividual());
            }

            Evaluate();
            UpdateState();
        }

        protected void Evaluate()
        {
            foreach(Individual<Element, EvaluationResult> individual in population)
            {
                individual.Evaluate(evaluation);
            }
        }

        protected void Select()
        {
            selection.Select(ref population);
        }

        protected void Mutate()
        {
            foreach (Individual<Element, EvaluationResult> individual in population)
            {
                individual.Mutate(mutation);
            }
        }

        protected bool UpdateState(bool onlyImprovements = true)
        {
            bool updated = false;

            foreach(Individual<Element, EvaluationResult> individual in population)
            {
                updated = UpdateState(individual.Genotype, individual.Fitness, onlyImprovements) || updated;
            }

            return updated;
        }

        protected Individual<Element, EvaluationResult> CreateIndividual(List<Element> genotype = null)
        {
            if(genotype == null)
            {
                genotype = generator.Create(evaluation.iSize);
            }

            return new Individual<Element, EvaluationResult>(genotype);
        }
    }
}
