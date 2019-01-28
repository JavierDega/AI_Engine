#include "pch.h"
#include "..\Headers\WifeSM.h"
#include "WifeStates.h"

using namespace std;

WifeSM::WifeSM(Wife * character)
{
	m_character = character;
	//m_charState could be replaced by dynamic_casts?
	m_charState = 0;
	m_curState = new Cooking();
	m_lastExec = 0;
	m_execRate = 0.5f;
}


WifeSM::~WifeSM()
{
}

void WifeSM::Update(float elapsedTime)
{
	m_lastExec += elapsedTime;
	if (m_lastExec >= m_execRate) {
		m_lastExec = 0;

		HandleStateTransitions();
		//Execute state
		m_curState->Execute(m_character);

		//@Log values
		m_character->m_text += L" Cook state: " + to_wstring(m_character->m_cookState) + L"/10"
			+ L" Food stack: " + to_wstring(m_character->m_foodStack)
			+ L" Drink stack: " + to_wstring(m_character->m_drinkStack);
	}

}

void WifeSM::HandleStateTransitions()
{
	//Handles state transitions
	switch (m_charState)
	{
	case COOKING:
		//Transition conditions
		if (m_character->m_cookState >= 10) {
			ChangeState(DELIVERING_FOOD);
		}
		break;
	case DELIVERING_FOOD:
		//@Transitions
		ChangeState(COOKING);
		break;
	}
}

void WifeSM::ChangeState(int newState)
{
	//@Right place to use dictionaries/maps?:
	//Map(AnimIndex, StateClass)
	//Animated texture seems not to be the most exact
	m_character->m_startMoving = true;
	m_curState = NULL;
	if (newState == COOKING){
		m_curState = new Cooking();
	}
	if (newState == DELIVERING_FOOD) {
		m_curState = new DeliveringFood();
	}
	m_charState = newState;
	m_character->m_animator->Load(m_character->m_animatedTextures[newState + 1].Get(), 2, 2);
}
