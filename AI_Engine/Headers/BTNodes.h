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
	BTNode(Blackboard bb)
	{
		this->bb = bb;
	}

	virtual BTStatus Execute() = 0;

	/// <summary>
	/// Reset should be overidden in child classes as and when necessary
	/// It should be called when a node is abruptly aborted before it can finish with a success or failure
	/// i.e the node was still RUNNING when it is aborted you need to gracefully handle it to avoid unintended bugs
	/// See DelayNode, CompositeNode and DecoratorNode for examples
	/// </summary>
	virtual void Reset()
	{

	}

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
	CompositeNode(Blackboard bb) : BTNode(bb)
	{
	}
	virtual void AddChild(BTNode * child)
	{
		//Add child BTNode to the list
		children.push_back(child);
	}

	/// <summary>
	/// When a composite node is reset it set the child index back to 0, and it should propogate the reset down to all its children
	/// </summary>
	virtual void Reset()
	{
		CurrentChildIndex = 0;
		//Reset every child
		for (int j = 0; j < children.size(); j++)
		{
			children[j]->Reset();
		}

	}

protected:
	int CurrentChildIndex = 0;
	std::vector< BTNode * > children;
};

/// <summary>
/// Selectors execute their children in order until a child succeeds, at which point it stops execution
/// If a child returns RUNNING, then it will need to stop execution but resume from the same point the next time it executes
/// </summary>
class Selector : CompositeNode
{
	Selector( Blackboard bb ) : CompositeNode(bb)
	{
		//just needs to call Composite's constructor (base(bb) part)
	}

	virtual BTStatus Execute()
	{
		//Use CompositeNode::CurrentChildIndex to know which Child to execute (:O)
		BTStatus rv = BTStatus::FAILURE;
		//If Action Node succeeds , we stop execution, and reset
		//If action node is running, we stop execution (break; out of for loop) keeping the currentIndex, so we continue from the next frame
		//If action node fails, we up the index and continue execution
		for (int i = CurrentChildIndex; i < children.size(); i++)
		{
			rv = children[i]->Execute();
			if (rv == BTStatus::SUCCESS)
			{
				Reset();
				break;
			}
			else if (rv == BTStatus::RUNNING)
			{
				break;
			}
			else if (rv == BTStatus::FAILURE)
			{
				//Track index
				CurrentChildIndex++;
			}
		}

		//We're done with the sequence (In this case, got all nodes in children[] to eventually return FAILURE), so reset it for the next time we call it
		if (CurrentChildIndex == children.size())
		{
			Reset();
		}
		return rv;
	}
};

/// <summary>
/// Sequences execute their children in order until a child fails, at which point it stops execution
/// If a child returns RUNNING, then it will need to stop execution but resume from the same point the next time it executes
/// </summary>
class Sequence : 
	public CompositeNode
{
public:
	Sequence( Blackboard bb ) : CompositeNode(bb)
	{
		//Same as selector, just needs to call Composite node's constructor, since this class holds no extra values
	}
	virtual BTStatus Execute()
	{
		//Use CompositeNode::CurrentChildIndex to know which Child to execute (:O)
		BTStatus rv = BTStatus::FAILURE;
		//If Action Node succeeds , we up the index and execute further.
		//If action node is running, we stop execution (break; out of for loop) keeping the currentIndex, so we continue from the next frame
		//If action node fails, we stop execution , and reset currentChildIndex = 0;
		for (int i = CurrentChildIndex; i < children.size(); i++) {
			rv = children[i]->Execute();
			if (rv == BTStatus::SUCCESS)
			{
				//Track index
				CurrentChildIndex++;
			}
			else if (rv == BTStatus::RUNNING)
			{
				break;
			}
			else if (rv == BTStatus::FAILURE) {
				Reset();
				break;
			}
		}

		//We're done with the sequence (Got all nodes in children[] to eventually succeed, reset it for the next time we call it
		if (CurrentChildIndex == children.size()) {
			Reset();
		}
		return rv;
	}
};

/// <summary>
/// Decorator nodes customise functionality of other nodes by wrapping around them, see InverterDecorator for example
/// </summary>
class DecoratorNode : 
	public BTNode
{
public:
	DecoratorNode(BTNode * WrappedNode, Blackboard bb) : BTNode(bb)
	{
		this->WrappedNode = WrappedNode;
	}

	BTNode * GetWrappedNode()
	{
		return WrappedNode;
	}

	/// <summary>
	/// Should reset the wrapped node
	/// </summary>
	virtual void Reset()
	{
		WrappedNode->Reset();
	}

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
	InverterDecorator(BTNode * WrappedNode, Blackboard bb) : DecoratorNode(WrappedNode, bb)
	{
		//No extra values, just calls constructor on parent
	}

	virtual BTStatus Execute()
	{
		BTStatus rv = WrappedNode->Execute();

		if (rv == BTStatus::FAILURE)
		{
			rv = BTStatus::SUCCESS;
		}
		else if (rv == BTStatus::SUCCESS)
		{
			rv = BTStatus::FAILURE;
		}

		return rv;
	}
};

/// <summary>
/// Inherit this and override CheckStatus. If that returns true, then it will execute the WrappedNode otherwise it will return failure
/// </summary>
class ConditionalDecorator : 
	public DecoratorNode
{
public:
	ConditionalDecorator(BTNode * WrappedNode, Blackboard bb) : DecoratorNode(WrappedNode, bb)
	{
	}

	virtual bool CheckStatus() = 0;
	virtual BTStatus Execute()
	{
		BTStatus rv = BTStatus::FAILURE;

		if (CheckStatus())
		{
			rv = WrappedNode->Execute();
		}
		else
		{
			rv = BTStatus::FAILURE;
		}

		return rv;
	}


};

