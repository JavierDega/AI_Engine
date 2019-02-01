#pragma once
#include "Blackboard.h"
#include <stdlib.h>
///ABSTRACT CLASSES + COMPOSITE NODE TYPES: TO DO
///PARALLEL SEQUENCE?
///RANDOM SELECTOR?
///

/// <summary>
/// Execute can return one of three things
/// </summary>
enum BTStatus
{
	RUNNING,
	SUCCESS,
	FAILURE
};

/// <summary>
/// Base class. Sets the foundations for everything else
/// </summary>
class BTNode
{
public:
	BTNode(Blackboard bb);

	virtual BTStatus Execute() = 0;

	/// <summary>
	/// Reset should be overidden in child classes as and when necessary
	/// It should be called when a node is abruptly aborted before it can finish with a success or failure
	/// i.e the node was still RUNNING when it is aborted you need to gracefully handle it to avoid unintended bugs
	/// See DelayNode, CompositeNode and DecoratorNode for examples
	/// </summary>
	virtual void Reset();

	protected:
	Blackboard bb;
};

/// <summary>
/// Base class for node that can take child nodes. Only meant to be used in subclasses like Selector and Sequence,
/// but you can add other subclass types (e.g. RandomSelector, RandomSequence, Parallel etc.)
/// </summary>
class CompositeNode : 
	public BTNode
{
public:
	CompositeNode(Blackboard bb);
	~CompositeNode();
	virtual void AddChild(BTNode * child);
	/// <summary>
	/// When a composite node is reset it set the child index back to 0, and it should propogate the reset down to all its children
	/// </summary>
	virtual void Reset();

protected:
	int CurrentChildIndex;
	std::vector< BTNode * > children;
};

/// <summary>
/// Selectors execute their children in order until a child succeeds, at which point it stops execution
/// If a child returns RUNNING, then it will need to stop execution but resume from the same point the next time it executes
/// </summary>
class Selector : 
	public CompositeNode
{
public:
	Selector(Blackboard bb);

	virtual BTStatus Execute();
};

/// <summary>
/// Sequences execute their children in order until a child fails, at which point it stops execution
/// If a child returns RUNNING, then it will need to stop execution but resume from the same point the next time it executes
/// </summary>
class Sequence : 
	public CompositeNode
{
public:
	Sequence(Blackboard bb);

	virtual BTStatus Execute();
};

/// <summary>
/// Decorator nodes customise functionality of other nodes by wrapping around them, see InverterDecorator for example
/// </summary>
class DecoratorNode : 
	public BTNode
{
public:
	DecoratorNode(BTNode * WrappedNode, Blackboard bb);
	~DecoratorNode();
	BTNode * GetWrappedNode();

	/// <summary>
	/// Should reset the wrapped node
	/// </summary>
	virtual void Reset();

	//@Variables
protected:
	BTNode * WrappedNode;
};


/// <summary>
/// Inverter decorator simply inverts the result of success/failure of the wrapped node
/// </summary>
class InverterDecorator : 
	public DecoratorNode
{
public:
	InverterDecorator(BTNode * WrappedNode, Blackboard bb);

	virtual BTStatus Execute();
};

/// <summary>
/// Inherit this and override CheckStatus. If that returns true, then it will execute the WrappedNode otherwise it will return failure
/// </summary>
class ConditionalDecorator : 
	public DecoratorNode
{
public:
	ConditionalDecorator(BTNode * WrappedNode, Blackboard bb);

	virtual bool CheckStatus() = 0;

	virtual BTStatus Execute();

};

