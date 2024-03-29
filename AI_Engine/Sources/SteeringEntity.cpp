#include "pch.h"
#include "SteeringEntity.h"
#include "GameScene.h"
#include "TempEntity.h"

#define NEIGHBOURING_THRESHOLD 300
#define DIST_THRESHOLD 100
#define BOUNDXMIN 360.f
#define BOUNDXMAX 1560.f
using namespace DirectX;
using namespace SimpleMath;
using namespace std;

SteeringEntity::SteeringEntity(Vector2 screenPos, float maxSpeed, SteeringType type, float layerDepth)
	: GameEntity(screenPos, layerDepth), m_maxSpeed(maxSpeed), m_type(type)
{
	m_waypointIndex = 0;
	m_seekVector = Vector2::Zero;
	if ((int)type & (int)SteeringType::PLAYER_CAR) m_seekVector = screenPos;//@Quick fix
}

SteeringEntity::~SteeringEntity()
{
}

void SteeringEntity::Initialize(ID3D11Device1 * device, const wchar_t * fileName)
{
	GameEntity::Initialize(device, fileName);
}

void SteeringEntity::Render(DirectX::SpriteBatch * spriteBatch)
{
	float angle = atan2f(m_side.y, m_side.x);
	angle = (m_velocity.LengthSquared() < 0.1f) ? 0.f : (min(.75f, max(angle, -.75f)));
	spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Colors::White, angle , m_origin, Vector2(1, 1), SpriteEffects_None, m_layerDepth);
}

void SteeringEntity::Update(float elapsedTime) {
	//@Clamp movement
	m_screenPos.x = min(BOUNDXMAX, max(m_screenPos.x, BOUNDXMIN));
	//@First update
	if (m_type == SteeringType::ENEMY_CAR && m_seekVector == Vector2::Zero) {
		m_waypoints.clear();
		m_waypointIndex = 0;
		GameScene * gs = GameScene::GetInstance();
		m_waypoints = gs->m_graph.CalculateAStar(m_screenPos, gs->GetPlayerCar()->m_screenPos);
		m_seekVector = m_waypoints[m_waypointIndex];
	}
	m_steeringForce = Vector2::Zero;
	Seek(m_seekVector);
	Arrive(m_seekVector);
	if (m_type == SteeringType::ENEMY_CAR)Flock();//@SEPARATION AND ALIGNMENT

	//@Steering behaviour
	Vector2 acceleration = m_steeringForce / 1;
	m_velocity += acceleration;
	if (m_velocity.LengthSquared() > m_maxSpeed*m_maxSpeed) {
		m_velocity = m_maxSpeed * m_velocity / m_velocity.Length();
	}
	m_screenPos += m_velocity * elapsedTime;
	if (m_velocity == Vector2::Zero) {
		m_heading = Vector2(-1, 0);
	}
	else m_heading = m_velocity / m_velocity.Length();
	m_side = Vector2(-m_heading.y, m_heading.x);

	GameScene * gs = GameScene::GetInstance();
	for (int i = 0; i < gs->m_entities.size(); i++) {
		//@Collide against every other entity
		SteeringEntity * otherCar = dynamic_cast<SteeringEntity*>(gs->m_entities[i]);
		if (otherCar) {
			if (otherCar != this) {
				//@We collided with another car, flag for deletion
				if ((m_screenPos - otherCar->m_screenPos).Length() <= DIST_THRESHOLD) {
					m_isDeleted = true;
					otherCar->m_isDeleted = true;
					//@Spawn two debris
					TempEntity * carDebris = new TempEntity(m_screenPos, Vector2(0.f, 50.f));
					carDebris->Initialize(gs->m_device, L"Textures/carCrashed.dds");
					gs->InsertEntity(carDebris);
					TempEntity * carDebris2 = new TempEntity(otherCar->m_screenPos, Vector2( 0.f, 50.f));
					carDebris2->Initialize(gs->m_device, L"Textures/carCrashed.dds");
					gs->InsertEntity(carDebris2);
					if (m_type == SteeringType::PLAYER_CAR || otherCar->m_type == SteeringType::PLAYER_CAR) {
						gs->CityChaseLost();
					}
				}
			}
		}
	}
	
}

//@Steering
void SteeringEntity::Seek(DirectX::SimpleMath::Vector2 position)
{
	Vector2 desiredVelocity = position - m_screenPos;
	desiredVelocity.Normalize();
	desiredVelocity *= m_maxSpeed;

	m_steeringForce += desiredVelocity - m_velocity;
}

void SteeringEntity::Arrive(DirectX::SimpleMath::Vector2 position)
{
	Vector2 toTarget = position - m_screenPos;
	float dist = toTarget.Length();
	if (dist < DIST_THRESHOLD) {//@Some threshold
		Vector2 desiredVelocity = toTarget / toTarget.Length() *m_maxSpeed*(dist / DIST_THRESHOLD);
		m_steeringForce = desiredVelocity - m_velocity;
		if (m_type == SteeringType::ENEMY_CAR) {
			//@M_ENEMY CAR
			//@When we arrive, we get the next waypoint or set of waypoints to the player
			//(If we arrived, presumably the player is somewhere else)
			m_waypointIndex++;
			if (m_waypointIndex == m_waypoints.size()) {
				m_waypoints.clear();
				m_waypointIndex = 0;
				GameScene * gs = GameScene::GetInstance();
				m_waypoints = gs->m_graph.CalculateAStar(m_screenPos, gs->GetPlayerCar()->m_screenPos);
				assert(m_waypoints.size() != 0);
			}
			m_seekVector = m_waypoints[m_waypointIndex];
		}
	}
}

void SteeringEntity::Flock()
{
	//@Get list of all other enemy cars
	GameScene * gs = GameScene::GetInstance();
	vector<SteeringEntity *> neighbours;

	for (int i = 0; i < gs->m_entities.size(); i++) {
		SteeringEntity * enemyCar = dynamic_cast<SteeringEntity *>(gs->m_entities[i]);
		if (enemyCar && enemyCar->m_type == SteeringType::ENEMY_CAR && this != enemyCar) {
			//@Distance check for neighbouring
			if ((m_screenPos - enemyCar->m_screenPos).Length() < NEIGHBOURING_THRESHOLD) {
				neighbours.push_back(enemyCar);
			}
		}
	}
	//@Separation + alignment
	Vector2 averageHeading = Vector2::Zero;
	for (SteeringEntity * neighbour : neighbours) {
		averageHeading += neighbour->m_heading;
		Vector2 toOurAgent = m_screenPos - neighbour->m_screenPos;
		float distance = toOurAgent.Length();
		toOurAgent /= distance;
		m_steeringForce += toOurAgent;
	}
	//@Alignment
	if (neighbours.size() > 0) {
		averageHeading /= neighbours.size();
		m_steeringForce += averageHeading - m_heading;
	}
}
