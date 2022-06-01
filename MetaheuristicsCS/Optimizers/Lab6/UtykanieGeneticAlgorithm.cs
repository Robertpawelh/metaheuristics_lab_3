using Crossovers;
using EvaluationsCLI;
using Generators;
using Mutations;
using Optimizers.Framework;
using Optimizers.Framework.PopulationOptimizers;
using Optimizers.SingleObjective;
using Selections;
using StopConditions;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Utility;

namespace MetaheuristicsCS.Optimizers.Lab6
{
    class UtykanieGeneticAlgorithm<Element> : UtykanieGeneticAlgo<Element, double, OptimizationResult<Element>>
    {
        public UtykanieGeneticAlgorithm(IEvaluation<Element, double> evaluation, IStopCondition stopCondition, AGenerator<Element> generator,
                                ASelection<double> selection, ACrossover crossover, IMutation<Element> mutation, int populationSize,
                                int? seed = null)
            : base(evaluation, stopCondition, generator, selection, crossover, mutation, populationSize,
                   new OptimizationState<Element>(evaluation.tMaxValue), seed)
        {

        }
    }

    class UtykanieGeneticAlgo<Element, EvaluationResult, OptimizationResult> : UtykanieGeneticOptimizer<Element, EvaluationResult, OptimizationResult>
    {
        protected ACrossover crossover;

        protected List<int> indices;
        protected readonly Shuffler shuffler;

        public UtykanieGeneticAlgo(IEvaluation<Element, EvaluationResult> evaluation, IStopCondition stopCondition, AGenerator<Element> generator,
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

            SaveOverallFitness(itertionNumber);

            return UpdateState() || updated;
        }

        protected void Crossover()
        {
            shuffler.Shuffle(indices);

            for (int i = 0; i < population.Count - 1; i += 2)
            {
                int index1 = indices[i];
                int index2 = indices[i + 1];

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


    abstract class UtykanieGeneticOptimizer<Element, EvaluationResult, OptimizationResult>
    : AOptimizer<Element, EvaluationResult, OptimizationResult>
    {
        protected readonly AGenerator<Element> generator;
        protected readonly ASelection<EvaluationResult> selection;
        protected readonly IMutation<Element> mutation;

        protected readonly int populationSize;
        protected List<Individual<Element, EvaluationResult>> population;

        public UtykanieGeneticOptimizer(IEvaluation<Element, EvaluationResult> evaluation, IStopCondition stopCondition, AGenerator<Element> generator,
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
            for (int i = 0; i < populationSize; ++i)
            {
                population.Add(CreateIndividual());
            }

            Evaluate();
            UpdateState();
        }

        protected void Evaluate()
        {
            foreach (Individual<Element, EvaluationResult> individual in population)
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

            foreach (Individual<Element, EvaluationResult> individual in population)
            {
                updated = UpdateState(individual.Genotype, individual.Fitness, onlyImprovements) || updated;
            }

            return updated;
        }

        protected Individual<Element, EvaluationResult> CreateIndividual(List<Element> genotype = null)
        {
            if (genotype == null)
            {
                genotype = generator.Create(evaluation.iSize);
            }

            return new Individual<Element, EvaluationResult>(genotype);
        }

        protected void SaveOverallFitness(long itertionNumber)
        {
            string method = evaluation.GetType().Name;
            string strFilePath = @"..\..\Results\" + $"zad_63_{method}_{evaluation.iSize}_utykanie.csv";
            string strSeperator = ";";
            StringBuilder sbOutput = new StringBuilder();

            double best = 0;
            double mean = 0;
            double worst = 0;
            {

                best += population.Max(x => Convert.ToDouble(x.Fitness));
                mean += population.Average(x => Convert.ToDouble(x.Fitness));
                worst += population.Min(x => Convert.ToDouble(x.Fitness));

                sbOutput.Append($"genetic_{mutation.Probability}");
                sbOutput.Append(strSeperator + itertionNumber);
                sbOutput.Append(strSeperator + best);
                sbOutput.Append(strSeperator + worst);
                sbOutput.Append(strSeperator + mean);

                // Create and write the csv file
                //File.WriteAllText(strFilePath, sbOutput.ToString());

                // To append more lines to the csv file

                if (!File.Exists(strFilePath))
                {
                    string header = "method;iteration;best;worst;mean";
                    File.WriteAllText(strFilePath, header + Environment.NewLine);
                };

                File.AppendAllText(strFilePath, sbOutput.ToString() + Environment.NewLine);
            }
        }
    }

}
