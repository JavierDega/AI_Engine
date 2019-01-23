#pragma once
#include "Wife.h"

enum WifeStates {
	COOKING,
	DELIVERING_FOOD
};
class WifeSM :
	public StateMachine<Wife>
{
public:
	WifeSM();
	WifeSM(Wife * character);
	~WifeSM();

	void Update(float elapsedTime)override;
	void HandleStateTransitions()override;
	void ChangeState(int newState)override;

};


