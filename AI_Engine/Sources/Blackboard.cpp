#include "pch.h"
#include "..\Headers\Blackboard.h"

using namespace DirectX;
using namespace SimpleMath;

Blackboard::Blackboard( Vector2 desiredLocation, bool pickPocket, bool stealFood)
	: m_desiredLocation(desiredLocation), m_pickPocket(pickPocket), m_stealFood(stealFood), m_speed(25)
{
}


Blackboard::~Blackboard()
{
}

void Blackboard::Update()
{
}
