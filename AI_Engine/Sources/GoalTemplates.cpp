#include "pch.h"
#include "..\Headers\GoalTemplates.h"

void CompositeGoal::Activate()
{
	IsActive = true;
}

void CompositeGoal::AddSubgoal(Goals * g)
{
	subgoals.push(g);
	g->Activate();
}

int CompositeGoal::Process()
{
	int status = subgoals.top()->Process();

	if (status == -1) // if status is -1, it means we should terminate this goal
	{
		Goals * g = subgoals.top();
		subgoals.pop();
		g->Terminate();
		delete g;//@Terminate call might be redundant
	}

	return status;
}

void CompositeGoal::Terminate()
{
	IsActive = false;
}

void AtomicGoal::Activate()
{
	IsActive = true;
}

int AtomicGoal::Process()
{
	int status = 1;

	//Perform custom logic here

	return status;
}

void AtomicGoal::Terminate()
{
	IsActive = false;
}

int BuySword::Process()
{
	int status = CompositeGoal::Process();

	//Here we could process some more custom logic to do with buying a sword
	if (NotEnoughGold())
	{
		subgoals.push(new GetGold());
	}

	return status;
}

bool BuySword::NotEnoughGold()
{
	//You should have a check here to actually check for gold, we're doing this to simplify things
	return true;
}

int GetGold::Process()
{
	int status = AtomicGoal::Process();

	//Perform custom getgold logic here, once we've got gold we set status to -1

	return status;
}
