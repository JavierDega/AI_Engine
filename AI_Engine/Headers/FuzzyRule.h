#pragma once
#include "FuzzyTerms.h"
/// <summary>
/// A fuzzy rule is a container for two FuzzyTerms: an antecedent and consequent.
/// It should have methods for calculating confidence values
/// It's up to you to write this class!
/// </summary>
class FuzzyRule
{
public:
	FuzzyRule(FuzzyTerm antecedent, FuzzyTerm consequent);

};
