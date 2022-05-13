#include "StopConditions.h"

using namespace StopConditions;


CIterationsStopCondition::CIterationsStopCondition(long long iMaxIterationNumber)
	: i_max_iteration_number(iMaxIterationNumber)
{

}//CIterationsStopCondition::CIterationsStopCondition(long long iMaxIterationNumber)

bool CIterationsStopCondition::bStop(long long iIterationNumber, long long iFFE, clock_t tStartTime)
{
	return iIterationNumber >= i_max_iteration_number;
}//bool CIterationsStopCondition::bStop(long long iIterationNumber, long long iFFE, clock_t tStartTime)


CFFEStopCondition::CFFEStopCondition(long long iMaxFFE)
	: i_max_ffe(iMaxFFE)
{

}//CFFEStopCondition::CFFEStopCondition(long long iMaxFFE)

bool CFFEStopCondition::bStop(long long iIterationNumber, long long iFFE, clock_t tStartTime)
{
	return iFFE >= i_max_ffe;
}//bool CFFEStopCondition::bStop(long long iIterationNumber, long long iFFE, clock_t tStartTime)


CRunningTimeStopCondition::CRunningTimeStopCondition(double dMaxRunningTime)
	: d_max_running_time(dMaxRunningTime)
{

}//CRunningTimeStopCondition::CRunningTimeStopCondition(double dMaxRunningTime)

bool CRunningTimeStopCondition::bStop(long long iIterationNumber, long long iFFE, clock_t tStartTime)
{
	return TimeUtils::dCalculateSeconds(tStartTime) >= d_max_running_time;
}//bool CRunningTimeStopCondition::bStop(long long iIterationNumber, long long iFFE, clock_t tStartTime)