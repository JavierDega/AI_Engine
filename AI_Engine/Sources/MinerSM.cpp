#include "pch.h"
#include "MinerSM.h"
#include "MinerStates.h"
#include "GameScene.h"

MinerSM::MinerSM()
{
}

MinerSM::MinerSM(Miner * character)
{
	m_character = character;
	//m_charState could be replaced by dynamic_casts?
	m_charState = 0;
	m_curState = new MiningForGold();
	m_lastExec = 0;
	m_execRate = 1.5f;
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
		m_curState->Execute(m_character);

		//@Log values
		m_character->m_text += L" Gold: " + to_wstring(m_character->m_gold) +
			L" Bank: " + to_wstring(m_character->m_bankedGold) +
			L" Tired: " + to_wstring(m_character->m_tiredness) +
			L" Thirsty: " + to_wstring(m_character->m_thirstiness) +
			L" Hungry: " + to_wstring(m_character->m_hunger);
	}

}

void MinerSM::HandleStateTransitions()
{	
	//Handles state transitions
	switch (m_charState)
	{
	case MINING_GOLD:
		//Transition conditions
		if (m_character->m_gold >= 10) {
			ChangeState(BANKING_GOLD);
		}
		else if (m_character->m_tiredness >= 10) {
			ChangeState(RESTING);
		}
		else if (m_character->m_thirstiness >= 10) {
			GameScene * gs = GameScene::GetInstance();
			//@Two cases
			//@Look for drinkStack
			if (gs->GetWife()->m_drinkStack > 0) ChangeState(HAVING_MEAL);
			else if (m_character->m_gold + m_character->m_bankedGold >= 5) {
				ChangeState(DRINKING);
			}
			else {
				//@Lose condition: Nowhere to drink from
			}
		}
		else if (m_character->m_hunger >= 10) {
			GameScene * gs = GameScene::GetInstance();
			if (gs->GetWife()->m_foodStack > 0) ChangeState(HAVING_MEAL);
			/*@@Could easily design a food shop very much like for DRINKING
			else if (m_character->m_gold + m_character->m_bankedGold >= 5) {
				ChangeState(DRINKING);
			}*/
			else {
				//@Lose condition: Nowhere to eat from
			}
		}
		break;
	case BANKING_GOLD:
		//@Transitions
		if (m_character->m_tiredness >= 10) {
			ChangeState(RESTING);
		}
		else if (m_character->m_thirstiness >= 10) {
			GameScene * gs = GameScene::GetInstance();
			//@Two cases
			//@Look for drinkStack
			if (gs->GetWife()->m_drinkStack > 0) ChangeState(HAVING_MEAL);
			else if (m_character->m_gold + m_character->m_bankedGold >= 5) {
				ChangeState(DRINKING);
			}
			else {
				//@Lose condition: Nowhere to drink from
			}
		}
		else if (m_character->m_hunger >= 10) {
			GameScene * gs = GameScene::GetInstance();
			if (gs->GetWife()->m_foodStack > 0) ChangeState(HAVING_MEAL);
			/*@@Could easily design a food shop very much like for DRINKING
			else if (m_character->m_gold + m_character->m_bankedGold >= 5) {
				ChangeState(DRINKING);
			}*/
			else {
				//@Lose condition: Nowhere to eat from
			}
		}
		else ChangeState(MINING_GOLD);
		break;
	case RESTING:
		//@Transitions only when woken up
		if (m_character->m_tiredness == 0) {
			//@Check hunger before thirst, since Having_Meal will decrease thirstiness too
		    if (m_character->m_thirstiness >= 10) {
				GameScene * gs = GameScene::GetInstance();
				//@Two cases
				//@Look for drinkStack
				if (gs->GetWife()->m_drinkStack > 0) ChangeState(HAVING_MEAL);
				else if (m_character->m_gold + m_character->m_bankedGold >= 5) {
					ChangeState(DRINKING);
				}
				else {
					//@Lose condition: Nowhere to drink from
				}
			}
			else if (m_character->m_hunger >= 10) {
				GameScene * gs = GameScene::GetInstance();
				if (gs->GetWife()->m_foodStack > 0) ChangeState(HAVING_MEAL);
				/*@@Could easily design a food shop very much like for DRINKING
				else if (m_character->m_gold + m_character->m_bankedGold >= 5) {
					ChangeState(DRINKING);
				}*/
				else {
					//@Lose condition: Nowhere to eat from
				}
			}
			else ChangeState(MINING_GOLD);
		}
		break;
	case DRINKING:
		if (m_character->m_hunger >= 10) {
			GameScene * gs = GameScene::GetInstance();
			if (gs->GetWife()->m_foodStack > 0) ChangeState(HAVING_MEAL);
			/*@@Could easily design a food shop very much like for DRINKING
			else if (m_character->m_gold + m_character->m_bankedGold >= 5) {
				ChangeState(DRINKING);
			}*/
			else {
				//@Lose condition: Nowhere to eat from
			}
		}
		ChangeState(MINING_GOLD);
		break;
	case HAVING_MEAL:
		//@Transitions
		ChangeState(MINING_GOLD);
		break;
	}
}

void MinerSM::ChangeState(int newState)
{
	//@Right place to use dictionaries/maps?:
	//Map(AnimIndex, StateClass)
	//Animated texture seems not to be the most exact
	m_character->m_startMoving = true;
	m_curState = NULL;
	if (newState == BANKING_GOLD){
		m_curState = new BankingGold();
	}
	if (newState == MINING_GOLD) {
		m_curState = new MiningForGold();
	}
	if (newState == RESTING) {
		m_curState = new Resting();
	}
	if (newState == DRINKING) {
		m_curState = new Drinking();
	}
	if (newState == HAVING_MEAL) {
		m_curState = new HavingMeal();
	}
	m_charState = newState;
	m_character->m_animator->Load(m_character->m_animatedTextures[newState].Get(), 2, 2);
}
