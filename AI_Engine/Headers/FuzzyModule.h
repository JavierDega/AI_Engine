#pragma once
#include "FuzzyVariable.h"
#include "FuzzyTerms.h"
#include "FuzzyRule.h"
#include <map>

/// <summary>
/// This is the main class where the whole Fuzzy Process comes together. Every AI agent that will 
/// make use of Fuzzy Logic will need to instantiate one of these
/// </summary>
class FuzzyModule {
public:
	enum DefuzzifyType
	{
		Max_Av,
		//We could add other Defuzzify types here
	};

	//Will create an FLV, store it in our map and return it
	FuzzyVariable * CreateFLV(std::string FLV_Name);

	//Adds a rule to this module
	void AddRule(FuzzyTerm antecedent, FuzzyTerm consequence);

	/// <summary>
	/// Run through every Rule in the rule set, generating a confidence value for each rule
	/// </summary>
	void FuzzyInference();

	//Fuzzifies a value against a FLV, setting the DOMs for all Fuzzy sets in that FLV
	void Fuzzify(std::string FLV_Name, float val);

	//Returns the defuzzified value of a set using the specified method
	float Defuzzify(std::string FLV_Name, DefuzzifyType method = DefuzzifyType::Max_Av);

	//Variables
	//All FLVs will be stored in this map
	std::map<std::string, FuzzyVariable *> FLV_Map;

	//Ruleset will be stored in here
	std::vector<FuzzyRule*> Rule_List;;
};