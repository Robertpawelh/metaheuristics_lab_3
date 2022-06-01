using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using Crossovers;
using DominationComparers.BiObjective;
using EvaluationsCLI;
using Generators;
using Lab7;
using MetaheuristicsCS.Lab7;
using MetaheuristicsCS.Optimizers.BiObjective.Lista8;
using MetaheuristicsCS.Optimizers.Lab6;
using Mutations;
using Optimizers.Lab5;
using Optimizers.SingleObjective;
using Selections;
using Selections.BiObjective;
using Selections.SingleObjective;
using StopConditions;

using BiObjective = Optimizers.BiObjective;


namespace MetaheuristicsCS
{
    class MetaheuristicsCS
    {

        /* Raport 2 code */
        private static void ReportOptimizationResult<Element>(OptimizationResult<Element> optimizationResult)
        {
            Console.WriteLine("value: {0}", optimizationResult.BestValue);
            Console.WriteLine("\twhen (time): {0}s", optimizationResult.BestTime);
            Console.WriteLine("\twhen (iteration): {0}", optimizationResult.BestIteration);
            Console.WriteLine("\twhen (FFE): {0}", optimizationResult.BestFFE);
        }

        private static void SaveOptimizationResult<Element>(OptimizationResult<Element> optimizationResult, int zadId, string problemName, double? param1, double? param2, string method)
        {
            string strFilePath = @"..\..\Results\" + $"zad_{zadId}_{problemName}.csv";
            string strSeperator = ";";
            StringBuilder sbOutput = new StringBuilder();

            sbOutput.Append(param1);
            sbOutput.Append(strSeperator + param2);
            sbOutput.Append(strSeperator + method);
            sbOutput.Append(strSeperator + optimizationResult.BestValue);
            sbOutput.Append(strSeperator + optimizationResult.BestTime);
            sbOutput.Append(strSeperator + optimizationResult.BestIteration);
            sbOutput.Append(strSeperator + optimizationResult.BestFFE);

            // Create and write the csv file
            //File.WriteAllText(strFilePath, sbOutput.ToString());

            // To append more lines to the csv file

            if (!File.Exists(strFilePath))
            {
                string header = "param1;param2;method;bestValue;bestTime;bestIteration;bestFFE";
                File.WriteAllText(strFilePath, header + Environment.NewLine);
            };

            File.AppendAllText(strFilePath, sbOutput.ToString() + Environment.NewLine);
        }

        private static void SaveProblemParams<Element>(int zadId, string problemName, int? genes, IEvaluation<bool, double> evaluation)
        {
            string strFilePath = @"..\..\Results\" + $"zad_{zadId}_optims.csv";
            string strSeperator = ";";
            StringBuilder sbOutput = new StringBuilder();

            sbOutput.Append(genes.HasValue ? genes : 123);
            sbOutput.Append(strSeperator + problemName);
            sbOutput.Append(strSeperator + evaluation.tMaxValue);

            if (!File.Exists(strFilePath))
            {
                string header = "genes;problemName;maxVal";
                File.WriteAllText(strFilePath, header + Environment.NewLine);
            };

            File.AppendAllText(strFilePath, sbOutput.ToString() + Environment.NewLine);
        }

     

        private static void Lab4BinaryGA(IEvaluation<bool, double> evaluation,
                                            IStopCondition stopCondition,
                                            int populationSize,
                                            ASelection<double> selection, 
                                            ACrossover crossover, 
                                            int? seed, 
                                            string method, 
                                            double? param1, 
                                            double? param2,
                                            string problemName)
        {
            //IterationsStopCondition stopCondition = new IterationsStopCondition(100);
            //RunningTimeStopCondition stopCondition = new RunningTimeStopCondition(5); // FFE?
            BinaryRandomGenerator generator = new BinaryRandomGenerator(evaluation.pcConstraint, seed);
            BinaryBitFlipMutation mutation = new BinaryBitFlipMutation(1.0 / evaluation.iSize, evaluation, seed);


            int zadId = 123345352;
            if (method == "lab4zad2")
            {
                zadId = 42;
                mutation = new BinaryBitFlipMutation((double) param2, evaluation, seed);
                method = $"C{param1}_M{param2}";
            }
            else if (method == "lab4zad1")
            {
                zadId = 41;
                method = $"{param1}";
            }
            else if (method == "lab6zad3")
            {
                zadId = 63;
                mutation = new BinaryBitFlipMutation((double) param1, evaluation, seed);
            }
            else if (method.StartsWith("lab7zad1"))
            {
                zadId = 71;
            }
            else if (method.StartsWith("lab7zad2"))
            {
                zadId = 72;
            }
            else if (method.StartsWith("lab7zad3"))
            {
                zadId = 73;
            }

            if (method == "lab6zad3_island")
            {
                mutation = new BinaryBitFlipMutation(0, evaluation, seed);
                zadId = 63;
                method = $"island_N{param1}_M{param2}";
                int n_populations = (int)param1;
                int migrations_frequence = (int)param2;

                IslandGeneticAlgorithm<bool> ga = new IslandGeneticAlgorithm<bool>(evaluation, stopCondition, generator, selection, crossover, mutation, n_populations, populationSize, migrations_frequence, seed);
                ga.Run();

                ReportOptimizationResult(ga.Result);
                SaveOptimizationResult(ga.Result, zadId, problemName, param1, param2, method);
                SaveProblemParams<double>(zadId, problemName, 123, evaluation);
            }
            else if (method == "lab6zad3")
            {
                UtykanieGeneticAlgorithm<bool> ga = new UtykanieGeneticAlgorithm<bool>(evaluation, stopCondition, generator, selection, crossover, mutation, populationSize, seed);
                ga.Run();

                ReportOptimizationResult(ga.Result);
                SaveOptimizationResult(ga.Result, zadId, problemName, param1, param2, method);
                SaveProblemParams<double>(zadId, problemName, (int?)param1, evaluation);
            }
            else if (method.StartsWith("lab7zad3"))
            {
                //mutation = new BinaryBitFlipMutation(0, evaluation, seed);

                DSMGeneticAlgorithm<bool> ga = new DSMGeneticAlgorithm<bool>(evaluation, stopCondition, generator, selection, crossover, mutation, populationSize, seed);
                ga.Run();

                ReportOptimizationResult(ga.Result);
                SaveOptimizationResult(ga.Result, zadId, problemName, param1, param2, method);
                SaveProblemParams<double>(zadId, problemName, (int)param1, evaluation);
            }
            else
            {
                GeneticAlgorithm<bool> ga = new GeneticAlgorithm<bool>(evaluation, stopCondition, generator, selection, crossover, mutation, populationSize, seed);
                ga.Run();

                ReportOptimizationResult(ga.Result);
                SaveOptimizationResult(ga.Result, zadId, problemName, param1, param2, method);
                SaveProblemParams<double>(zadId, problemName, (int?) param1, evaluation);
            }




        }

        private static void Lab4Max3SAT(int? seed, IStopCondition stopCondition, int populationSize, ASelection<double> selection, ACrossover crossover, string method, double? param1, double? param2)
        {
            Lab4BinaryGA(new CBinaryMax3SatEvaluation(100), stopCondition, populationSize, selection, crossover, seed, method, param1, param2, "Max3SAT");
        }

        private static void Lab4IsingSpinGlass(int? seed, IStopCondition stopCondition, int populationSize, ASelection<double> selection, ACrossover crossover, string method, double? param1, double? param2)
        {
            Lab4BinaryGA(new CBinaryIsingSpinGlassEvaluation(100), stopCondition, populationSize, selection, crossover, seed, method, param1, param2, "ISG");
        }

        private static void Lab4NKLandscapes(int? seed, IStopCondition stopCondition, int populationSize, ASelection<double> selection, ACrossover crossover, string method, double? param1, double? param2)
        {
            Lab4BinaryGA(new CBinaryNKLandscapesEvaluation(100), stopCondition, populationSize, selection, crossover, seed, method, param1, param2, "NKLandscapes");
        }

        private static void Lab4StandardDeceptiveConcatenation(int n_functions, int? seed, IStopCondition stopCondition, int populationSize, ASelection<double> selection, ACrossover crossover, string method, double? param1, double? param2)
        {
            //Lab1BinaryRandomSearch(new CBinaryStandardDeceptiveConcatenationEvaluation(genes, genes/5), "std_deceptive", genes, seed, 500);
            Lab4BinaryGA(new CBinaryStandardDeceptiveConcatenationEvaluation(3, n_functions), stopCondition, populationSize, selection, crossover, seed, method, param1, param2, "Concatenation_" + n_functions);
            //new RouletteWheelSelection(seed),
            //            new UniformCrossover(0.5, seed),
            //             seed);
        }

        /*
        private static void Lab4TrapTournamentSelectionOnePointCrossover(int? seed, string method)
        {
            Lab4BinaryGA(new CBinaryStandardDeceptiveConcatenationEvaluation(3, 50),
                         new TournamentSelection(2, seed),
                         new OnePointCrossover(0.5, seed),
                         seed, method, "TrapTournamentSelectionOnePointCrossover");
        }

        private static void Lab4TrapRouletteWheelSelectionUniformCrossover(int? seed, string method)
        {
            Lab4BinaryGA(new CBinaryStandardDeceptiveConcatenationEvaluation(3, 50),
                         new RouletteWheelSelection(seed),
                         new UniformCrossover(0.5, seed),
                         seed);
        }

        */

        private static void RunLab4Problems(int? seed, string method, double? param1, double? param2)
        {
            // TODO CHANGE STOP CONDITIONS, PROBS AND POPULATION SIZE BEFORE DOING EXPERIMENTS
            var selection = new TournamentSelection(2, seed);
            var crossover = new OnePointCrossover(0.5, seed);
            var populationSize = 500;
            IStopCondition stopCondition = new RunningTimeStopCondition(30); // FFE?

            if (method == "lab4zad1")
            {
                Console.WriteLine($"Setting population size to: {param1}");
                populationSize = (int)param1;
                stopCondition = new IterationsStopCondition(100);
            }


            if (method == "lab4zad2")
            {
                Console.WriteLine($"Setting crossover and mutation to: P(C) = {param1}, P(M) = {param2}");
                populationSize = 200;
                stopCondition = new IterationsStopCondition(100);
                crossover = new OnePointCrossover((double)param1, seed);
            }


            if (method == "lab6zad3_island")
            {
                //Console.WriteLine($"Setting crossover and mutation to: P(C) = {param1}, P(M) = {param2}");
                populationSize = 200;
                stopCondition = new RunningTimeStopCondition(45); //new IterationsStopCondition(100); 
                selection = new TournamentSelection(2, seed);
            }


            if (method == "lab6zad3")
            {
                //Console.WriteLine($"Setting crossover and mutation to: P(C) = {param1}, P(M) = {param2}");
                populationSize = 200;
                stopCondition = new RunningTimeStopCondition(45); //new IterationsStopCondition(100); 
                selection = new TournamentSelection(2, seed);
            }


            //new RouletteWheelSelection(seed),
            //new UniformCrossover(0.5, seed),


            //Lab5(seed);
            Lab4Max3SAT(seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab4IsingSpinGlass(seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab4NKLandscapes(seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab4StandardDeceptiveConcatenation(10, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab4StandardDeceptiveConcatenation(50, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab4StandardDeceptiveConcatenation(100, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
        }

        static void Raport2Lab4_Zad1(int? seed, int n_samples)
        {
            int[] populationSizes = { 10, 50, 100, 200, 500, 1000 };
            foreach (int populationSize in populationSizes)
            {
                for (int i = 0; i < n_samples; i++)
                {
                    RunLab4Problems(seed, "lab4zad1", populationSize, null);
                }
            }
        }

        static void Raport2Lab4_Zad2(int? seed, int n_samples)
        {
            double[] probabilities = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };
            foreach (double crossoverProbability in probabilities)
            {
                foreach (double mutationProbability in probabilities)
                {
                    for (int i = 0; i < n_samples; i++)
                    {
                        RunLab4Problems(seed, "lab4zad2", crossoverProbability, mutationProbability);
                    }
                }
            }
        }


        private static void Lab5Knapsack(EBinaryKnapsackInstance knapsackInstance,
                                            IStopCondition stopCondition,
                                            int populationSize,
                                            KnapsackASelection selection,
                                            ACrossover crossover,
                                            int? seed,
                                            string method,
                                            double? param1,
                                            double? param2,
                                            string problemName)
        {
            CBinaryKnapsackEvaluation evaluation = new CBinaryKnapsackEvaluation(knapsackInstance);

            BinaryRandomGenerator generator = new BinaryRandomGenerator(evaluation.pcConstraint, seed);
            BinaryBitFlipMutation mutation = new BinaryBitFlipMutation(1.0 / evaluation.iSize, evaluation, seed);

            KnapsackGeneticAlgorithm ga = new KnapsackGeneticAlgorithm (evaluation, stopCondition, generator, selection, crossover, mutation, populationSize, seed, evaluationMethod: method);

            ga.Run();

            ReportOptimizationResult<bool>(ga.Result);
            SaveOptimizationResult(ga.Result, 5, problemName, param1, param2, method);
            SaveProblemParams<double>(5, problemName, 123, evaluation);
        }


        private static void RunLab5Knapsack(int? seed, string method, double? param1, double? param2)
        {
            // TODO CHANGE STOP CONDITIONS, PROBS AND POPULATION SIZE BEFORE DOING EXPERIMENTS
            var selection = new KnapsackTournamentSelection(64, seed);
            var crossover = new OnePointCrossover(0.5, seed);
            var populationSize = 200;
            IStopCondition stopCondition = new RunningTimeStopCondition(45); // FFE?
            
            EBinaryKnapsackInstance[] knapsackInstances = { 
                EBinaryKnapsackInstance.knapPI_1_100_1000_1,
                EBinaryKnapsackInstance.knapPI_2_200_1000_1,
                EBinaryKnapsackInstance.knapPI_3_500_1000_1,
                EBinaryKnapsackInstance.knapPI_1_1000_1000_1,
                EBinaryKnapsackInstance.knapPI_2_2000_1000_1,
                EBinaryKnapsackInstance.knapPI_3_5000_1000_1,
            };
            

            foreach (var knapsackInstance in knapsackInstances)
            {
                Lab5Knapsack(knapsackInstance, stopCondition, populationSize, selection, crossover, seed, method, param1, param2, knapsackInstance.ToString());
            }
            
        }

        static void Raport2Lab5(int? seed, int n_samples)
        {
            string[] methods= { "penalty", "lamarck", "baldwin" };
            foreach (string method in methods)
            {
                for (int i = 0; i < n_samples; i++)
                {
                    RunLab5Knapsack(seed, method, null, null);
                }
            }
        }

        static void Raport2Lab6_1(int? seed, int n_samples)
        {
            (int, int)[] configs = new[] { (4, 5), (4, 15) };//{ (10, 2), (10, 5), (10, 15) };


            for (int i = 0; i < n_samples; i++)
            {
                RunLab4Problems(seed, "lab6_1_utykanie", null, null);
            }
        }

        static void Raport2Lab6(int? seed, int n_samples)
        {
            (int, int)[] configs = new[] { (4, 5), (4, 15), (20, 5) };//{ (10, 2), (10, 5), (10, 15) };

            double[] muts = { 0.0, 0.01, 0.1 };
            foreach (var mutation in muts)
            {
                for (int i = 0; i < n_samples; i++)
                {
                    RunLab4Problems(seed, "lab6zad3", mutation, null);
                }
            }

            foreach (var config in configs)
            {
                for (int i = 0; i < n_samples; i++)
                {
                    RunLab4Problems(seed, "lab6zad3_island", config.Item1, config.Item2);
                }
            }

        }



        private static void Lab7BimodalDeceptiveConcatenation(int n_functions, int? seed, IStopCondition stopCondition, int populationSize, ASelection<double> selection, ACrossover crossover, string method, double? param1, double? param2)
        {
            Lab4BinaryGA(new CBinaryBimodalDeceptiveConcatenationEvaluation(10, n_functions), stopCondition, populationSize, selection, crossover, seed, method, n_functions, param2, "BimodalConcatenation");
        }

        private static void Lab7StandardDeceptiveConcatenation(int n_functions, int? seed, IStopCondition stopCondition, int populationSize, ASelection<double> selection, ACrossover crossover, string method, double? param1, double? param2)
        {
            Lab4BinaryGA(new CBinaryStandardDeceptiveConcatenationEvaluation(3, n_functions), stopCondition, populationSize, selection, crossover, seed, method, n_functions, param2, "StandardConcatenation");
        }

        
        private static void Lab7RandomBimodalDeceptiveConcatenation(int n_functions, int? seed, IStopCondition stopCondition, int populationSize, ASelection<double> selection, ACrossover crossover, string method, double? param1, double? param2)
        {
            Lab4BinaryGA(new RandomBinaryBimodalDeceptiveConcatenationEvaluation(10, n_functions, seed), stopCondition, populationSize, selection, crossover, seed, method, n_functions, param2, "RandomBimodalConcatenation");
        }
        

        private static void Lab7RandomStandardDeceptiveConcatenation(int n_functions, int? seed, IStopCondition stopCondition, int populationSize, ASelection<double> selection, ACrossover crossover, string method, double? param1, double? param2)
        {
            Lab4BinaryGA(new RandomBinaryStandardDeceptiveConcatenationEvaluation(3, n_functions, seed), stopCondition, populationSize, selection, crossover, seed, method, n_functions, param2, "RandomStandardConcatenation");
        }

        private static void RunLab7_1Problems(int? seed, string method, double? param1, double? param2)
        {
            // TODO CHANGE STOP CONDITIONS, PROBS AND POPULATION SIZE BEFORE DOING EXPERIMENTS
            var selection = new TournamentSelection(2, seed);
            ACrossover crossover = new OnePointCrossover(0.5, seed);
            var populationSize = 500;
            IStopCondition stopCondition = new RunningTimeStopCondition(30); // FFE?


            if (method == "lab7zad1_onepoint")
            {
                crossover = new OnePointCrossover(0.5, seed);
            }

            if (method == "lab7zad1_uniform")
            {
                crossover = new UniformCrossover(0.5, seed);
            }

            //Lab5(seed);
            Lab7StandardDeceptiveConcatenation(10, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7StandardDeceptiveConcatenation(50, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7StandardDeceptiveConcatenation(100, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7StandardDeceptiveConcatenation(200, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);

            Lab7BimodalDeceptiveConcatenation(10, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7BimodalDeceptiveConcatenation(50, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7BimodalDeceptiveConcatenation(100, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7BimodalDeceptiveConcatenation(200, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
        }

        private static void RunLab7_2Problems(int? seed, string method, double? param1, double? param2)
        {
            // TODO CHANGE STOP CONDITIONS, PROBS AND POPULATION SIZE BEFORE DOING EXPERIMENTS
            var selection = new TournamentSelection(2, seed);
            ACrossover crossover = new OnePointCrossover(0.5, seed);
            var populationSize = 500;
            IStopCondition stopCondition = new RunningTimeStopCondition(30); // FFE?


            if (method == "lab7zad2_onepoint")
            {
                crossover = new OnePointCrossover(0.5, seed);
            }

            if (method == "lab7zad2_uniform")
            {
                crossover = new UniformCrossover(0.5, seed);
            }

            //Lab5(seed);
            Lab7RandomStandardDeceptiveConcatenation(3, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7RandomStandardDeceptiveConcatenation(50, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7RandomStandardDeceptiveConcatenation(100, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7RandomStandardDeceptiveConcatenation(200, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);

            Lab7RandomBimodalDeceptiveConcatenation(10, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7RandomBimodalDeceptiveConcatenation(50, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7RandomBimodalDeceptiveConcatenation(100, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7RandomBimodalDeceptiveConcatenation(200, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
        }



        static void Raport2Lab7_Zad1(int? seed, int n_samples)
        {
            string[] methods = { "lab7zad1_onepoint", "lab7zad1_uniform" };

            foreach (string method in methods)
            {
                for (int i = 0; i < n_samples; i++)
                {
                    RunLab7_1Problems(seed, method, null, null);
                }
            }
        }

        static void Raport2Lab7_Zad2(int? seed, int n_samples)
        {
            string[] methods = { "lab7zad2_onepoint", "lab7zad2_uniform" };

            foreach (string method in methods)
            {
                for (int i = 0; i < n_samples; i++)
                {
                    RunLab7_2Problems(seed, method, null, null);
                }
            }
        }


        private static void RunLab7_3Problems(int? seed, string method, double? param1, double? param2)
        {
            // TODO CHANGE STOP CONDITIONS, PROBS AND POPULATION SIZE BEFORE DOING EXPERIMENTS
            var selection = new TournamentSelection(2, seed);
            ACrossover crossover = new OnePointCrossover(0.5, seed);
            var populationSize = 500;
            IStopCondition stopCondition = new RunningTimeStopCondition(30); // FFE?

            if (method == "lab7zad3_onepoint")
            {
                crossover = new OnePointCrossover(0.5, seed);
            }

            if(method == "lab7zad3_uniform")
            {
                crossover = new UniformCrossover(0.5, seed);
            }

            if(method == "lab7zad3_DSM")
            {
                crossover = new DSMCrossover(0.5, seed);
            }
            /*
            if (method == "lab7zad2_onepoint")
            {
                crossover = new OnePointCrossover(0.5, seed);
            }

            if (method == "lab7zad2_uniform")
            {
                crossover = new UniformCrossover(0.5, seed);
            }
            */

            //Lab5(seed);
            /*
            Lab7StandardDeceptiveConcatenation(10, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7StandardDeceptiveConcatenation(50, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7StandardDeceptiveConcatenation(100, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7StandardDeceptiveConcatenation(200, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);

            Lab7BimodalDeceptiveConcatenation(10, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7BimodalDeceptiveConcatenation(50, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7BimodalDeceptiveConcatenation(100, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7BimodalDeceptiveConcatenation(200, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            */
            Lab7RandomStandardDeceptiveConcatenation(3, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7RandomStandardDeceptiveConcatenation(50, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7RandomStandardDeceptiveConcatenation(100, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7RandomStandardDeceptiveConcatenation(200, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);

            Lab7RandomBimodalDeceptiveConcatenation(10, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7RandomBimodalDeceptiveConcatenation(50, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7RandomBimodalDeceptiveConcatenation(100, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
            Lab7RandomBimodalDeceptiveConcatenation(200, seed, stopCondition, populationSize, selection, crossover, method, param1, param2);
        }


        static void Raport2Lab7_Zad3(int? seed, int n_samples)
        {
            string[] methods = { "lab7zad3_DSM", "lab7zad3_onepoint", "lab7zad3_uniform" };

            foreach (string method in methods)
            {
                for (int i = 0; i < n_samples; i++)
                {
                    RunLab7_3Problems(seed, method, null, null);
                }
            }
        }







        /* Raport 3 code */
        /* Raport 3 code */

        private static void SaveOptimizationResult<Element>(BiObjective.OptimizationResult<Element> optimizationResult, int zadId, string problemName, int genes, string method)
        {
            string strFilePath = @"..\..\Results\" + $"zad_{zadId}_{problemName}.csv";
            string strSeperator = ";";
            StringBuilder sbOutput = new StringBuilder();

            sbOutput.Append(genes);
            sbOutput.Append(strSeperator + method);

            sbOutput.Append(strSeperator + optimizationResult.Front.HyperVolume());
            sbOutput.Append(strSeperator + optimizationResult.Front.InversedGenerationalDistance());
            sbOutput.Append(strSeperator + optimizationResult.LastUpdateTime);
            sbOutput.Append(strSeperator + optimizationResult.LastUpdateIteration);
            sbOutput.Append(strSeperator + optimizationResult.LastUpdateFFE);

            // Create and write the csv file
            //File.WriteAllText(strFilePath, sbOutput.ToString());

            // To append more lines to the csv file

            if (!File.Exists(strFilePath))
            {
                string header = "genes;method;hyperVolume;IGD;lastUpdateTime;lastUpdateIteration;LastUpdateFFE";
                File.WriteAllText(strFilePath, header + Environment.NewLine);
            };

            File.AppendAllText(strFilePath, sbOutput.ToString() + Environment.NewLine);
        }

        private static void SaveProblemParams<Element>(int zadId, string problemName, int genes, IEvaluation<bool, Tuple<double, double>> evaluation)
        {
            string strFilePath = @"..\..\Results\" + $"zad_{zadId}_optims.csv";
            string strSeperator = ";";
            StringBuilder sbOutput = new StringBuilder();

            sbOutput.Append(genes);
            sbOutput.Append(strSeperator + problemName);
            sbOutput.Append(strSeperator + evaluation.tMaxValue);

            if (!File.Exists(strFilePath))
            {
                string header = "genes;problemName;maxVal";
                File.WriteAllText(strFilePath, header + Environment.NewLine);
            };

            File.AppendAllText(strFilePath, sbOutput.ToString() + Environment.NewLine);
        }


        private static void ReportBiObjectiveOptimizationResult<Element>(BiObjective.OptimizationResult<Element> optimizationResult)
        {
            Console.WriteLine("hyper volume: {0}", optimizationResult.Front.HyperVolume());
            Console.WriteLine("IGD: {0}", optimizationResult.Front.InversedGenerationalDistance());
            Console.WriteLine("\tlast update (time): {0}s", optimizationResult.LastUpdateTime);
            Console.WriteLine("\tlast update (iteration): {0}", optimizationResult.LastUpdateIteration);
            Console.WriteLine("\tlast update (FFE): {0}", optimizationResult.LastUpdateFFE);
        }

        private static void Lab9NSGA2(IEvaluation<bool, Tuple<double, double>> evaluation, int? seed, string method, string problemName)
        {
            RunningTimeStopCondition stopCondition = new RunningTimeStopCondition(5); // TODO: "wiarygodne kryterium zatrzymania"

            DefaultDominationComparer dominationComparer = new DefaultDominationComparer();

            BinaryRandomGenerator generator = new BinaryRandomGenerator(evaluation.pcConstraint, seed);
            OnePointCrossover crossover = new OnePointCrossover(0.5, seed);
            BinaryBitFlipMutation mutation = new BinaryBitFlipMutation(1.0 / evaluation.iSize, evaluation, seed);
            SampleBiObjectiveSelection selection = new SampleBiObjectiveSelection(dominationComparer, seed);

            BiObjective.NSGA2.NSGA2<bool> nsga2 = new BiObjective.NSGA2.NSGA2<bool>(evaluation, stopCondition, generator, dominationComparer, 
                                                                                    crossover, mutation, 100, seed);

            nsga2.Run();

            ReportBiObjectiveOptimizationResult(nsga2.Result);
            SaveOptimizationResult(nsga2.Result, 1, problemName, 123, method);
            SaveProblemParams<double>(1, problemName, 123, evaluation);
        }

        private static void Lab9ZeroMaxOneMax(int? seed)
        {
            Lab9NSGA2(new CBinaryZeroMaxOneMaxEvaluation(10), seed, "default", "ZeroMaxOneMax");
        }

        private static void Lab9Trap5InvTrap5(int? seed)
        {
            Lab9NSGA2(new CBinaryTrapInvTrapEvaluation(5, 10), seed, "default", "Trap5InvTrap5");
        }

        private static void Lab9LOTZ(int? seed)
        {
            Lab9NSGA2(new CBinaryLOTZEvaluation(10), seed, "default", "LOTZ");
        }

        private static void Lab9MOMaxCut(int? seed)
        {
            Lab9NSGA2(new CBinaryMOMaxCutEvaluation(EBinaryBiObjectiveMaxCutInstance.maxcut_instance_6), seed, "default", "MOMaxCut");
        }

        private static void Lab9MOKnapsack(int? seed)
        {
            Lab9NSGA2(new CBinaryMOKnapsackEvaluation(EBinaryBiObjectiveKnapsackInstance.knapsack_100), seed, "default", "MOKnapSack");
        }

        private static void Lab8BiObjectiveBinaryGA(IEvaluation<bool, Tuple<double, double>> evaluation, int? seed, string method, string problemName)
        {
            RunningTimeStopCondition stopCondition = new RunningTimeStopCondition(5);
            //RunningTimeStopCondition stopCondition = new RunningTimeStopCondition(1);
            //IterationsStopCondition stopCondition = new IterationsStopCondition(200);

            DefaultDominationComparer dominationComparer = new DefaultDominationComparer();

            BinaryRandomGenerator generator = new BinaryRandomGenerator(evaluation.pcConstraint, seed);
            OnePointCrossover crossover = new OnePointCrossover(0.5, seed);
            BinaryBitFlipMutation mutation = new BinaryBitFlipMutation(1.0 / evaluation.iSize, evaluation, seed);

            ASelection<Tuple<double, double>> selection = null;

            switch (method)
            {
                case "default":
                    selection = new SampleBiObjectiveSelection(dominationComparer, seed);
                    var ga = new BiObjective.GeneticAlgorithm<bool>(evaluation, stopCondition, generator, selection, crossover, mutation, 100, seed);
                    ga.Run();
                    ReportBiObjectiveOptimizationResult(ga.Result);
                    SaveOptimizationResult(ga.Result, 1, problemName, 123, method);
                    SaveProblemParams<double>(1, problemName, 123, evaluation);
                    break;
                case "skrajni1":
                    selection = new SkrajniSelection(dominationComparer, seed);
                    var gaa = new BiObjective.GeneticAlgorithm<bool>(evaluation, stopCondition, generator, selection, crossover, mutation, 100, seed);
                    gaa.Run();
                    ReportBiObjectiveOptimizationResult(gaa.Result);
                    SaveOptimizationResult(gaa.Result, 1, problemName, 123, method);
                    SaveProblemParams<double>(1, problemName, 123, evaluation);
                    break;
                case "skrajni2":
                    selection = new SkrajniSelectionDwa(dominationComparer, seed);
                    var gaaa = new BiObjective.GeneticAlgorithm<bool>(evaluation, stopCondition, generator, selection, crossover, mutation, 100, seed);
                    gaaa.Run();
                   
                    ReportBiObjectiveOptimizationResult(gaaa.Result);
                    SaveOptimizationResult(gaaa.Result, 1, problemName, 123, method);
                    SaveProblemParams<double>(1, problemName, 123, evaluation);
                    break;

                case "skrajni1_turniej":
                    selection = new SkrajniSelection(dominationComparer, seed);
                    var gaaaa = new BiObjective.GeneticAlgorithmPierwszy<bool>(evaluation, stopCondition, generator, selection, crossover, mutation, 100, seed);
                    gaaaa.Run();
                    ReportBiObjectiveOptimizationResult(gaaaa.Result);
                    SaveOptimizationResult(gaaaa.Result, 1, problemName, 123, method);
                    SaveProblemParams<double>(1, problemName, 123, evaluation);
                    break;
                case "skrajni2_turniej":
                    selection = new SkrajniSelectionDwa(dominationComparer, seed);
                    var gaaaaaa = new BiObjective.GeneticAlgorithmPierwszy<bool>(evaluation, stopCondition, generator, selection, crossover, mutation, 100, seed);
                    gaaaaaa.Run();

                    ReportBiObjectiveOptimizationResult(gaaaaaa.Result);
                    SaveOptimizationResult(gaaaaaa.Result, 1, problemName, 123, method);
                    SaveProblemParams<double>(1, problemName, 123, evaluation);
                    break;
                default:
                    Console.WriteLine("USING DEFAULT METHOD!!!!!!!!!!!!!!!!!");
                    //ga = new BiObjective.GeneticAlgorithm<bool>(evaluation, stopCondition, generator, selection, crossover, mutation, 100, seed);
                    break;
            };



        }

        private static void Lab8ZeroMaxOneMax(int? seed, string method)
        {
            Lab8BiObjectiveBinaryGA(new CBinaryZeroMaxOneMaxEvaluation(10), seed, method, "ZeroMaxOneMax");
        }

        private static void Lab8Trap5InvTrap5(int? seed, string method)
        {
            Lab8BiObjectiveBinaryGA(new CBinaryTrapInvTrapEvaluation(5, 10), seed, method, "Trap5InvTrap5");
        }

        private static void Lab8LOTZ(int? seed, string method)
        {
            Lab8BiObjectiveBinaryGA(new CBinaryLOTZEvaluation(10), seed, method, "LOTZ");
        }

        private static void Lab8MOMaxCut(int? seed, string method)
        {
            Lab8BiObjectiveBinaryGA(new CBinaryMOMaxCutEvaluation(EBinaryBiObjectiveMaxCutInstance.maxcut_instance_6), seed, method, "MOMaxCut");
        }

        private static void Lab8MOKnapsack(int? seed, string method)
        {
            Lab8BiObjectiveBinaryGA(new CBinaryMOKnapsackEvaluation(EBinaryBiObjectiveKnapsackInstance.knapsack_100), seed, method, "MOKnapsack");
        }

        private static void RunObjectiveProblems(int? seed, string method)
        {

            Lab8ZeroMaxOneMax(seed, method);
            Lab8Trap5InvTrap5(seed, method);
            Lab8LOTZ(seed, method);
            Lab8MOMaxCut(seed, method);
            Lab8MOKnapsack(seed, method);
        }

        static void Raport3Zad1(int? seed, int n_samples)
        {
            //(string, int)[] config = new[] { ("default", 0), ("1_5_success", 5), ("1_5_success", 25), ("1_5_success", 50), ("dziedzina_adaptation", 10) };

            /*
            for (int i = 0; i < n_samples; i++)
            {
                foreach ((string, int) conf in config)
                {
                    RunProblems(seed, conf.Item1, conf.Item2);
                }
            }
            */
            string[] config = { "skrajni2", "skrajni1", "default"}; //, ;//, "default3" }; // "skrajni2_turniej", "skrajni1_turniej", 

            for (int i = 0; i < n_samples; i++)
            {
                foreach (string conf in config)
                {
                    RunObjectiveProblems(seed, conf);
                }
            }
        }



        /* End of raport 3 code */

        static void Main(string[] args)
        {
            int? seed = null;
            int n_samples = 3;

            //Raport2Lab4_Zad1(seed, n_samples);
            //Raport2Lab4_Zad2(seed, 2);
            //Raport2Lab5(seed, n_samples);



            //Raport2Lab6(seed, n_samples);
            //Raport2Lab7_Zad1(seed, n_samples);
            //Raport2Lab7_Zad2(seed, n_samples);
            Raport2Lab7_Zad3(seed, n_samples);
            //Raport2Zad1(seed, n_samples);
            //Raport3Zad1(seed, n_samples);

            //Lab5(seed);

            Console.ReadKey();
        }
    }
}
