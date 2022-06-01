using System;
using System.Collections.Generic;
using System.Linq;
using EvaluationsCLI;
using Mutations;
using Optimizers.Framework.PopulationOptimizers;
using Utility;

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

        public List<bool> GetOptimizedGenotype(CBinaryKnapsackEvaluation evaluation)
        {
            // TODO
            List<bool> currentGenotype = new List<bool>(Genotype);
            double currentCapacity = evaluation.dCalculateWeight(currentGenotype);
            double maxCapacity = evaluation.dCapacity;

            List<double> weights = (List<double>)evaluation.lWeights;
            List<double> profits = (List<double>)evaluation.lProfits;

            List<int> itemsIndices = Utils.CreateIndexList(Genotype.Count);
            List<double> profitability = profits.Zip(weights, (x, y) => x / y).ToList();

            if (currentCapacity <= maxCapacity)
            {
                List<int> toAddIndices = itemsIndices.OrderByDescending(x => profitability[x]).OrderBy(x => currentGenotype[x]).ToList();
                for (int j = 0; j < toAddIndices.Count; j++)
                {
                    int index = toAddIndices[j];
                    if (currentGenotype[index] == true) break;

                    if (currentCapacity + weights[index] <= maxCapacity)
                    {
                        currentGenotype[index] = true;
                        currentCapacity += weights[index];
                    }

                }
            }
            else
            {
                List<int> toDropIndices = itemsIndices.OrderBy(x => profitability[x]).OrderByDescending(x => currentGenotype[x]).ToList();

                int i = 0;
                while (currentCapacity > maxCapacity)
                {
                    int index = toDropIndices[i];
                    currentGenotype[index] = false;
                    currentCapacity -= weights[index];

                    i++;
                }
            }

            return currentGenotype;
        }

        public double GetPenalty(CBinaryKnapsackEvaluation evaluation)
        {
            List<bool> currentGenotype = new List<bool>(Genotype);

            double currentCapacity = evaluation.dCalculateWeight(currentGenotype);
            double maxCapacity = evaluation.dCapacity;

            if (currentCapacity <= maxCapacity)
            {
                return 0;
            }
            double coefficient = 100;

            double penalty = coefficient * (currentCapacity - maxCapacity);
            
            return penalty;
        }



        public new void Evaluate(IEvaluation<bool, double> evaluation, string evaluationMethod)
        {
            if (!evaluated)
            {
                if (evaluationMethod == "penalty")
                {
                    double penalty = GetPenalty((CBinaryKnapsackEvaluation) evaluation);
                    Fitness = evaluation.tEvaluate(Genotype);
                    Fitness -= penalty;
                }
                else if (evaluationMethod == "lamarck")
                {
                    List<bool> fixedGenotype = GetOptimizedGenotype((CBinaryKnapsackEvaluation) evaluation);
                    Fitness = evaluation.tEvaluate(fixedGenotype);
                    Genotype = fixedGenotype;
                }
                else if (evaluationMethod == "baldwin")
                {
                    List<bool> fixedGenotype = GetOptimizedGenotype((CBinaryKnapsackEvaluation)evaluation);

                    Fitness = evaluation.tEvaluate(fixedGenotype);

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
