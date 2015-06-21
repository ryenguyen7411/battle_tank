#include "stdafx.h"
#include "State.h"
#include "Entity.h"
#include "Components.h"
#include "Scripts.h"

#include "TankAI.h"

//////////////////////////////////////////////////////////
// ROAMING
Roaming::Roaming()
{

}

Roaming::~Roaming()
{
	
}

void Roaming::Enter(Entity* _entity)
{
	// Calculate/setup variables of strength
}

void Roaming::Execute(Entity* _entity)
{
	//if(...)
		static_cast<TankController*>(_entity->GetComponent(CompType::COMP_TANKCONTROLLER))->m_stateMachine.ChangeState(new Fighting());
}

void Roaming::Exit(Entity* _entity)
{
	// Reset variable
}
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
// FIGHTING
Fighting::Fighting()
{

}

Fighting::~Fighting()
{
	
}

void Fighting::Enter(Entity* _entity)
{

}

void Fighting::Execute(Entity* _entity)
{

}

void Fighting::Exit(Entity* _entity)
{

}
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
// CHASING
Chasing::Chasing()
{

}

Chasing::~Chasing()
{
	
}

void Chasing::Enter(Entity* _entity)
{

}

void Chasing::Execute(Entity* _entity)
{

}

void Chasing::Exit(Entity* _entity)
{

}
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
// FLEEING
Fleeing::Fleeing()
{

}

Fleeing::~Fleeing()
{
	
}

void Fleeing::Enter(Entity* _entity)
{

}

void Fleeing::Execute(Entity* _entity)
{

}

void Fleeing::Exit(Entity* _entity)
{

}
//////////////////////////////////////////////////////////