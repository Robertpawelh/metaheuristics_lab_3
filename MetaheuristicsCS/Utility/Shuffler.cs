using System.Collections.Generic;

namespace Utility
{
    class Shuffler
    {
        private readonly UniformIntegerRandom rng;

        public Shuffler(int? seed = null)
        {
            rng = new UniformIntegerRandom(seed);
        }

        public void Shuffle<T>(List<T> list)
        {
            for(int i = list.Count - 1; i > 0; --i)
            {
                Utils.Swap(list, i, rng.Next(i + 1));
            }
        }
    }
}
