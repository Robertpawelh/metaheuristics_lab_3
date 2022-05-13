#pragma once

#include "StopCondition.h"
#include "TimeUtils.h"

#include <cfloat>
#include <ctime>

namespace StopConditions
{
	class CIterationsStopCondition : public IStopCondition
	{
	public:
		CIterationsStopCondition(long long iMaxIterationNumber);

		virtual bool bStop(long long iIterationNumber, long long iFFE, clock_t tStartTime);

	private:
		long long i_max_iteration_number;
	};//class CIterationsStopCondition : public IStopCondition


	class CFFEStopCondition : public IStopCondition
	{
	public:
		CFFEStopCondition(long long iMaxFFE);

		virtual bool bStop(long long iIterationNumber, long long iFFE, clock_t tStartTime);

	private:
		long long i_max_ffe;
	};//class CFFEStopCondition : public IStopCondition


	class CRunningTimeStopCondition : public IStopCondition
	{
	public:
		CRunningTimeStopCondition(double dMaxRunningTime);

		virtual bool bStop(long long iIterationNumber, long long iFFE, clock_t tStartTime);

	private:
		double d_max_running_time;
	};//class CRunningTimeStopCondition : public IStopCondition
}//namespace StopConditions