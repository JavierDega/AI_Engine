#include "pch.h"
#include "..\Headers\BTNodes.h"


BTNode::BTNode(Blackboard * bb)
{
	this->bb = bb;
}

void BTNode::Reset()
{
}

CompositeNode::CompositeNode(Blackboard * bb)
	: BTNode(bb), CurrentChildIndex(0)
{
}

CompositeNode::~CompositeNode()
{
	while (!children.empty()) {
		BTNode * curNode = children.back();
		delete curNode;
		children.pop_back();
	}
}

void CompositeNode::AddChild(BTNode * child)
{
	//Add child BTNode to the list
	children.push_back(child);
}

void CompositeNode::Reset()
{
	CurrentChildIndex = 0;
	//Reset every child
	for (int j = 0; j < children.size(); j++)
	{
		children[j]->Reset();
	}
}

Selector::Selector( Blackboard * bb ) 
	: CompositeNode(bb)
{
	//just needs to call Composite's constructor (base(bb) part)
}

BTStatus Selector::Execute()
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

Sequence::Sequence(Blackboard * bb) 
	: CompositeNode(bb)
{
	//Same as selector, just needs to call Composite node's constructor, since this class holds no extra values
}

BTStatus Sequence::Execute()
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

DecoratorNode::DecoratorNode(BTNode * WrappedNode, Blackboard * bb) 
	: BTNode(bb)
{
	this->WrappedNode = WrappedNode;
}

DecoratorNode::~DecoratorNode()
{
	delete WrappedNode;
	WrappedNode = nullptr;
}

BTNode * DecoratorNode::GetWrappedNode()
{
	return WrappedNode;
}

void DecoratorNode::Reset()
{
	WrappedNode->Reset();
}

InverterDecorator::InverterDecorator(BTNode * WrappedNode, Blackboard * bb) 
	: DecoratorNode(WrappedNode, bb)
{
	//No extra values, just calls constructor on parent
}

BTStatus InverterDecorator::Execute()
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

ConditionalDecorator::ConditionalDecorator(BTNode * WrappedNode, Blackboard * bb) 
	: DecoratorNode(WrappedNode, bb)
{
}

BTStatus ConditionalDecorator::Execute()
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

