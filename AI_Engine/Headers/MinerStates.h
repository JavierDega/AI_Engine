#pragma once
#include "State.h"
#include "Miner.h"
//Mining for gold state
class MiningForGold : 
	public State<Miner>
{
	void Execute(Miner * miner);
};

class BankingGold :
	public State<Miner>
{
public:

	void Execute(Miner * miner);
};

class Resting :
	public State<Miner>
{
public:

	void Execute(Miner * miner);
};

class Drinking :
	public State<Miner>
{
public:

	void Execute(Miner * miner);
};
//@Takes from food stack to refresh Thirstiness, and hunger.
class HavingMeal :
	public State<Miner>
{
public:

	void Execute(Miner * miner);

};

class Eating :
	public State<Miner>
{
public:
	void Execute(Miner * miner);
};

