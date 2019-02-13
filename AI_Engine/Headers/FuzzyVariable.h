#pragma once
#include "FuzzySets.h"
#include <map>
/// <summary>
/// This represents an FLV (Fuzzy Linguistic Variable). This contains our sets
/// </summary>
class FuzzyVariable {
private:
	void AdjustRangeToFit(float min, float max);

public:
	FuzzyVariable();

	/// <summary>
	/// This method adds a triangular set to this FLV
	/// </summary>
	FuzzySet * AddTriangularSet(std::string name, float minBound, float peak, float maxBound);

	/// <summary>
	/// This method adds a left shoulder set to this FLV
	/// </summary>
	FuzzySet * AddLeftShoulderSet(std::string name, float minBound, float peak, float maxBound);

	/// <summary>
	/// This method adds a right shoulder set to this FLV
	/// </summary>
	FuzzySet * AddRightShoulderSet(std::string name, float minBound, float peak, float maxBound);

	/// <summary>
	/// Fuzzifies a value against every single set in this FLV, storing the DOM within each set
	/// </summary>
	/// <param name="val"></param>
	void Fuzzify(float val);

	/// <summary>
	/// It's up to you to implement this method!
	/// </summary>
	/// <returns></returns>
	float DefuzzifyMaxAv();

	//Variables
	/// <summary>
	/// The map of sets
	/// </summary>
	std::map< std::string, FuzzySet*> MemberSets;
	//Min and Max ranges are adjusted as we add more member sets
	float MinRange, MaxRange;
};
