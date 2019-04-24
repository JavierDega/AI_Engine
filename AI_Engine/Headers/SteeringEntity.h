#pragma once
#include "GameEntity.h"

enum class SteeringType {
	PLAYER_CAR,
	ENEMY_CAR
};
class SteeringEntity :
	public GameEntity
{
public:
	SteeringEntity(DirectX::SimpleMath::Vector2 screenPos = DirectX::SimpleMath::Vector2::Zero, float maxSpeed = 100.0f, SteeringType type = SteeringType::PLAYER_CAR,
		float layerDepth = 0.6f);
	virtual ~SteeringEntity();
	//Init
	virtual void Initialize(ID3D11Device1 * device, const wchar_t* fileName = L"Textures/playercar.dds");
	virtual void Render(DirectX::SpriteBatch * spriteBatch);
	virtual void Update(float elapsedTime);
	//@Utility
	void Seek(DirectX::SimpleMath::Vector2 position);
	void Arrive(DirectX::SimpleMath::Vector2 position);

	//@Variables
	SteeringType m_type;
	//@Optional (Enemy cars)
	std::vector<DirectX::SimpleMath::Vector2> m_waypoints;
	unsigned int m_waypointIndex;
	//@Position, velocity, heading, side, mass, max speed, max force, max turn rate
	DirectX::SimpleMath::Vector2 m_velocity;//@Generate rotation based on it
	DirectX::SimpleMath::Vector2 m_seekVector;//@Seek vector
	DirectX::SimpleMath::Vector2 m_steeringForce;
	DirectX::SimpleMath::Vector2 m_heading, m_side;//@Heading and side
	float m_maxSpeed;

};

