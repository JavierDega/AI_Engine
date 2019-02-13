#pragma once
#include "FuzzySets.h"
#include <vector>

/// <summary>
/// The ruleset is the most difficult part of coding a Fuzzy Logic system, because it needs to be able to support complex
/// rules! 
/// Complex rule example: IF [(A1 AND A2) OR (NOT(A3) OR A4)] THEN [C1 AND C2]. 
/// This is an overcomplicated example, but your system needs to be able to support a rule like this
/// You may have to make changes to the FuzzySet class to make this work in a robust way. Good luck!
/// 
/// These classes can combine FuzzySets into the antecedent and consequent parts (so we can AND and OR them correctly)
/// This is essential for defining your ruleset.
/// </summary>
class FuzzyTerm
{
public:

	FuzzyTerm(FuzzySet * v1);

	virtual float GetDOM();

	virtual void SetDOM(float val);

	//Variables
	FuzzySet * Set;
};

/// <summary>
/// It is up to you to define the rest of this class and define other classes like FzOR, FzNOT and more...
/// </summary>
class FzAND 
	: public FuzzyTerm
{
public:
	//ANDs two Fuzzy sets
	FzAND(FuzzySet * v1, FuzzySet * v2);

	//ANDs three Fuzzy sets
	FzAND(FuzzySet * v1, FuzzySet * v2, FuzzySet * v3);

	//ANDs four Fuzzy sets
	FzAND(FuzzySet *  v1, FuzzySet * v2, FuzzySet * v3, FuzzySet * v4);

	/// <summary>
	/// This should work differently than the base class...
	/// </summary>
	/// <returns></returns>
	virtual float GetDOM()override;

	//Variables
	std::vector<FuzzySet *> Sets;
};
