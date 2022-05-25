using System;
using System.Collections.Generic;
using System.Linq;
using DominationComparers.BiObjective;
using Optimizers.Framework.PopulationOptimizers;
using Selections;
using Utility;

namespace MetaheuristicsCS.Optimizers.BiObjective.Lista8
{
    class SkrajniSelectionDwa : ASelection<Tuple<double, double>>
    {
        private readonly Shuffler shuffler;
        private readonly IDominationComparer dominationComparer;

        public SkrajniSelectionDwa(IDominationComparer dominationComparer, int? seed = null)
        {
            shuffler = new Shuffler(seed);
            this.dominationComparer = dominationComparer;
        }

        protected override void AddToNewPopulation<Element>(List<Individual<Element, Tuple<double, double>>> population,
                                                    List<Individual<Element, Tuple<double, double>>> newPopulation)
        {
            List<int> indices = Utils.CreateIndexList(population.Count);
            int pseudoTournamentSize = 4;

            Random rnd = new Random();

            while (population.Count != newPopulation.Count)
            {
                Individual<Element, Tuple<double, double>> ith = population[rnd.Next(0, population.Count)];
                bool wasDominated = false;
                for (int i = 0; i < pseudoTournamentSize; i++)
                {
                    Individual<Element, Tuple<double, double>> jth = population[rnd.Next(0, population.Count)];
                    if (dominationComparer.Compare(ith.Fitness, jth.Fitness) < 0)
                    {
                        wasDominated = true;
                        break;
                    }
                }
                if (!wasDominated)
                {
                    newPopulation.Add(new Individual<Element, Tuple<double, double>>(ith));
                }
            }
        }
    }
}


/*
protected override void AddToNewPopulation<Element>(List<Individual<Element, Tuple<double, double>>> population,
                                                    List<Individual<Element, Tuple<double, double>>> newPopulation)
{
    List<int> indices = Utils.CreateIndexList(population.Count);
    List<int> indicesCrit1 = indices.OrderByDescending(x => population[x].Fitness.Item1).ToList();
    List<int> indicesCrit2 = indices.OrderByDescending(x => population[x].Fitness.Item2).ToList();


    int i = 0;
    bool negative = false;
    shuffler.Shuffle(indices);
    while (newPopulation.Count < population.Count / 2)
    {
        Individual<Element, Tuple<double, double>> ith = population[indicesCrit1[negative ? i : population.Count - i - 1]];
        Individual<Element, Tuple<double, double>> jth = population[indices[i]];

        Individual<Element, Tuple<double, double>> nonDominated = (dominationComparer.Compare(ith.Fitness,
                                                                                              jth.Fitness) >= 0) ? ith : jth;

        newPopulation.Add(new Individual<Element, Tuple<double, double>>(nonDominated));

        if (negative) i = i + 1;
        negative = !negative;
    };


    i = 0;
    negative = false;
    shuffler.Shuffle(indices);

    while (newPopulation.Count < population.Count)
    {
        Individual<Element, Tuple<double, double>> ith = population[indicesCrit2[negative ? i : population.Count - i - 1]];
        Individual<Element, Tuple<double, double>> jth = population[indices[i]];

        Individual<Element, Tuple<double, double>> nonDominated = (dominationComparer.Compare(ith.Fitness,
                                                                                              jth.Fitness) >= 0) ? ith : jth;

        newPopulation.Add(new Individual<Element, Tuple<double, double>>(nonDominated));

        if (negative) i = i + 1;
        negative = !negative;
    };


    //shuffler.Shuffle(indices);
}
}
}

*/