using System.Collections.Generic;

using Utility;

namespace Crossovers
{
    sealed class UniformCrossover : ACrossover
    {
        private readonly BoolRandom rng;

        public UniformCrossover(double probability, int? seed = null)
            : base(probability, seed)
        {
            rng = new BoolRandom(seed);
        }

        protected override bool Cross<Element>(List<Element> parent1, List<Element> parent2, List<Element> offspring1, List<Element> offspring2)
        {
            for (int i = 0; i < parent1.Count; ++i)
            {
                if(rng.Next())
                {
                    offspring1[i] = parent1[i];
                    offspring2[i] = parent2[i];
                }
                else
                {
                    offspring1[i] = parent2[i];
                    offspring2[i] = parent1[i];
                }
            }

            return true;
        }
    }
}
