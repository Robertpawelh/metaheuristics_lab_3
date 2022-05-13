using System;
using System.Collections.Generic;

using DominationComparers.BiObjective;
using Optimizers.BiObjective.NSGA2;
using Optimizers.Framework.PopulationOptimizers;
using Utility;

namespace Selections.BiObjective
{
    sealed class NSGA2Selection : ASelection<Tuple<double, double>>
    {
        private readonly UniformIntegerRandom rng;
        private readonly Shuffler shuffler;

        private readonly int size;
        private readonly Tuple<double, double> maxObjectiveValues;
        private readonly IDominationComparer dominationComparer;
        private readonly bool modifyPopulation;

        private object rankingRef;

        public NSGA2Selection(int size, Tuple<double, double> maxObjectiveValues, IDominationComparer dominationComparer, bool modifyPopulation = true, int? seed = null)
        {
            rng = new UniformIntegerRandom(seed);
            shuffler = new Shuffler(seed);

            this.size = size;
            this.maxObjectiveValues = maxObjectiveValues;
            this.dominationComparer = dominationComparer;
            this.modifyPopulation = modifyPopulation;

            rankingRef = null;
        }

        protected override void AddToNewPopulation<Element>(List<Individual<Element, Tuple<double, double>>> population,
                                                            List<Individual<Element, Tuple<double, double>>> newPopulation)
        {
            if (!(rankingRef is Ranking<Element> ranking))
            {
                ranking = new Ranking<Element>(maxObjectiveValues, dominationComparer);
                rankingRef = ranking;
            }

            population = Elitism(population, ranking);

            Dictionary<Individual<Element, Tuple<double, double>>, int> rankingVals = new Dictionary<Individual<Element, Tuple<double, double>>, 
                                                                                                     int>();
            for(int i = 0; i < ranking.RankingList.Count; ++i)
            {
                rankingVals.Add(ranking.RankingList[i], i);
            }

            List<int> indices = Utils.CreateIndexList(population.Count);

            for (int i = 0; i < population.Count; ++i)
            {
                shuffler.Shuffle(indices);

                newPopulation.Add(new Individual<Element, Tuple<double, double>>(TournamentWinner(population, indices, rankingVals)));
            }
        }

        private List<Individual<Element, Tuple<double, double>>> Elitism<Element>(List<Individual<Element, Tuple<double, double>>> population,
                                                                                  Ranking<Element> ranking)
        {
            List<Individual<Element, 
                            Tuple<double, double>>> modifiedPopulation = modifyPopulation ? population : 
                                                                                            new List<Individual<Element, 
                                                                                                                Tuple<double, double>>>(population);
            
            foreach(Individual<Element, Tuple<double, double>> individual in modifiedPopulation)
            {
                ranking.Add(individual);
            }

            ranking.Update();
            ranking.RemoveFrom(population.Count);

            modifiedPopulation.Clear();
            modifiedPopulation.AddRange(ranking.RankingList);

            return modifiedPopulation;
        }

        private Individual<Element, Tuple<double, double>> TournamentWinner<Element>(List<Individual<Element, Tuple<double, double>>> population, 
                                                                                     List<int> indices, 
                                                                                     Dictionary<Individual<Element, Tuple<double, double>>, 
                                                                                                int> rankingVals)
        {
            Individual<Element, Tuple<double, double>> winner = population[indices[0]];
            for (int i = 1; i < size; ++i)
            {
               if (rankingVals[population[indices[i]]] > rankingVals[winner])
                {
                    winner = population[indices[i]];
                }
            }

            return winner;
        }
    }
}
