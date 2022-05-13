using System;

using Crossovers;
using DominationComparers.BiObjective;
using EvaluationsCLI;
using Generators;
using Mutations;
using Selections.BiObjective;
using StopConditions;

namespace Optimizers.BiObjective.NSGA2
{
    class NSGA2<Element> : GeneticAlgorithm<Element>
    {
        public NSGA2(IEvaluation<Element, Tuple<double, double>> evaluation, IStopCondition stopCondition, AGenerator<Element> generator,
                     IDominationComparer dominationComparer, ACrossover crossover, IMutation<Element> mutation, int populationSize, 
                     int? seed = null)
            : base(evaluation, stopCondition, generator, new NSGA2Selection(2, evaluation.tMaxValue, dominationComparer, true, seed), 
                   crossover, mutation, populationSize, seed)
        {
        }
    }
}
