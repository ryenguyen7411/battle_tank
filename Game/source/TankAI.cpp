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

}

void Roaming::Execute(Entity* _entity)
{
	HealthControl* healthControl = static_cast<HealthControl*>(_entity->GetComponent(CompType::COMP_HEALTHCONTROL));
	TankController* tankController = static_cast<TankController*>(_entity->GetComponent(CompType::COMP_TANKCONTROLLER));
	FindEnemy* findEnemy = static_cast<FindEnemy*>(_entity->GetComponent(CompType::COMP_FINDENEMY));

	if(healthControl->m_health <= 20.0f)
	{
		if(findEnemy->m_encounterEnemy)
		{
			if(tankController->m_heuristicValue < 0.8 * static_cast<TankController*>(findEnemy->m_encounterEnemy->GetComponent(CompType::COMP_TANKCONTROLLER))->m_heuristicValue)
				tankController->m_stateMachine.ChangeState(Fleeing::GetInstance());
		}
	}
	else if(findEnemy->m_targetEnemy)
	{
		tankController->m_stateMachine.ChangeState(Fighting::GetInstance());
	}
	
	// Roaming
}

void Roaming::Exit(Entity* _entity)
{
	
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
	HealthControl* healthControl = static_cast<HealthControl*>(_entity->GetComponent(CompType::COMP_HEALTHCONTROL));
	TankController* tankController = static_cast<TankController*>(_entity->GetComponent(CompType::COMP_TANKCONTROLLER));
	FindEnemy* findEnemy = static_cast<FindEnemy*>(_entity->GetComponent(CompType::COMP_FINDENEMY));

	if(!findEnemy->m_targetEnemy)
		tankController->m_stateMachine.ChangeState(Roaming::GetInstance());
	else if(healthControl->m_health <= 20.0f && healthControl->m_health <
		0.6 * static_cast<HealthControl*>(findEnemy->m_targetEnemy->GetComponent(CompType::COMP_HEALTHCONTROL))->m_health)
		tankController->m_stateMachine.ChangeState(Fleeing::GetInstance());
	else if(_entity->m_transform->CalculateDistance(findEnemy->m_targetEnemy->m_transform) /*> ...*/)
		tankController->m_stateMachine.ChangeState(Chasing::GetInstance());

	// Fighting
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
	HealthControl* healthControl = static_cast<HealthControl*>(_entity->GetComponent(CompType::COMP_HEALTHCONTROL));
	TankController* tankController = static_cast<TankController*>(_entity->GetComponent(CompType::COMP_TANKCONTROLLER));
	FindEnemy* findEnemy = static_cast<FindEnemy*>(_entity->GetComponent(CompType::COMP_FINDENEMY));

	if(!findEnemy->m_targetEnemy)
		tankController->m_stateMachine.ChangeState(Roaming::GetInstance());
	else if(_entity->m_transform->CalculateDistance(findEnemy->m_targetEnemy->m_transform) /*< ...*/)
		tankController->m_stateMachine.ChangeState(Fighting::GetInstance());

	// Chasing
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
	HealthControl* healthControl = static_cast<HealthControl*>(_entity->GetComponent(CompType::COMP_HEALTHCONTROL));
	TankController* tankController = static_cast<TankController*>(_entity->GetComponent(CompType::COMP_TANKCONTROLLER));
	FindEnemy* findEnemy = static_cast<FindEnemy*>(_entity->GetComponent(CompType::COMP_FINDENEMY));

	if(healthControl->m_health <= 20.0f && healthControl->m_health <
		0.2 * static_cast<HealthControl*>(findEnemy->m_targetEnemy->GetComponent(CompType::COMP_HEALTHCONTROL))->m_health)
		tankController->m_stateMachine.ChangeState(Fighting::GetInstance());

	// Fleeing
}

void Fleeing::Exit(Entity* _entity)
{

}
//////////////////////////////////////////////////////////