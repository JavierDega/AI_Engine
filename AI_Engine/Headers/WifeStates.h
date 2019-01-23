#pragma once
#include "State.h"
#include "Wife.h"
//Mining for gold state
class Cooking : 
	public State<Wife>
{
	void Execute(Wife * miner);
};

class DeliveringFood :
	public State<Wife>
{
public:

	void Execute(Wife * miner);
};

