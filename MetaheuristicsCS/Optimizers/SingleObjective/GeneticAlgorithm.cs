using Crossovers;
using EvaluationsCLI;
using Generators;
using Mutations;
using Selections;
using StopConditions;


namespace Optimizers.SingleObjective
{
    class GeneticAlgorithm<Element> : Framework.PopulationOptimizers.GeneticAlgorithm<Element, double, OptimizationResult<Element>>
    {
        public GeneticAlgorithm(IEvaluation<Element, double> evaluation, IStopCondition stopCondition, AGenerator<Element> generator,
                                ASelection<double> selection, ACrossover crossover, IMutation<Element> mutation, int populationSize, 
                                int? seed = null)
            : base(evaluation, stopCondition, generator, selection, crossover, mutation, populationSize, 
                   new OptimizationState<Element>(evaluation.tMaxValue), seed)
        {

        }
    }
}
