#pragma once

/// <summary>
/// This is the BASE class for all our FuzzySets, we will inherit from this to create different types of "membership functions" 
/// (see FuzzySet_Triangle below)
/// </summary>
class FuzzySet {
public:

	FuzzySet(float RepresentativeValue);
	virtual ~FuzzySet();
	//Needs to be overridden in child class for proper functionality
	virtual float CalculateDOM(float val);
	//If value is higher than the current DOM, then set that as the DOM
	void OR_DOM(float val);
	//Helpers
	void ClearDOM();

	//Variables
	float DOM;
	float RepresentativeValue;
};

/// <summary>
/// An example of inheriting to create a triangle membership function
/// </summary>
class FuzzySet_Triangle 
	: public FuzzySet
{
public:

	FuzzySet_Triangle(float mid, float left, float right);

	//This will return a DOM using said value
	virtual float CalculateDOM(float val)override;

	//Variables
private:
	float PeakPoint, LeftOffset, RightOffset;
};

/// <summary>
/// This class is incomplete / not working
/// </summary>
class FuzzySet_LeftShoulder 
	: public FuzzySet
{
public:
	FuzzySet_LeftShoulder(float mid, float left, float right);

	//This will return a DOM using said value
	virtual float CalculateDOM(float val)override;
private:
	float PeakPoint, LeftOffset, RightOffset;
};

/// <summary>
/// This class is incomplete / not working
/// </summary>
class FuzzySet_RightShoulder 
	: public FuzzySet
{
public:
	FuzzySet_RightShoulder(float mid, float left, float right) : FuzzySet(mid)
	{
		PeakPoint = mid;
		LeftOffset = left;
		RightOffset = right;
	}

	//This will return a DOM using said value
	virtual float CalculateDOM(float val)override;

private:
	float PeakPoint, LeftOffset, RightOffset;
};