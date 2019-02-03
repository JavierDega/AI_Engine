#pragma once
#include <stack>
/// <summary>
/// Abstract classes contain no functionality, they are made to be inherited from
/// </summary>
class Goals
{
public:
	virtual void Activate() = 0;

	virtual int Process() = 0;

	virtual void Terminate() = 0;

	virtual void AddSubgoal(Goals * g) = 0;

	//Variables
	bool IsActive = false;
};

/// <summary>
/// Represents a composite goal, this should be inherited from for custom functionality
/// </summary>
class CompositeGoal 
	: public Goals
{
public:
	/// <summary>
	/// We could use this for initialisations
	/// </summary>
	virtual void Activate()override;

	/// <summary>
	/// Adds a goal onto subgoals stack
	/// </summary>
	/// <param name="g"></param>
	virtual void AddSubgoal(Goals * g)override;

	/// <summary>
	/// Processes subgoals, also removes subgoals if applicable
	/// </summary>
	/// <returns></returns>
	virtual int Process()override;

	/// <summary>
	/// Any uninitialisations
	/// </summary>
	virtual void Terminate()override;

protected:
	//Stack represents a LIFO (last in, first out) container
	std::stack<Goals*> subgoals;
};

/// <summary>
/// Represents an atomic goal, this cannot have any subgoals
/// </summary>
class AtomicGoal 
	: public Goals
{
public:
	virtual void Activate()override;

	virtual void AddSubgoal(Goals * g)override {/*Does nothing*/ };

	virtual int Process()override;

	virtual void Terminate()override;
};

/// <summary>
/// Inherited from composite goals
/// </summary>
class BuySword 
	: public CompositeGoal
{
	virtual int Process()override;

	bool NotEnoughGold();
};

//Inherited from atomic goals
class GetGold 
	: public AtomicGoal
{
	virtual int Process()override;

};
