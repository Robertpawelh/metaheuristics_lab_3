using System.Collections.Generic;

using Utility;

namespace Crossovers
{
    sealed class OnePointCrossover : ACrossover
    {
        private readonly UniformIntegerRandom pointRNG;

        public OnePointCrossover(double probability, int? seed = null)
            : base(probability, seed)
        {
            pointRNG = new UniformIntegerRandom(seed);
        }

        protected override bool Cross<Element>(List<Element> parent1, List<Element> parent2, List<Element> offspring1, List<Element> offspring2)
        {
            int crossPoint = pointRNG.Next(0, parent1.Count);

            for(int i = 0; i < crossPoint; ++i)
            {
                offspring1[i] = parent1[i];
                offspring2[i] = parent2[i];
            }

            for (int i = crossPoint; i < parent1.Count; ++i)
            {
                offspring1[i] = parent2[i];
                offspring2[i] = parent1[i];
            }

            return true;
        }
    }
}
