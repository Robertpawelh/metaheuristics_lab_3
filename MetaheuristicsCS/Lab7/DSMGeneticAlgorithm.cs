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
using System.Runtime.InteropServices;
using Utility;

namespace Lab7
{
    class DSMGeneticAlgorithm<Element> : DSMGeneticAlgo<Element, double, OptimizationResult<Element>>
    {
        public DSMGeneticAlgorithm(IEvaluation<Element, double> evaluation, IStopCondition stopCondition, AGenerator<Element> generator,
                                ASelection<double> selection, ACrossover crossover, IMutation<Element> mutation, int populationSize,
                                int? seed = null)
            : base(evaluation, stopCondition, generator, selection, crossover, mutation, populationSize,
                   new OptimizationState<Element>(evaluation.tMaxValue), seed)
        {

        }
    }


    class DSMGeneticAlgo<Element, EvaluationResult, OptimizationResult> : APopulationOptimizer<Element, EvaluationResult, OptimizationResult>
    {
        protected ACrossover crossover;

        protected List<int> indices;
        protected readonly Shuffler shuffler;

        protected double[,] DSM;
        int N_clusters;
        int MaxClusterSize;

        public DSMGeneticAlgo(IEvaluation<Element, EvaluationResult> evaluation, IStopCondition stopCondition, AGenerator<Element> generator,
                                ASelection<EvaluationResult> selection, ACrossover crossover, IMutation<Element> mutation, int populationSize,
                                AOptimizationState<Element, EvaluationResult, OptimizationResult> state, int? seed = null)
            : base(evaluation, stopCondition, generator, selection, mutation, populationSize, state)
        {
            this.crossover = crossover;

            indices = Utils.CreateIndexList(populationSize);
            shuffler = new Shuffler(seed);

            DSM = new double[evaluation.iSize, evaluation.iSize];

            N_clusters = 6;
            MaxClusterSize = evaluation.iSize / 10;
        }

        protected void PrintDSM()
        {
            for (int i = 0; i < evaluation.iSize; i++)
            {
                for (int j = 0; j < evaluation.iSize; j++)
                {
                    Console.Write($"{DSM[i, j]} ");
                }
                Console.WriteLine();
            }
        }

        protected void CalculateDSM(long iterationNumber)
        {
            for (int i = 0; i < evaluation.iSize; i++)
            {
                for (int j = 0; j < evaluation.iSize; j++)
                {
                    double p00 = (double)population.Count(x => (Convert.ToBoolean(x.Genotype[i]) == false && Convert.ToBoolean(x.Genotype[j]) == false)) / populationSize;
                    double p01 = (double)population.Count(x => (Convert.ToBoolean(x.Genotype[i]) == false && Convert.ToBoolean(x.Genotype[j]) == true)) / populationSize;
                    double p10 = (double)population.Count(x => (Convert.ToBoolean(x.Genotype[i]) == true && Convert.ToBoolean(x.Genotype[j]) == false)) / populationSize;
                    double p11 = (double)population.Count(x => (Convert.ToBoolean(x.Genotype[i]) == true && Convert.ToBoolean(x.Genotype[j]) == true)) / populationSize;

                    double pi0 = (double)population.Count(x => (Convert.ToBoolean(x.Genotype[i]) == false)) / populationSize;
                    double pi1 = (double)population.Count(x => (Convert.ToBoolean(x.Genotype[i]) == true)) / populationSize;
                    double pj0 = (double)population.Count(x => (Convert.ToBoolean(x.Genotype[j]) == false)) / populationSize;
                    double pj1 = (double)population.Count(x => (Convert.ToBoolean(x.Genotype[j]) == true)) / populationSize;

                    double p00calc = (p00 > 0) ? (p00 * Math.Log(p00 / (pi0 * pj0))) : 0;
                    double p01calc = (p01 > 0) ? (p01 * Math.Log(p01 / (pi0 * pj1))) : 0;
                    double p10calc = (p10 > 0) ? (p10 * Math.Log(p10 / (pi1 * pj0))) : 0;
                    double p11calc = (p11 > 0) ? (p11 * Math.Log(p11 / (pi1 * pj1))) : 0;


                    DSM[i, j] = p00calc + p01calc + p10calc + p11calc;
                }
            }

            if (iterationNumber % 10 == 0)
            {
                using (StreamWriter tw = File.CreateText(@"..\..\Results\" + $"DSM_{evaluation.GetType().Name}_{iterationNumber}.txt"))
                {
                    for (int i = 0; i < evaluation.iSize; i++)
                    {
                        for (int j = 0; j < evaluation.iSize; j++)
                        {
                            tw.Write($"{DSM[i, j]:N3} ");
                        }
                        tw.WriteLine();
                    }
                }
            }

            //PrintDSM();
        }

        protected override bool RunIteration(long itertionNumber, DateTime startTime)
        {
            Select();
            CalculateDSM(itertionNumber);

            if (crossover is DSMCrossover)
            {
                DSMCrossover();
            }
            else
            {
                Crossover();
            }

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

        protected void DSMCrossover()
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


                if (DSMCrossover(parent1.Genotype, parent2.Genotype, offspringGenotype1, offspringGenotype2))
                {
                    population[index1] = CreateIndividual(offspringGenotype1);
                    population[index2] = CreateIndividual(offspringGenotype2);
                }

            }
        }

        public bool DSMCrossover(List<Element> parent1, List<Element> parent2, List<Element> offspring1, List<Element> offspring2)
        {
            if (crossover.crossoverRNG.Next(crossover.Probability))
            {
                return DSMCross(parent1, parent2, offspring1, offspring2);
            }

            return false;
        }

        public List<int> GetCluster(int geneId, List<int> remainingGenes)
        {
            //List<(int, double)>
            List<int> cluster = new List<int>();
            var neighbours = DSM.GetRow(geneId).Select((v, i) => new { neighbourSimilarity = v, index = i }).OrderBy(x => x.neighbourSimilarity).ToList();

            int index = 0;
            var neighbour = neighbours[index];
            while (neighbour.neighbourSimilarity > 0.75 && cluster.Count < MaxClusterSize)
            {
                while (!remainingGenes.Contains(neighbour.index))
                {
                    index++;
                    neighbour = neighbours[index];
                }

                cluster.Add(neighbour.index);
            }

            return cluster;
        }

        protected bool DSMCross(List<Element> parent1, List<Element> parent2, List<Element> offspring1, List<Element> offspring2)
        {
            int n_clusters = 6;
            List<int> remainingGenes = Utils.CreateIndexList(parent1.Count);
            shuffler.Shuffle(remainingGenes);

            List<List<int>> clusters = new List<List<int>>();

            for (int i = 0; i < n_clusters; i++)
            {
                int geneId = remainingGenes[0];
                List<int> cluster = GetCluster(geneId, remainingGenes);
                clusters.Add(cluster);
            }


            int crossPoint = 50;

            for (int i = 0; i < crossPoint; ++i)
            {
                offspring1[i] = parent1[i];
                offspring2[i] = parent2[i];
            }

            for (int i = crossPoint; i < parent1.Count; ++i)
            {
                offspring1[i] = parent2[i];
                offspring2[i] = parent1[i];
            }

            return true;
        }
    }
        // from stack
        public static class ArrayExt
        {
            public static T[] GetRow<T>(this T[,] array, int row)
            {
                if (!typeof(T).IsPrimitive)
                    throw new InvalidOperationException("Not supported for managed types.");

                if (array == null)
                    throw new ArgumentNullException("array");

                int cols = array.GetUpperBound(1) + 1;
                T[] result = new T[cols];

                int size;

                if (typeof(T) == typeof(bool))
                    size = 1;
                else if (typeof(T) == typeof(char))
                    size = 2;
                else
                    size = Marshal.SizeOf<T>();

                Buffer.BlockCopy(array, row * cols * size, result, 0, cols * size);

                return result;
            }
        }
    }
