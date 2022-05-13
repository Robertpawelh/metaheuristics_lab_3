
namespace Utility
{
    class UniformRealRandom : ASeedableRandom
    {
        public UniformRealRandom(int? seed = null)
            : base(seed)
        {

        }

        public double Next(double a, double b)
        {
            return a + rng.NextDouble() * (b - a);
        }

        public double Next()
        {
            return rng.NextDouble();
        }
    }
}
