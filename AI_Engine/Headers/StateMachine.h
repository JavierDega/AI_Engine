#pragma once
#include "State.h"
#include <iostream>
using namespace std;

//Base class for our FSM characters. Made to be inheritted and its methods overriden.
template <class T>
class StateMachine
{
public:
	StateMachine()
	{
	}

	~StateMachine() 
	{
	}

	T * m_attachedCharacter;
	State<T> * m_curState;
	int m_charState;
	//Time (In secs) since last SM execution
	float m_lastExec;
	float m_execRate;

	virtual void Update(float) = 0;
	virtual void HandleStateTransitions() = 0;
	virtual void ChangeState(int newState) = 0;
};
