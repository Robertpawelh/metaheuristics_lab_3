using System;
using System.Collections.Generic;

using DominationComparers.BiObjective;
using Utility;


namespace Optimizers.BiObjective.NSGA2
{
    class Ranking<Element>
    {
        private readonly Tuple<double, double> maxObjectiveValues;
        private readonly IDominationComparer dominationComparer;

        public List<Individual<Element>> RankingList { get; }

        public Ranking(Tuple<double, double> maxObjectiveValues, IDominationComparer dominationComparer)
        {
            this.maxObjectiveValues = maxObjectiveValues;
            this.dominationComparer = dominationComparer;

            RankingList = new List<Individual<Element>>();
        }

        public void Add(Framework.PopulationOptimizers.Individual<Element, Tuple<double, double>> individual)
        {
            RankingList.Add(new Individual<Element>(individual));
        }

        public void RemoveFrom(int index)
        {
            RankingList.RemoveRange(index, RankingList.Count - index);
        }

        public void Update()
        {
            ResetRankingIndividualData();
            List<Individual<Element>> currentParetoFront = UpdateDominationStatus();

            int frontIndex = 0;
            List<Individual<Element>> nextParetoFront = new List<Individual<Element>>();
            while(currentParetoFront.Count > 0)
            {
                UpdateCrowdingDistance(currentParetoFront);

                ++frontIndex;
                foreach(Individual<Element> ith in currentParetoFront)
                {
                    foreach(Individual<Element> dominatedByIth in ith.Dominates)
                    {
                        if(--dominatedByIth.DominationCounter == 0)
                        {
                            dominatedByIth.FrontIndex = frontIndex;
                            nextParetoFront.Add(dominatedByIth);
                        }
                    }
                }

                Utils.Swap(ref currentParetoFront, ref nextParetoFront);
                nextParetoFront.Clear();
            }

            RankingList.Sort((x, y) =>
            {
                if(x.FrontIndex == y.FrontIndex)
                {
                    if(x.CrowdingDistance == y.CrowdingDistance)
                    {
                        return 0;
                    }

                    return (y.CrowdingDistance < x.CrowdingDistance) ? -1 : 1;
                }

                return (x.FrontIndex < y.FrontIndex) ? -1 : 1;
            });
        }

        private void ResetRankingIndividualData()
        {
            foreach(Individual<Element> individual in RankingList)
            {
                individual.CrowdingDistance = 0.0;
                individual.DominationCounter = 0;
                individual.Dominates.Clear();
            }
        }

        private List<Individual<Element>> UpdateDominationStatus()
        {
            List<Individual<Element>> paretoFront = new List<Individual<Element>>();

            for(int i = 0; i < RankingList.Count - 1; ++i)
            {
                Individual<Element> ith = RankingList[i];

                for (int j = i + 1; j < RankingList.Count - 1; ++j)
                {
                    Individual<Element> jth = RankingList[j];
                    int dominationComparison = dominationComparer.Compare(ith.Fitness, jth.Fitness);

                    if(dominationComparison > 0)
                    {
                        ith.Dominates.Add(jth);
                        ++jth.DominationCounter;
                    }
                    else if(dominationComparison < 0)
                    {
                        jth.Dominates.Add(ith);
                        ++ith.DominationCounter;
                    }
                }

                if(ith.DominationCounter == 0)
                {
                    ith.FrontIndex = 0;
                    paretoFront.Add(ith);
                }
            }

            return paretoFront;
        }

        private void UpdateCrowdingDistance(List<Individual<Element>> currentParetoFront)
        {
            UpdateCrowdingDistanceFirstObjective(currentParetoFront);
            UpdateCrowdingDistanceSecondObjective(currentParetoFront);
        }

        private void UpdateCrowdingDistanceFirstObjective(List<Individual<Element>> currentParetoFront)
        {
            currentParetoFront.Sort((x, y) => (int)(x.Fitness.Item1 - y.Fitness.Item1));

            currentParetoFront[0].CrowdingDistance = double.MaxValue / 2.0;
            currentParetoFront[currentParetoFront.Count - 1].CrowdingDistance = double.MaxValue / 2.0;

            for(int i = 1; i < currentParetoFront.Count - 1; ++i)
            {
                currentParetoFront[i].CrowdingDistance = (currentParetoFront[i + 1].Fitness.Item1 - currentParetoFront[i - 1].Fitness.Item1) 
                                                         / maxObjectiveValues.Item1;
            }
        }

        private void UpdateCrowdingDistanceSecondObjective(List<Individual<Element>> currentParetoFront)
        {
            currentParetoFront.Sort((x, y) => (int)(x.Fitness.Item2 - y.Fitness.Item2));

            currentParetoFront[0].CrowdingDistance += double.MaxValue / 2.0;
            currentParetoFront[currentParetoFront.Count - 1].CrowdingDistance += double.MaxValue / 2.0;

            for (int i = 1; i < currentParetoFront.Count - 1; ++i)
            {
                currentParetoFront[i].CrowdingDistance += (currentParetoFront[i + 1].Fitness.Item2 - currentParetoFront[i - 1].Fitness.Item2)
                                                          / maxObjectiveValues.Item2;
            }
        }
    }
}
