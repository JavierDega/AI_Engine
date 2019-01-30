#pragma once


//@Holds all data the BTNodes need for behaviour
class Blackboard {
public:
	//Conditional decorators: (@To be replaced/complemented by desirability?)
	//Higher level to lower level
	Blackboard();
	~Blackboard();

	// Update is called once per frame
	virtual void Update();

};

