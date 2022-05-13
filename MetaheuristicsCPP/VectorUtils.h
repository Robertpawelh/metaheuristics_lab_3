#pragma once

#include <vector>

using namespace std;

namespace VectorUtils
{
	template <class T>
	void vClear(vector<T*> &vVector)
	{
		for (size_t i = 0; i < vVector.size(); i++)
		{
			delete vVector[i];
		}//for (size_t i = 0; i < vVector.size(); i++)

		vVector.clear();
	}//void vClear(vector<T*> &vVector)

	template <class T>
	void vErase(vector<T*> &vVector, size_t iFrom)
	{
		for (size_t i = iFrom; i < vVector.size(); i++)
		{
			delete vVector[i];
		}//for (size_t i = iFrom; i < vVector.size(); i++)

		vVector.erase(vVector.begin() + iFrom, vVector.end());
	}//void vClear(vector<T*> &vVector)
}//namespace VectorUtils
