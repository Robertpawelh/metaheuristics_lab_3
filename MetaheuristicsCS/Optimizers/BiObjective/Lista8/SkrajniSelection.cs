using System;
using System.Collections.Generic;
using System.Linq;
using DominationComparers.BiObjective;
using Optimizers.Framework.PopulationOptimizers;
using Selections;
using Utility;

namespace MetaheuristicsCS.Optimizers.BiObjective.Lista8
{
    class SkrajniSelection : ASelection<Tuple<double, double>>
    {
        private readonly Shuffler shuffler;
        private readonly IDominationComparer dominationComparer;

        public SkrajniSelection(IDominationComparer dominationComparer, int? seed = null)
        {
            shuffler = new Shuffler(seed);
            this.dominationComparer = dominationComparer;
        }

        
        protected override void AddToNewPopulation<Element>(List<Individual<Element, Tuple<double, double>>> population,
                                                            List<Individual<Element, Tuple<double, double>>> newPopulation)
        {
            List<int> indices = Utils.CreateIndexList(population.Count);
            List<int> indicesCrit1 = indices.OrderByDescending(x => population[x].Fitness.Item1).ToList();
            List<int> indicesCrit2 = indices.OrderByDescending(x => population[x].Fitness.Item2).ToList();

            Random rnd = new Random();
            for (int xx = 0; xx < 10; xx++)
            {
                int index = rnd.Next(0, population.Count/20);
                newPopulation.Add(new Individual<Element, Tuple<double, double>>(population[indicesCrit1[index]]));
                newPopulation.Add(new Individual<Element, Tuple<double, double>>(population[indicesCrit2[index]]));
            }

            foreach (int index in indicesCrit1)
            {
                var ind = population[index];
                bool wasntDominated = true;
                foreach (var other in newPopulation)
                {
                    bool isDominated = (dominationComparer.Compare(ind.Fitness, other.Fitness) < 0);
                    if (isDominated)
                    {
                        wasntDominated = false;
                        break;
                    }         
                }
                if (wasntDominated && (newPopulation.Count - 10) < 0.25 * population.Count)
                {
                    newPopulation.Add(new Individual<Element, Tuple<double, double>>(ind));
                    indices.RemoveAll(item => item == index);
                }
            }

            foreach (int index in indicesCrit2)
            {
                var ind = population[index];
                bool wasntDominated = true;

                foreach (var other in newPopulation)
                {
                    bool isDominated = (dominationComparer.Compare(ind.Fitness, other.Fitness) < 0);
                    if (isDominated)
                    {
                        wasntDominated = false;
                        break;
                    }
                }
                if (wasntDominated && (newPopulation.Count - 10) < 0.5 * population.Count)
                {
                    newPopulation.Add(new Individual<Element, Tuple<double, double>>(ind));
                    indices.RemoveAll(item => item == index);
                }
            }

            shuffler.Shuffle(indices);

            //Console.WriteLine("Przed: " + newPopulation.Count);
            int itemsToAdd = population.Count - newPopulation.Count;
            for (int j = 0; j < itemsToAdd;  ++j)
            {
                Individual<Element, Tuple<double, double>> ith = population[j];
                Individual<Element, Tuple<double, double>> jth = population[indices[j]];

                Individual<Element, Tuple<double, double>> nonDominated = (dominationComparer.Compare(ith.Fitness,
                                                                                                      jth.Fitness) >= 0) ? ith : jth;

                newPopulation.Add(new Individual<Element, Tuple<double, double>>(nonDominated));
            }
            //Console.WriteLine("Po: " + newPopulation.Count + "Diff: " + itemsToAdd + "popcount " + population.Count);
        }
    }
}
