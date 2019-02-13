#include "pch.h"
#include "..\Headers\FuzzyVariable.h"

using namespace std;

void FuzzyVariable::AdjustRangeToFit(float min, float max)
{
	if (min < MinRange)
	{
		MinRange = min;
	}

	if (max > MaxRange)
	{
		MaxRange = max;
	}
}

FuzzyVariable::FuzzyVariable()
{
	MinRange = 0.0f;
	MaxRange = 0.0f;
}

FuzzySet * FuzzyVariable::AddTriangularSet(string name, float minBound, float peak, float maxBound)
{
	FuzzySet * fs = new FuzzySet_Triangle(peak, minBound, maxBound);
	MemberSets.emplace( name, fs);
	AdjustRangeToFit(minBound, maxBound);
	return fs;
}

FuzzySet * FuzzyVariable::AddLeftShoulderSet(string name, float minBound, float peak, float maxBound)
{
	FuzzySet * fs = new FuzzySet_LeftShoulder(peak, minBound, maxBound);
	MemberSets.emplace(name, fs);
	AdjustRangeToFit(minBound, maxBound);
	return fs;
}

FuzzySet * FuzzyVariable::AddRightShoulderSet(string name, float minBound, float peak, float maxBound)
{
	FuzzySet * fs = new FuzzySet_RightShoulder(peak, minBound, maxBound);
	MemberSets.emplace(name, fs);

	AdjustRangeToFit(minBound, maxBound);

	return fs;
}

void FuzzyVariable::Fuzzify(float val)
{
	for( pair<string, FuzzySet *> fs : MemberSets)
	{
		fs.second->DOM = fs.second->CalculateDOM(val);
	}
}

float FuzzyVariable::DefuzzifyMaxAv()
{
	return 0.0f;
}