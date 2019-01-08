#include "pch.h"
#include "MinerSM.h"

#include "MinerStates.h"

MinerSM::MinerSM()
{
	//@Wont set attached character
	//m_charState could be replaced by dynamic_casts?
	m_charState = 0;
	m_curState = new MiningForGold();
	m_lastExec = 0;
	m_execRate = 1.0f;
}

MinerSM::MinerSM(Miner * character)
{
	m_attachedCharacter = character;
	//m_charState could be replaced by dynamic_casts?
	m_charState = 0;
	m_curState = new MiningForGold();
	m_lastExec = 0;
	m_execRate = 1.0f;
}


MinerSM::~MinerSM()
{
}

void MinerSM::Update(float elapsedTime)
{
	m_lastExec += elapsedTime;
	if (m_lastExec >= m_execRate) {
		m_lastExec = 0;
		HandleStateTransitions();
		//Execute state
		m_curState->Execute(m_attachedCharacter);
	}

}

void MinerSM::HandleStateTransitions()
{
	//Handles state transitions
	switch (m_charState)
	{
	case MINING_GOLD:
		//Transition conditions
		if (m_attachedCharacter->m_gold >= 10) {
			ChangeState(BANKING_GOLD);
		}
		break;
	case BANKING_GOLD:
		//Back to mining instantly?
		ChangeState(MINING_GOLD);
		break;
	case RESTING:
		break;
	case DRINKING:
		break;
	case HAVING_MEAL:
		break;
	}
}

void MinerSM::ChangeState(int newState)
{
	//Right place to use dictionaries/maps?:
	//Map(AnimIndex, StateClass)
	//Animated texture seems not to be the most exact
	m_attachedCharacter->m_startMoving = true;
	m_curState = NULL;
	if (newState == BANKING_GOLD){
		m_curState = new BankingGold();
		m_charState = BANKING_GOLD;
		m_attachedCharacter->m_animator->Load(m_attachedCharacter->m_animatedTextures[BANKING_GOLD].Get(), 2, 2);
	}
	if (newState == MINING_GOLD) {
		m_curState = new MiningForGold();
		m_charState = MINING_GOLD;
		m_attachedCharacter->m_animator->Load(m_attachedCharacter->m_animatedTextures[MINING_GOLD].Get(), 2, 2);
	}
	
}
