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
using Utility;

namespace Optimizers.Lab5
{
    class IslandGeneticAlgorithm<Element> : IslandGeneticOptimizer<Element, double, OptimizationResult<Element>>
    {
        public IslandGeneticAlgorithm(IEvaluation<Element, double> evaluation, IStopCondition stopCondition, AGenerator<Element> generator,
                                ASelection<double> selection, ACrossover crossover, IMutation<Element> mutation, int n_populations, int populationSize,
                                int migrationsFrequence,
                                int? seed = null)
            : base(evaluation, stopCondition, generator, selection, crossover, mutation, n_populations, populationSize, migrationsFrequence,
                   new OptimizationState<Element>(evaluation.tMaxValue), seed)
        {

        }
    }


    class IslandGeneticOptimizer<Element, EvaluationResult, OptimizationResult> : APopulationOptimizer<Element, EvaluationResult, OptimizationResult>
    {
        protected ACrossover crossover;

        protected List<int> indices;
        protected readonly Shuffler shuffler;
        protected int N_populations;
        protected int MigrationsFrequence;
        protected List<List<Individual<Element, EvaluationResult>>> populations;

        protected int RealNoImprovementsCounter;
        protected int NoImprovementsCounter;
        protected double bestFitness;
        protected int BestFoundOn;

        public IslandGeneticOptimizer(IEvaluation<Element, EvaluationResult> evaluation, IStopCondition stopCondition, AGenerator<Element> generator,
                                ASelection<EvaluationResult> selection, ACrossover crossover, IMutation<Element> mutation, int n_populations, int populationSize,
                                int migrationsFrequence,
                                AOptimizationState<Element, EvaluationResult, OptimizationResult> state, int? seed = null)
            : base(evaluation, stopCondition, generator, selection, mutation, populationSize, state)
        {
            this.crossover = crossover;

            indices = Utils.CreateIndexList(populationSize);
            shuffler = new Shuffler(seed);

            N_populations = n_populations;
            MigrationsFrequence = migrationsFrequence;

            population = null;

            populations = new List<List<Individual<Element, EvaluationResult>>>();
            for (int i = 0; i < n_populations; i++)
            {
                populations.Add(new List<Individual<Element, EvaluationResult>>());
            }

        }

        protected new void Initialize(DateTime startTime)
        {
            foreach (var population in populations)
            {
                population.Clear();
                for (int i = 0; i < populationSize; ++i)
                {
                    population.Add(CreateIndividual());
                }

                Evaluate();
                UpdateState();

                NoImprovementsCounter = 0;
                RealNoImprovementsCounter = 0;
                bestFitness = population.Max(x => Convert.ToDouble(x.Fitness));
                BestFoundOn = 0;
            }
        }

        public new void Run()
        {
            Initialize();

            while (!ShouldStop())
            {
                RunIteration();
            }

            SaveNoImprove();
        }

        public new void Initialize()
        {
            state.Reset();

            iterationNumber = 0;
            startTime = DateTime.UtcNow;

            Initialize(startTime);
        }


        protected new void Evaluate()
        {
            foreach (var population in populations)
            {
                foreach (Individual<Element, EvaluationResult> individual in population)
                {
                    individual.Evaluate(evaluation);
                }
            }
        }

        protected new void Select()
        {
            for (int i = 0; i < populations.Count; i++)
            {
                var population = populations[i];
                selection.Select(ref population);
                populations[i] = population;
            }
        }

        protected new void Mutate()
        {
            foreach (var population in populations)
            {
                foreach (Individual<Element, EvaluationResult> individual in population)
                {
                    individual.Mutate(mutation);
                }
            }
        }

        protected new bool UpdateState(bool onlyImprovements = true)
        {
            bool updated = false;
            foreach (var population in populations)
            {
                foreach (Individual<Element, EvaluationResult> individual in population)
                {
                    updated = updated || UpdateState(individual.Genotype, individual.Fitness, onlyImprovements) || updated;
                }
            }

            return updated;
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
            foreach(var population in populations)
            {
                best += population.Max(x => Convert.ToDouble(x.Fitness));
                mean += population.Average(x => Convert.ToDouble(x.Fitness));
                worst += population.Min(x => Convert.ToDouble(x.Fitness));
            }
            best /= N_populations;
            worst /= N_populations;
            mean /= N_populations;

            sbOutput.Append($"island_{N_populations}_{MigrationsFrequence}");
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



        protected override bool RunIteration(long itertionNumber, DateTime startTime)
        {
            
            Select();

            Crossover();
            Evaluate();

            bool updated = UpdateState();

            Mutate();
            Evaluate();

            Migration(itertionNumber);
            /*
            foreach (var population in populations)
            {
                Console.WriteLine(population.Count);
            }
            */
            SaveOverallFitness(itertionNumber);

            double maxx = 0;
            foreach (var population in populations)
            {
                maxx += population.Max(x => Convert.ToDouble(x.Fitness));
            }
            maxx /= N_populations;

            if (bestFitness < maxx)
            {
                NoImprovementsCounter = 0;
                RealNoImprovementsCounter = 0;
                bestFitness = maxx;
            }
            else 
            {
                NoImprovementsCounter++;
                RealNoImprovementsCounter++;
            }

            return UpdateState() || updated;

        }

        protected void Crossover()
        {
            shuffler.Shuffle(indices);

            foreach (var population in populations)
            {
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

        protected void Migration(long iterationNumber)
        {
            var random = new Random();

            List<Individual<Element, EvaluationResult>> travelers = new List<Individual<Element, EvaluationResult>>();

            //Console.WriteLine("HEHE" + iterationNumber);
            if (NoImprovementsCounter > MigrationsFrequence)
            //if ((iterationNumber + 1) % MigrationsFrequence == 0)
            {
                NoImprovementsCounter = 0;
                //Console.WriteLine(iterationNumber);
                List<int> populationsToSendIndices = Utils.CreateIndexList(N_populations);
                List<int> populationsToGetIndices = Utils.CreateIndexList(N_populations);

                while (populationsToSendIndices.Count > 0)
                {
                    int index_sender = populationsToSendIndices[random.Next(populationsToSendIndices.Count)];
                    populationsToSendIndices.RemoveAll(item => item == index_sender);

                    var population_sending = populations[index_sender];

                    int index_getter = populationsToGetIndices[random.Next(populationsToGetIndices.Count)];
                    var population_getting = populations[index_getter];
                    while (population_sending == population_getting && populationsToGetIndices.Count > 1)
                    {
                        index_getter = populationsToGetIndices[random.Next(populationsToGetIndices.Count)];
                        population_getting = populations[index_getter];
                    }

                    populationsToGetIndices.RemoveAll(item => item == index_getter);

                    population_sending = population_sending.OrderByDescending(x => x.Fitness).ToList();
                    int index = 0;
                    Individual<Element, EvaluationResult> traveler = population_sending[index];
                    while (travelers.Contains(traveler))
                    {
                        index += 1;
                        traveler = population_sending[index];
                    }
                    populations[index_sender].Remove(traveler);
                    populations[index_getter].Add(traveler);

                    travelers.Add(traveler);
                }
            }
        }

        public void SaveNoImprove()
        {
            string dset = evaluation.GetType().Name;
            string strFilePath = @"..\..\Results\" + $"zad_63_{dset}_{evaluation.iSize}_utykanie_NO_IMPROVEMENT.csv";
            string strSeperator = ";";

            StringBuilder sbOutput = new StringBuilder();
            sbOutput.Append($"island_{N_populations}_{MigrationsFrequence}");
            sbOutput.Append(strSeperator + RealNoImprovementsCounter);
            sbOutput.Append(strSeperator + BestFoundOn);
            sbOutput.Append(strSeperator + bestFitness);

            if (!File.Exists(strFilePath))
            {
                string header = "method;noImprovements;bestFoundOn;fitness";
                File.WriteAllText(strFilePath, header + Environment.NewLine);
            };

            File.AppendAllText(strFilePath, sbOutput.ToString() + Environment.NewLine);
        }
    }
}
