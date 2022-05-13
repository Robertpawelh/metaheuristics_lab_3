using System.Collections.Generic;


namespace Utility
{
    class Utils
    {
        public static List<int> CreateIndexList(int size)
        {
            List<int> indices = new List<int>(size);
            for (int i = 0; i < size; ++i)
            {
                indices.Add(i);
            }

            return indices;
        }

        public static void Swap<T>(ref T lhs, ref T rhs)
        {
            T temp = lhs;
            lhs = rhs;
            rhs = temp;
        }

        public static void Swap<T>(List<T> list, int index1, int index2)
        {
            T temp = list[index1];
            list[index1] = list[index2];
            list[index2] = temp;
        }
    }
}
