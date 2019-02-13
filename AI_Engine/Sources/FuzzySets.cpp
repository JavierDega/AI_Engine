#include "pch.h"
#include "..\Headers\FuzzySets.h"

FuzzySet::FuzzySet(float RepresentativeValue)
{
	DOM = 0.0f;
	RepresentativeValue = RepresentativeValue;
}
FuzzySet::~FuzzySet()
{
}
float FuzzySet::CalculateDOM(float val)
{
	return 0.0f;
}

void FuzzySet::OR_DOM(float val)
{
	if (DOM < val)
	{
		DOM = val;
	}
}

void FuzzySet::ClearDOM() 
{ 
	DOM = 0.0f;
}

FuzzySet_Triangle::FuzzySet_Triangle(float mid, float left, float right) 
	: FuzzySet(mid)
{
	PeakPoint = mid;
	LeftOffset = left;
	RightOffset = right;
}

float FuzzySet_Triangle::CalculateDOM(float val)
{
	//NOTE: You could get divide by 0 errors with this code, add some checks to stop that!

	float rv = 0.0f;
	//Find DOM if left of centre
	float leftpoint = PeakPoint - LeftOffset;
	float rightpoint = PeakPoint + RightOffset;
	if (val <= PeakPoint && val >= leftpoint)
	{
		float ZeroedVal = val - leftpoint;
		float ZeroedPeak = PeakPoint - leftpoint;

		rv = ZeroedVal / ZeroedPeak;
	}
	//Find DOM right of centre
	else if (val > PeakPoint && val < rightpoint)
	{
		float ZeroedVal = val - PeakPoint;
		float ZeroedRight = rightpoint - PeakPoint;

		rv = ZeroedVal / ZeroedRight;
	}
	//Out of range, return 0
	else
	{
		rv = 0.0f;
	}

	return rv;
}

FuzzySet_LeftShoulder::FuzzySet_LeftShoulder(float mid, float left, float right) 
	: FuzzySet(mid)
{
	PeakPoint = mid;
	LeftOffset = left;
	RightOffset = right;
}

float FuzzySet_LeftShoulder::CalculateDOM(float val)
{
	//Incomplete...

	float rv = 0.0f;


	return rv;
}

float FuzzySet_RightShoulder::CalculateDOM(float val) 
{
	//Incomplete...

	float rv = 0.0f;


	return rv;
}
