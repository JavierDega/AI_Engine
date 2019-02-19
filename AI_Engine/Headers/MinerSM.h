#pragma once
#include "Miner.h"

enum MinerStates {
	MINING_GOLD,
	BANKING_GOLD,
	RESTING,
	DRINKING,
	EATING,
	HAVING_MEAL
};
class MinerSM :
	public StateMachine<Miner>
{
public:
	MinerSM(Miner * character);
	~MinerSM();
	void Update(float elapsedTime)override;
	void HandleStateTransitions()override;
	void ChangeState(int newState)override;

};

