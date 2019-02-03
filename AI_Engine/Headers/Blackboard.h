#pragma once


//@Holds all data the BTNodes need for behaviour
class Blackboard {
public:
	//Conditional decorators: (@To be replaced/complemented by desirability?)
	//Higher level to lower level
	Blackboard( bool pickPocket = false, bool stealFood = false );
	~Blackboard();

	// Update is called once per frame
	virtual void Update();

	//Variables data
	//m_desirabilities?

	bool m_pickPocket;
	bool m_stealFood;
	DirectX::SimpleMath::Vector2 m_desiredLocation;
	float m_speed;
};

