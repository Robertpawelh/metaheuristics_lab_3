using EvaluationsCLI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MetaheuristicsCS.Lab7
{
    class RandomBinaryBimodalDeceptiveConcatenationEvaluation : CBinaryBimodalDeceptiveConcatenationEvaluation
    {
        private List<int> GenesOrder;

        public RandomBinaryBimodalDeceptiveConcatenationEvaluation(int iBlockSize, int iNumberOfBlocks, int? seed) : base(iBlockSize, iNumberOfBlocks)
        {
            Random rng = seed.HasValue ? new Random(seed.Value) : new Random();
            GenesOrder = Enumerable.Range(0, iSize).OrderBy(x => rng.Next()).ToList();
        }

        public override double tEvaluate(IList<bool> lSolution)
        {
            lSolution = Order(lSolution);
            return base.tEvaluate(lSolution);
        }

        private IList<bool> Order(IList<bool> solution)
        {
            return solution.Select((val, index) => new { val, index }).OrderBy(x => GenesOrder[x.index]).Select(x => x.val).ToList();
        }


    }
}
