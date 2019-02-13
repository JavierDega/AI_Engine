#include "pch.h"
#include "..\Headers\FuzzyModule.h"

using namespace std;

FuzzyVariable * FuzzyModule::CreateFLV(std::string FLV_Name) 
{
	FuzzyVariable * theFLV = new FuzzyVariable();
	FLV_Map.emplace(FLV_Name, theFLV);
	return theFLV;
}

void FuzzyModule::AddRule(FuzzyTerm antecedent, FuzzyTerm consequence)
{
	//You have to write the class FuzzyRule!
	FuzzyRule * fr = new FuzzyRule(antecedent, consequence);
	Rule_List.push_back(fr);
}



void FuzzyModule::FuzzyInference() 
{
	//You have to implement this part yourself!
	for(FuzzyRule * fr : Rule_List)
	{
		///...
	}
}

void FuzzyModule::Fuzzify(std::string FLV_Name, float val)
{
	//You have to implement this part yourself!
	for(FuzzyRule * fr : Rule_List)
	{
		///...
	}
}

float FuzzyModule::Defuzzify(string FLV_Name, DefuzzifyType method)
{
	//@ITERATOR MIGHT NOT BE CODED RIGHT
	float rv = 0.0f;

	if (method == DefuzzifyType::Max_Av)
	{
		// Declaring iterator to a vector 

		auto ptr = FLV_Map.find(FLV_Name);
		if (ptr != FLV_Map.end())
		{
			//You have to implement this part yourself
			FuzzyVariable * FLV = ptr->second;
			rv = FLV->DefuzzifyMaxAv(); // this method is not implemented!
		}
	}

	return rv;

}