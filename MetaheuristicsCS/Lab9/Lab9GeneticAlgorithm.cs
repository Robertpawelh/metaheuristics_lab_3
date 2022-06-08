using Crossovers;
using DominationComparers.BiObjective;
using EvaluationsCLI;
using Generators;
using Mutations;
using Optimizers.BiObjective;
using Optimizers.Framework;
using Optimizers.Framework.PopulationOptimizers;
using Selections;
using Selections.BiObjective;
using StopConditions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Utility;

namespace MetaheuristicsCS.Lab9
{
    class ImprovedNSGA2<Element> : GenneticAlgorithm<Element>
    {
        public ImprovedNSGA2(IEvaluation<Element, Tuple<double, double>> evaluation, IStopCondition stopCondition, AGenerator<Element> generator,
                     IDominationComparer dominationComparer, ASelection<Tuple<double, double>> selection, ACrossover crossover, IMutation<Element> mutation, int populationSize,
                     int? seed = null)
            : base(evaluation, stopCondition, generator, selection,
                   crossover, mutation, populationSize, seed)
        {
        }
    }

    class GenneticAlgorithm<Element> : Lab9GeneticAlgorithm<Element, Tuple<double, double>, OptimizationResult<Element>>
    {
        public GenneticAlgorithm(IEvaluation<Element, Tuple<double, double>> evaluation, IStopCondition stopCondition,
                                AGenerator<Element> generator, ASelection<Tuple<double, double>> selection, ACrossover crossover,
                                IMutation<Element> mutation, int populationSize, int? seed = null)
            : base(evaluation, stopCondition, generator, selection, crossover, mutation, populationSize,
                   new OptimizationState<Element>(evaluation.tMaxValue, evaluation.lOptimalParetoFront), seed)
        {
        }

        private double GetAngle(Individual<Element, Tuple<double, double>> x)
        {
            var vector2 = (x.Fitness.Item1, x.Fitness.Item2);
            var vector1 = (0, 1); // 12 o'clock == 0°, assuming that y goes from bottom to top

            double angleInRadians = Math.Atan2(vector2.Item2, vector2.Item1) - Math.Atan2(vector1.Item2, vector1.Item1);
            return -angleInRadians * 180.0 / Math.PI;
        }

        public override void Crossover()
        {
            int nClusters = 12;
            int min_clusters = 5;
            double extremeAngle = 90 / nClusters;

            List<List<Individual<Element, Tuple<double, double>>>> clusters = new List<List<Individual<Element, Tuple<double, double>>>>();
            List<Individual<Element, Tuple<double, double>>> aloneBoys = new List<Individual<Element, Tuple<double, double>>>();

            for (int i = 0; i < nClusters; i++)
            {
                clusters.Add(population.Where(x => i * extremeAngle <= GetAngle(x) && GetAngle(x) < i * extremeAngle + extremeAngle).ToList());
            }

           
            while (nClusters > min_clusters && clusters.Any(x => x.Count > 4 * (populationSize / nClusters)))
            {
                nClusters -= 2;

                clusters.Clear();

                for (int i = 0; i < nClusters; i++)
                {
                    clusters.Add(population.Where(x => i * extremeAngle <= GetAngle(x) && GetAngle(x) < i * extremeAngle + extremeAngle).ToList());
                }

                aloneBoys.Clear();
            }

            /*
            Console.WriteLine($"ROZMIAR: {clusters.Count}");
            foreach (var clust in clusters)
            {
                Console.WriteLine(clust.Count);
            }
            Console.WriteLine();
            */

            if (nClusters < min_clusters)
            {
                Console.WriteLine("Stara metoda");
                shuffler.Shuffle(indices);

                for (int i = 0; i < population.Count - 1; i += 2)
                {
                    int index1 = indices[i];
                    int index2 = indices[i + 1];

                    Individual<Element, Tuple<double, double>> parent1 = population[index1];
                    Individual<Element, Tuple<double, double>> parent2 = population[index2];

                    List<Element> offspringGenotype1 = new List<Element>(parent1.Genotype);
                    List<Element> offspringGenotype2 = new List<Element>(parent2.Genotype);

                    if (crossover.Crossover(parent1.Genotype, parent2.Genotype, offspringGenotype1, offspringGenotype2))
                    {
                        population[index1] = CreateIndividual(offspringGenotype1);
                        population[index2] = CreateIndividual(offspringGenotype2);
                    }
                }
            }
            else
            {
                Console.WriteLine($"Nowa, {clusters.Count} klastrow");
                foreach (var cluster in clusters)
                {
                    shuffler.Shuffle(cluster);

                    for (int i = 0; i < cluster.Count - 1; i += 2)
                    {
                        Individual<Element, Tuple<double, double>> parent1 = cluster[i];
                        Individual<Element, Tuple<double, double>> parent2 = cluster[i + 1];

                        List<Element> offspringGenotype1 = new List<Element>(parent1.Genotype);
                        List<Element> offspringGenotype2 = new List<Element>(parent2.Genotype);

                        if (crossover.Crossover(parent1.Genotype, parent2.Genotype, offspringGenotype1, offspringGenotype2))
                        {
                            population[i] = CreateIndividual(offspringGenotype1);
                            population[i + 1] = CreateIndividual(offspringGenotype2);
                        }
                    }

                    if (cluster.Count % 2 == 1) aloneBoys.Add(cluster[cluster.Count - 1]);
                }

                shuffler.Shuffle(aloneBoys);
                for (int i = 0; i < aloneBoys.Count - 1; i += 2)
                {
                    Individual<Element, Tuple<double, double>> parent1 = population[i];
                    Individual<Element, Tuple<double, double>> parent2 = population[i + 1];

                    List<Element> offspringGenotype1 = new List<Element>(parent1.Genotype);
                    List<Element> offspringGenotype2 = new List<Element>(parent2.Genotype);

                    if (crossover.Crossover(parent1.Genotype, parent2.Genotype, offspringGenotype1, offspringGenotype2))
                    {
                        population[i] = CreateIndividual(offspringGenotype1);
                        population[i + 1] = CreateIndividual(offspringGenotype2);
                    }
                }
            }


            /*
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
            */
        }
    }

    class Lab9GeneticAlgorithm<Element, EvaluationResult, OptimizationResult> : APopulationOptimizer<Element, EvaluationResult, OptimizationResult>
    {
        protected ACrossover crossover;

        protected List<int> indices;
        protected readonly Shuffler shuffler;

        public Lab9GeneticAlgorithm(IEvaluation<Element, EvaluationResult> evaluation, IStopCondition stopCondition, AGenerator<Element> generator,
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

        public virtual void Crossover()
        {
            throw new Exception("Hehe");
        }
    }
}