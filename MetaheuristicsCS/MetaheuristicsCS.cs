using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using Crossovers;
using DominationComparers.BiObjective;
using EvaluationsCLI;
using Generators;
using MetaheuristicsCS.Optimizers.BiObjective.Lista8;
using Mutations;
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


        private static void Lab5(int? seed)
        {
            CBinaryKnapsackEvaluation evaluation = new CBinaryKnapsackEvaluation(EBinaryKnapsackInstance.knapPI_1_100_1000_1);
            IterationsStopCondition stopCondition = new IterationsStopCondition(100);

            BinaryRandomGenerator generator = new BinaryRandomGenerator(evaluation.pcConstraint, seed);
            OnePointCrossover crossover = new OnePointCrossover(0.5, seed);
            BinaryBitFlipMutation mutation = new BinaryBitFlipMutation(1.0 / evaluation.iSize, evaluation, seed);
            TournamentSelection selection = new TournamentSelection(2, seed);

            GeneticAlgorithm<bool> ga = new GeneticAlgorithm<bool>(evaluation, stopCondition, generator, selection, crossover, mutation, 50, seed);

            ga.Run();

            ReportOptimizationResult<bool>(ga.Result);
        }

        private static void Lab4BinaryGA(IEvaluation<bool, double> evaluation, ASelection<double> selection, ACrossover crossover, int? seed)
        {
            IterationsStopCondition stopCondition = new IterationsStopCondition(100);

            BinaryRandomGenerator generator = new BinaryRandomGenerator(evaluation.pcConstraint, seed);
            BinaryBitFlipMutation mutation = new BinaryBitFlipMutation(1.0 / evaluation.iSize, evaluation, seed);

            GeneticAlgorithm<bool> ga = new GeneticAlgorithm<bool>(evaluation, stopCondition, generator, selection, crossover, mutation, 50, seed);

            ga.Run();

            ReportOptimizationResult(ga.Result);
        }

        private static void Lab4Max3SAT(int? seed)
        {
            Lab4BinaryGA(new CBinaryMax3SatEvaluation(100),
                         new TournamentSelection(2, seed),
                         new OnePointCrossover(0.5, seed),
                         seed);
        }

        private static void Lab4TrapTournamentSelectionOnePointCrossover(int? seed)
        {
            Lab4BinaryGA(new CBinaryStandardDeceptiveConcatenationEvaluation(3, 50),
                         new TournamentSelection(2, seed),
                         new OnePointCrossover(0.5, seed),
                         seed);
        }

        private static void Lab4TrapRouletteWheelSelectionUniformCrossover(int? seed)
        {
            Lab4BinaryGA(new CBinaryStandardDeceptiveConcatenationEvaluation(3, 50),
                         new RouletteWheelSelection(seed),
                         new UniformCrossover(0.5, seed),
                         seed);
        }



        private static void RunBinaryProblems(int? seed, string method)
        {

            //Lab5(seed);
            Lab4Max3SAT(seed);
            Lab4TrapTournamentSelectionOnePointCrossover(seed);
            Lab4TrapRouletteWheelSelectionUniformCrossover(seed);
        }

        static void Raport2Zad1(int? seed, int n_samples)
        {
            string[] config = { "default", "default2", "default3" };

            for (int i = 0; i < n_samples; i++)
            {
                foreach (string conf in config)
                {
                    RunBinaryProblems(seed, conf);
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
            int n_samples = 5;

            //Raport2Zad1(seed, n_samples);
            Raport3Zad1(seed, n_samples);

            Console.ReadKey();
        }
    }
}
