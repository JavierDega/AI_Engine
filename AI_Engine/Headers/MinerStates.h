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

class HavingMeal :
	public State<Miner>
{
public:

	void Execute(Miner * miner);
};

