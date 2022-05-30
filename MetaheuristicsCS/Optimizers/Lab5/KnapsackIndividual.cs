using System;
using System.Collections.Generic;

using EvaluationsCLI;
using Mutations;
using Optimizers.Framework.PopulationOptimizers;

namespace Optimizers.Lab5
{
    class KnapsackIndividual
    {
        private bool evaluated;

        public List<bool> Genotype { get; private set; }
        public double Fitness { get; private set; }

        public KnapsackIndividual(List<bool> genotype)
        {
            evaluated = false;

            Genotype = genotype;
            Fitness = default(double);
        }

        public KnapsackIndividual(KnapsackIndividual other)
        {
            evaluated = other.evaluated;

            Genotype = new List<bool>(other.Genotype);
            Fitness = other.Fitness;
        }

        public List<bool> GetFixedGenotype(CBinaryKnapsackEvaluation evaluation)
        {
            // TODO
            List<bool> currentGenotype = new List<bool>(Genotype);
            double currentCapacity = evaluation.dCalculateWeight(currentGenotype);
            double maxCapacity = evaluation.dCapacity;
            return currentGenotype;
         }

        
        public new void Evaluate(IEvaluation<bool, double> evaluation, string evaluationMethod)
        {
            if (!evaluated)
            {
                Fitness = evaluation.tEvaluate(Genotype);
                if (evaluationMethod == "penalty")
                {
                    Fitness = evaluation.tEvaluate(Genotype);
                    // TO IMPLEMENT. THE CODE BELOW IS ONLY FOR TESTS
                    double newFitness = Convert.ToDouble(Fitness);
                    double capacity = ((CBinaryKnapsackEvaluation)evaluation).dCapacity;
                    double penalty = (((CBinaryKnapsackEvaluation)evaluation).dCalculateWeight((IList<bool>)Genotype) - capacity) * 10;
                    //Console.WriteLine(penalty);
                    newFitness -= penalty;
                    Fitness = (double) Convert.ChangeType(newFitness, typeof(double));
                }
                else if (evaluationMethod == "lamarck")
                {
                    //List<Element> fixedGenotype = GetFixedGenotype((CBinaryKnapsackEvaluation) evaluation);
                    //Fitness = evaluation.tEvaluate(fixedGenotype);
                    //Genotype = fixedGenotype;
                }
                else if (evaluationMethod == "baldwin")
                {
                    //List<Element> fixedGenotype = GetFixedGenotype();

                    //Fitness = evaluation.tEvaluate(fixedGenotype);

                }
                else
                {
                    throw new ArgumentException("Knapsack problem can not be used without special evaluation method!");
                }    
                evaluated = true;
            }
        }

        

        public bool Mutate(IMutation<bool> mutation)
        {
            if (mutation.Mutate(Genotype))
            {
                evaluated = false;

                return true;
            }

            return false;
        }
    }
}
