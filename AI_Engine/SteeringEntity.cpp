#include "pch.h"
#include "SteeringEntity.h"

using namespace DirectX;
using namespace SimpleMath;

SteeringEntity::SteeringEntity(Vector2 screenPos, float layerDepth)
	: GameEntity(screenPos, layerDepth)
{
}


SteeringEntity::~SteeringEntity()
{
}

void SteeringEntity::Initialize(ID3D11Device1 * device, const wchar_t * fileName)
{
	GameEntity::Initialize(device, fileName);
}