using System;
using System.Collections.Generic;
using System.Linq;

using Crossovers;
using DominationComparers.BiObjective;
using EvaluationsCLI;
using Generators;
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
        private static void ReportOptimizationResult<Element>(OptimizationResult<Element> optimizationResult)
        {
            Console.WriteLine("value: {0}", optimizationResult.BestValue);
            Console.WriteLine("\twhen (time): {0}s", optimizationResult.BestTime);
            Console.WriteLine("\twhen (iteration): {0}", optimizationResult.BestIteration);
            Console.WriteLine("\twhen (FFE): {0}", optimizationResult.BestFFE);
        }

        private static void ReportBiObjectiveOptimizationResult<Element>(BiObjective.OptimizationResult<Element> optimizationResult)
        {
            Console.WriteLine("hyper volume: {0}", optimizationResult.Front.HyperVolume());
            Console.WriteLine("IGD: {0}", optimizationResult.Front.InversedGenerationalDistance());
            Console.WriteLine("\tlast update (time): {0}s", optimizationResult.LastUpdateTime);
            Console.WriteLine("\tlast update (iteration): {0}", optimizationResult.LastUpdateIteration);
            Console.WriteLine("\tlast update (FFE): {0}", optimizationResult.LastUpdateFFE);
        }

        private static void Lab9NSGA2(IEvaluation<bool, Tuple<double, double>> evaluation, int? seed)
        {
            RunningTimeStopCondition stopCondition = new RunningTimeStopCondition(5);

            DefaultDominationComparer dominationComparer = new DefaultDominationComparer();

            BinaryRandomGenerator generator = new BinaryRandomGenerator(evaluation.pcConstraint, seed);
            OnePointCrossover crossover = new OnePointCrossover(0.5, seed);
            BinaryBitFlipMutation mutation = new BinaryBitFlipMutation(1.0 / evaluation.iSize, evaluation, seed);
            SampleBiObjectiveSelection selection = new SampleBiObjectiveSelection(dominationComparer, seed);

            BiObjective.NSGA2.NSGA2<bool> nsga2 = new BiObjective.NSGA2.NSGA2<bool>(evaluation, stopCondition, generator, dominationComparer, 
                                                                                    crossover, mutation, 100, seed);

            nsga2.Run();

            ReportBiObjectiveOptimizationResult(nsga2.Result);
        }

        private static void Lab9ZeroMaxOneMax(int? seed)
        {
            Lab9NSGA2(new CBinaryZeroMaxOneMaxEvaluation(10), seed);
        }

        private static void Lab9Trap5InvTrap5(int? seed)
        {
            Lab9NSGA2(new CBinaryTrapInvTrapEvaluation(5, 10), seed);
        }

        private static void Lab9LOTZ(int? seed)
        {
            Lab9NSGA2(new CBinaryLOTZEvaluation(10), seed);
        }

        private static void Lab9MOMaxCut(int? seed)
        {
            Lab9NSGA2(new CBinaryMOMaxCutEvaluation(EBinaryBiObjectiveMaxCutInstance.maxcut_instance_6), seed);
        }

        private static void Lab9MOKnapsack(int? seed)
        {
            Lab9NSGA2(new CBinaryMOKnapsackEvaluation(EBinaryBiObjectiveKnapsackInstance.knapsack_100), seed);
        }

        private static void Lab8BiObjectiveBinaryGA(IEvaluation<bool, Tuple<double, double>> evaluation, int? seed)
        {
            RunningTimeStopCondition stopCondition = new RunningTimeStopCondition(5);

            DefaultDominationComparer dominationComparer = new DefaultDominationComparer();

            BinaryRandomGenerator generator = new BinaryRandomGenerator(evaluation.pcConstraint, seed);
            OnePointCrossover crossover = new OnePointCrossover(0.5, seed);
            BinaryBitFlipMutation mutation = new BinaryBitFlipMutation(1.0 / evaluation.iSize, evaluation, seed);
            SampleBiObjectiveSelection selection = new SampleBiObjectiveSelection(dominationComparer, seed);

            BiObjective.GeneticAlgorithm<bool> ga = new BiObjective.GeneticAlgorithm<bool>(evaluation, stopCondition, generator, selection, crossover, mutation, 100, seed);

            ga.Run();

            ReportBiObjectiveOptimizationResult(ga.Result);
        }

        private static void Lab8ZeroMaxOneMax(int? seed)
        {
            Lab8BiObjectiveBinaryGA(new CBinaryZeroMaxOneMaxEvaluation(10), seed);
        }

        private static void Lab8Trap5InvTrap5(int? seed)
        {
            Lab8BiObjectiveBinaryGA(new CBinaryTrapInvTrapEvaluation(5, 10), seed);
        }

        private static void Lab8LOTZ(int? seed)
        {
            Lab8BiObjectiveBinaryGA(new CBinaryLOTZEvaluation(10), seed);
        }

        private static void Lab8MOMaxCut(int? seed)
        {
            Lab8BiObjectiveBinaryGA(new CBinaryMOMaxCutEvaluation(EBinaryBiObjectiveMaxCutInstance.maxcut_instance_6), seed);
        }

        private static void Lab8MOKnapsack(int? seed)
        {
            Lab8BiObjectiveBinaryGA(new CBinaryMOKnapsackEvaluation(EBinaryBiObjectiveKnapsackInstance.knapsack_100), seed);
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

        private static void Lab3CMAES(IEvaluation<double, double> evaluation, int? seed)
        {
            IterationsStopCondition stopCondition = new IterationsStopCondition(1000);

            CMAES cmaes = new CMAES(evaluation, stopCondition, 1, seed);

            cmaes.Run();

            ReportOptimizationResult(cmaes.Result);
        }

        private static void Lab3SphereCMAES(int? seed)
        {
            Lab3CMAES(new CRealSphereEvaluation(10), seed);
        }

        private static void Lab3Sphere10CMAES(int? seed)
        {
            Lab3CMAES(new CRealSphere10Evaluation(10), seed);
        }

        private static void Lab3EllipsoidCMAES(int? seed)
        {
            Lab3CMAES(new CRealEllipsoidEvaluation(10), seed);
        }

        private static void Lab3Step2SphereCMAES(int? seed)
        {
            Lab3CMAES(new CRealStep2SphereEvaluation(10), seed);
        }

        private static void Lab3RastriginCMAES(int? seed)
        {
            Lab3CMAES(new CRealRastriginEvaluation(10), seed);
        }

        private static void Lab3AckleyCMAES(int? seed)
        {
            Lab3CMAES(new CRealAckleyEvaluation(10), seed);
        }

        private static void Lab2Sphere(int? seed)
        {
            CRealSphereEvaluation sphereEvaluation = new CRealSphereEvaluation(2);

            List<double> sigmas = Enumerable.Repeat(0.1, sphereEvaluation.iSize).ToList();

            IterationsStopCondition stopCondition = new IterationsStopCondition(1000);
            RealGaussianMutation mutation = new RealGaussianMutation(sigmas, sphereEvaluation, seed);
            RealNullRealMutationES11Adaptation mutationAdaptation = new RealNullRealMutationES11Adaptation(mutation);

            RealEvolutionStrategy11 es11 = new RealEvolutionStrategy11(sphereEvaluation, stopCondition, mutationAdaptation, seed);

            es11.Run();

            ReportOptimizationResult(es11.Result);
        }

        private static void Lab2Sphere10(int? seed)
        {
            CRealSphere10Evaluation sphere10Evaluation = new CRealSphere10Evaluation(2);

            List<double> sigmas = Enumerable.Repeat(0.1, sphere10Evaluation.iSize).ToList();

            IterationsStopCondition stopCondition = new IterationsStopCondition(1000);
            RealGaussianMutation mutation = new RealGaussianMutation(sigmas, sphere10Evaluation, seed);
            RealNullRealMutationES11Adaptation mutationAdaptation = new RealNullRealMutationES11Adaptation(mutation);

            RealEvolutionStrategy11 es11 = new RealEvolutionStrategy11(sphere10Evaluation, stopCondition, mutationAdaptation, seed);

            es11.Run();

            ReportOptimizationResult(es11.Result);
        }

        private static void Lab2Ellipsoid(int? seed)
        {
            CRealEllipsoidEvaluation ellipsoidEvaluation = new CRealEllipsoidEvaluation(2);

            List<double> sigmas = Enumerable.Repeat(0.1, ellipsoidEvaluation.iSize).ToList();

            IterationsStopCondition stopCondition = new IterationsStopCondition(1000);
            RealGaussianMutation mutation = new RealGaussianMutation(sigmas, ellipsoidEvaluation, seed);
            RealNullRealMutationES11Adaptation mutationAdaptation = new RealNullRealMutationES11Adaptation(mutation);

            RealEvolutionStrategy11 es11 = new RealEvolutionStrategy11(ellipsoidEvaluation, stopCondition, mutationAdaptation, seed);

            es11.Run();

            ReportOptimizationResult(es11.Result);
        }

        private static void Lab2Step2Sphere(int? seed)
        {
            CRealStep2SphereEvaluation step2SphereEvaluation = new CRealStep2SphereEvaluation(2);

            List<double> sigmas = Enumerable.Repeat(0.1, step2SphereEvaluation.iSize).ToList();

            IterationsStopCondition stopCondition = new IterationsStopCondition(1000);
            RealGaussianMutation mutation = new RealGaussianMutation(sigmas, step2SphereEvaluation, seed);
            RealNullRealMutationES11Adaptation mutationAdaptation = new RealNullRealMutationES11Adaptation(mutation);

            RealEvolutionStrategy11 es11 = new RealEvolutionStrategy11(step2SphereEvaluation, stopCondition, mutationAdaptation, seed);

            es11.Run();

            ReportOptimizationResult(es11.Result);
        }

        private static void Lab1BinaryRandomSearch(IEvaluation<bool, double> evaluation, int? seed, int maxIterationNumber)
        {
            IterationsStopCondition stopCondition = new IterationsStopCondition(maxIterationNumber);
            BinaryRandomSearch randomSearch = new BinaryRandomSearch(evaluation, stopCondition, seed);

            randomSearch.Run();

            ReportOptimizationResult(randomSearch.Result);
        }

        private static void Lab1OneMax(int? seed)
        {
            Lab1BinaryRandomSearch(new CBinaryOneMaxEvaluation(5), seed, 500);
        }

        private static void Lab1StandardDeceptiveConcatenation(int? seed)
        {
            Lab1BinaryRandomSearch(new CBinaryStandardDeceptiveConcatenationEvaluation(5, 1), seed, 500);
        }

        private static void Lab1BimodalDeceptiveConcatenation(int? seed)
        {
            Lab1BinaryRandomSearch(new CBinaryBimodalDeceptiveConcatenationEvaluation(10, 1), seed, 500);
        }

        private static void Lab1IsingSpinGlass(int? seed)
        {
            Lab1BinaryRandomSearch(new CBinaryIsingSpinGlassEvaluation(25), seed, 500);
        }

        private static void Lab1NkLandscapes(int? seed)
        {
            Lab1BinaryRandomSearch(new CBinaryNKLandscapesEvaluation(10), seed, 500);
        }

        static void Main(string[] args)
        {
            int? seed = null;

            Lab9ZeroMaxOneMax(seed);
            Lab9Trap5InvTrap5(seed);
            Lab9LOTZ(seed);
            Lab9MOMaxCut(seed);
            Lab9MOKnapsack(seed);
            
            Lab8ZeroMaxOneMax(seed);
            Lab8Trap5InvTrap5(seed);
            Lab8LOTZ(seed);
            Lab8MOMaxCut(seed);
            Lab8MOKnapsack(seed);

            /*
            Lab5(seed);

            Lab4Max3SAT(seed);
            Lab4TrapTournamentSelectionOnePointCrossover(seed);
            Lab4TrapRouletteWheelSelectionUniformCrossover(seed);

            Lab3SphereCMAES(seed);
            Lab3Sphere10CMAES(seed);
            Lab3EllipsoidCMAES(seed);
            Lab3Step2SphereCMAES(seed);
            Lab3RastriginCMAES(seed);
            Lab3AckleyCMAES(seed);
            
            Lab2Sphere(seed);
            Lab2Sphere10(seed);
            Lab2Ellipsoid(seed);
            Lab2Step2Sphere(seed);

            Lab1OneMax(seed);
            Lab1StandardDeceptiveConcatenation(seed);
            Lab1BimodalDeceptiveConcatenation(seed);
            Lab1IsingSpinGlass(seed);
            Lab1NkLandscapes(seed);
            */

            Console.ReadKey();
        }
    }
}
