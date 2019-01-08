#pragma once
#include "Miner.h"

enum MinerStates {
	MINING_GOLD,
	BANKING_GOLD,
	RESTING,
	DRINKING,
	HAVING_MEAL
};
class MinerSM :
	public StateMachine<Miner>
{
public:
	MinerSM();
	MinerSM(Miner * character);
	~MinerSM();
	void Update(float elapsedTime)override;
	void HandleStateTransitions()override;
	void ChangeState(int newState)override;

};

