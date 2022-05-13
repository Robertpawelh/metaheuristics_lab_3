#pragma once

#define _USE_MATH_DEFINES

#include "RealConstraints.h"
#include "Evaluation.h"

#include <cmath>
#include <vector>

using namespace Constraints;

using namespace std;

namespace Evaluations
{
	class CRealEvaluation : public CEvaluation<double, double>
	{
	public:
		CRealEvaluation(int iSize, double dMaxValue, double dLowerBound, double dUpperBound);

		virtual IConstraint<double> &cGetConstraint() { return c_constraint; }

	private:
		 CRealBoundingBoxConstraint c_constraint;
	};//class CRealEvaluation : public CEvaluation<double, double>


	class CRealHorizontalScalingEvaluation : public CEvaluation<double, double>
	{
	public:
		CRealHorizontalScalingEvaluation(IEvaluation<double, double> &cRealEvaluation, vector<double> &vFactors);

		virtual ~CRealHorizontalScalingEvaluation();

		virtual IConstraint<double> &cGetConstraint() { return *pc_constraint; }

	protected:
		virtual double t_evaluate(vector<double> &vSolution);

	private:
		CRealBoundingBoxConstraint *pc_constraint;

		IEvaluation<double, double> &c_real_evaluation;
		vector<double> v_factors;
	};//class CRealHorizontalScalingEvaluation : public CEvaluation<double, double>


	class CRealStepEvaluation : public CEvaluation<double, double>
	{
	public:
		CRealStepEvaluation(IEvaluation<double, double> &cRealEvaluation, vector<int> &vStepSizes);

		virtual IConstraint<double> &cGetConstraint() { return c_real_evaluation.cGetConstraint(); }

	protected:
		virtual double t_evaluate(vector<double> &vSolution);

	private:
		IEvaluation<double, double> &c_real_evaluation;
		vector<int> v_step_sizes;
	};//class CRealStepEvaluation : public CEvaluation<double, double>


	class CRealSphereEvaluation : public CRealEvaluation
	{
	public:
		CRealSphereEvaluation(int iSize);

	protected:
		virtual double t_evaluate(vector<double> &vSolution);
	};//class CRealSphereEvaluation : public CRealEvaluation


	class CRealSphere10Evaluation : public CProxyEvaluation<double, double>
	{
	public:
		CRealSphere10Evaluation(int iSize);

		virtual ~CRealSphere10Evaluation();

	private:
		CRealSphereEvaluation *pc_sphere_evaluation;
		CVerticalScalingEvaluation<double> *pc_vertical_scaling_evaluation;
	};//class CRealSphere10Evaluation : public CProxyEvaluation<double, double>


	class CRealEllipsoidEvaluation : public CProxyEvaluation<double, double>
	{
	public:
		CRealEllipsoidEvaluation(int iSize);

		virtual ~CRealEllipsoidEvaluation();

	private:
		CRealSphereEvaluation *pc_sphere_evaluation;
		CRealHorizontalScalingEvaluation *pc_horizontal_scaling_evaluation;
	};//class CRealEllipsoidEvaluation : public CProxyEvaluation<double, double>


	class CRealStep2SphereEvaluation : public CProxyEvaluation<double, double>
	{
	public:
		CRealStep2SphereEvaluation(int iSize);

		virtual ~CRealStep2SphereEvaluation();

	private:
		CRealSphereEvaluation *pc_sphere_evaluation;
		CRealStepEvaluation *pc_step_evaluation;
	};//class CRealStep2SphereEvaluation : public CProxyEvaluation<double, double>


	class CRealRastriginEvaluation : public CRealEvaluation
	{
	public:
		CRealRastriginEvaluation(int iSize);

	protected:
		virtual double t_evaluate(vector<double> &vSolution);
	};//class CRealRastriginEvaluation : public CRealEvaluation


	class CRealAckleyEvaluation : public CRealEvaluation
	{
	public:
		CRealAckleyEvaluation(int iSize);

	protected:
		virtual double t_evaluate(vector<double> &vSolution);
	};//class CRealAckleyEvaluation : public CRealEvaluation
}//namespace Evaluations