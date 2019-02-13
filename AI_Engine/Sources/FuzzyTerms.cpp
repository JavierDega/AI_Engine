#include "pch.h"
#include "..\Headers\FuzzyTerms.h"

FuzzyTerm::FuzzyTerm(FuzzySet * v1)
{
	Set = v1;
}

float FuzzyTerm::GetDOM()
{
	return Set->DOM;
}

void FuzzyTerm::SetDOM(float val)
{
	Set->DOM = val;
}

FzAND::FzAND(FuzzySet * v1, FuzzySet * v2) : FuzzyTerm(v1)
{
	Sets.push_back(v1);
	Sets.push_back(v2);
}

FzAND::FzAND(FuzzySet * v1, FuzzySet * v2, FuzzySet * v3) : FuzzyTerm(v1)
{

}

FzAND::FzAND(FuzzySet * v1, FuzzySet * v2, FuzzySet * v3, FuzzySet * v4) : FuzzyTerm(v1)
{

}

float FzAND::GetDOM()
{
	//Algorithm here
	return FuzzyTerm::GetDOM();
}
