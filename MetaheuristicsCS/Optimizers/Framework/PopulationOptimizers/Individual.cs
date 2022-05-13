using System.Collections.Generic;

using EvaluationsCLI;
using Mutations;

namespace Optimizers.Framework.PopulationOptimizers
{
    class Individual<Element, EvaluationResult>
    {
        private bool evaluated;

        public List<Element> Genotype { get; }
        public EvaluationResult Fitness { get; private set; }

        public Individual(List<Element> genotype)
        {
            evaluated = false;

            Genotype = genotype;
            Fitness = default(EvaluationResult);
        }

        public Individual(Individual<Element, EvaluationResult> other)
        {
            evaluated = other.evaluated;

            Genotype = new List<Element>(other.Genotype);
            Fitness = other.Fitness;
        }

        public void Evaluate(IEvaluation<Element, EvaluationResult> evaluation)
        {
            if(!evaluated)
            {
                Fitness = evaluation.tEvaluate(Genotype);
                evaluated = true;
            }
        }

        public bool Mutate(IMutation<Element> mutation)
        {
            if(mutation.Mutate(Genotype))
            {
                evaluated = false;

                return true;
            }

            return false;
        }
    }
}
