using System;

using Crossovers;
using EvaluationsCLI;
using Generators;
using Mutations;
using Selections;
using StopConditions;

namespace Optimizers.BiObjective
{
    class GeneticAlgorithm<Element> : Framework.PopulationOptimizers.GeneticAlgorithm<Element, Tuple<double, double>, OptimizationResult<Element>>
    {
        public GeneticAlgorithm(IEvaluation<Element, Tuple<double, double>> evaluation, IStopCondition stopCondition, 
                                AGenerator<Element> generator, ASelection<Tuple<double, double>> selection, ACrossover crossover, 
                                IMutation<Element> mutation, int populationSize, int? seed = null)
            : base(evaluation, stopCondition, generator, selection, crossover, mutation, populationSize,
                   new OptimizationState<Element>(evaluation.tMaxValue, evaluation.lOptimalParetoFront), seed)
        {

        }
    }
}
