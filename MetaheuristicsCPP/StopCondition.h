#pragma once

#include <cfloat>
#include <cmath>
#include <ctime>

namespace StopConditions
{
	class IStopCondition
	{
	public:
		virtual ~IStopCondition() = default;

		virtual bool bStop(long long iIterationNumber, long long iFFE, clock_t tStartTime) = 0;
	};//class IStopCondition
}//namespace StopConditions