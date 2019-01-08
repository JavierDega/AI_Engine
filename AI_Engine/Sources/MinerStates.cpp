#include "pch.h"
#include "..\Headers\MinerStates.h"

void MiningForGold::Execute(Miner * miner)
{
	miner->m_gold++;
}

void BankingGold::Execute(Miner * miner)
{
	miner->m_bankedGold += miner->m_gold;
	miner->m_gold = 0;
}

void Resting::Execute(Miner * miner)
{
}

void Drinking::Execute(Miner * miner)
{
}

void HavingMeal::Execute(Miner * miner)
{
}

