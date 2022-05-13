using System;
using System.Collections.Generic;

using DominationComparers.BiObjective;
using Utility;

namespace Optimizers.BiObjective
{
    class ParetoFront
    {
        private readonly Tuple<double, double> objectiveMaxValues;
        private readonly IDominationComparer dominationComparer;
        private readonly List<Tuple<double, double>> optimalFront;

        public List<Tuple<double, double>> Front { get; private set; }

        public ParetoFront(Tuple<double, double> objectiveMaxValues, List<Tuple<double, double>> optimalParetoFront, 
                           IDominationComparer dominationComparer)
        {
            this.objectiveMaxValues = objectiveMaxValues;
            optimalFront = optimalParetoFront;
            this.dominationComparer = dominationComparer;
            Front = new List<Tuple<double, double>>();
        }

        public bool Add(Tuple<double, double> objectiveValues)
        {
            bool added = false;
            bool dominated = false;

            int dominatedIndividuals = 0;

            for(int i = 0; i < Front.Count && !dominated; ++i)
            {
                int dominationComparison = dominationComparer.Compare(objectiveValues, Front[i - dominatedIndividuals]);

                if(dominationComparison > 0)
                {
                    Utils.Swap(Front, i - dominatedIndividuals, Front.Count - 1 - dominatedIndividuals);
                    ++dominatedIndividuals;
                }
                else if(dominationComparison < 0)
                {
                    dominated = true;
                }
            }

            if(!dominated)
            {
                if(dominatedIndividuals > 0)
                {
                    Front.RemoveRange(Front.Count - dominatedIndividuals, dominatedIndividuals);
                }

                Front.Sort((x, y) =>
                {
                    if (x.Item1 == y.Item1)
                    {
                        if (x.Item2 == y.Item2)
                            return 0;

                        return (x.Item2 > y.Item2) ? -1 : 1;
                    }

                    return (x.Item1 < y.Item1) ? -1 : 1;
                });

                added = Insert(objectiveValues);
            }

            return added;
        }

        public double HyperVolume()
        {
            double hyperVolume = 0.0;

            if(Front.Count > 0)
            {
                hyperVolume += (Front[0].Item1 - 0) * (objectiveMaxValues.Item2 - Front[0].Item2);

                for(int i = 1; i < Front.Count; ++i)
                {
                    hyperVolume += (Front[i].Item1 - Front[i - 1].Item1) * (objectiveMaxValues.Item2 - Front[i].Item2);
                }

                hyperVolume += (objectiveMaxValues.Item1 - Front[Front.Count - 1].Item1) * (objectiveMaxValues.Item2 - 0);
            }

            return hyperVolume;
        }

        public double InversedGenerationalDistance()
        {
            if(Front.Count == 0 || optimalFront.Count == 0)
            {
                return double.MaxValue;
            }

            double igdSum = 0.0;
            foreach(Tuple<double, double> optimalObjectiveValues in optimalFront)
            {
                igdSum += MinDistance(optimalObjectiveValues);
            }

            return igdSum / optimalFront.Count;
        }

        private bool Insert(Tuple<double, double> objectiveValues)
        {
            bool found = false;
            Tuple<double, double> objectiveValuesCopy = new Tuple<double, double>(objectiveValues.Item1, objectiveValues.Item2);

            if(Front.Count == 0)
            {
                Front.Add(objectiveValuesCopy);
            }
            else
            {
                bool inserted = false;

                for(int i = 0; i < Front.Count && !found && !inserted; ++i)
                {
                    if(objectiveValues.Item1 < Front[i].Item1)
                    {
                        Front.Insert(i, objectiveValuesCopy);
                        inserted = true;
                    }
                    else if(objectiveValues.Item1 == Front[i].Item1)
                    {
                        if(objectiveValues.Item2 == Front[i].Item2)
                        {
                            found = true;
                            inserted = true;
                        }
                        else if (objectiveValues.Item2 > Front[i].Item2)
                        {
                            Front.Insert(i, objectiveValuesCopy);
                            inserted = true;
                        }
                    }
                }

                if(!inserted)
                {
                    Front.Add(objectiveValuesCopy);
                }
            }

            return !found;
        }

        private double MinDistance(Tuple<double, double> optimalObjectiveValues)
        {
            double minSquaredDistance = double.MaxValue;
            foreach(Tuple<double, double> objectiveValues in Front)
            {
                minSquaredDistance = MinSquaredDistance(optimalObjectiveValues, objectiveValues, minSquaredDistance);
            }

            return Math.Sqrt(minSquaredDistance);
        }

        private double MinSquaredDistance(Tuple<double, double> optimalObjectiveValues, Tuple<double, double> objectiveValues, 
                                          double minSquaredDistance)
        {
            double squaredDistance = Math.Pow(optimalObjectiveValues.Item1 - objectiveValues.Item1, 2.0);
            if(squaredDistance < minSquaredDistance)
            {
                squaredDistance += Math.Pow(optimalObjectiveValues.Item2 - objectiveValues.Item2, 2.0);
            }

            return Math.Min(minSquaredDistance, squaredDistance);
        }
    }
}
