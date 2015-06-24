#include "stdafx.h"
#include <ctime>

#include "Map.h"
#include "Entity.h"
#include "EntitiesSystem.h"

#include "Components.h"
#include "Scripts.h"

#include "State.h"

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
	DetectEnemy* detectEnemy = static_cast<DetectEnemy*>(_entity->GetComponent(CompType::COMP_DETECTENEMY));
	AutoTankManager* autoTankManager = static_cast<AutoTankManager*>(_entity->GetComponent(CompType::COMP_AUTOTANKANAGER));

	if(healthControl->m_health <= 20.0f)
	{
		if(detectEnemy->m_encounterEnemy)
		{
			if(tankController->m_heuristicValue < 0.8 * static_cast<TankController*>(detectEnemy->m_encounterEnemy->GetComponent(CompType::COMP_TANKCONTROLLER))->m_heuristicValue)
				tankController->m_stateMachine.ChangeState(Fleeing::GetInstance());
		}
	}
	else if(detectEnemy->m_targetEnemy)
	{
		tankController->m_stateMachine.ChangeState(Fighting::GetInstance());
	}
	
	// Roaming
	tankController->m_direction = autoTankManager->GetNextRandomirection(tankController->m_direction);
	autoTankManager->Move(tankController->m_direction);
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
	
}

void Fighting::Execute(Entity* _entity)
{
	HealthControl* healthControl = static_cast<HealthControl*>(_entity->GetComponent(CompType::COMP_HEALTHCONTROL));
	TankController* tankController = static_cast<TankController*>(_entity->GetComponent(CompType::COMP_TANKCONTROLLER));
	DetectEnemy* detectEnemy = static_cast<DetectEnemy*>(_entity->GetComponent(CompType::COMP_DETECTENEMY));
	AutoTankManager* autoTankManager = static_cast<AutoTankManager*>(_entity->GetComponent(CompType::COMP_AUTOTANKANAGER));

	if(!detectEnemy->m_targetEnemy)
		tankController->m_stateMachine.ChangeState(Roaming::GetInstance());
	else if(healthControl->m_health <= 20.0f && healthControl->m_health <
		0.6 * static_cast<HealthControl*>(detectEnemy->m_targetEnemy->GetComponent(CompType::COMP_HEALTHCONTROL))->m_health)
		tankController->m_stateMachine.ChangeState(Fleeing::GetInstance());
	else if(_entity->m_transform->CalculateDistance(detectEnemy->m_targetEnemy->m_transform) /*> ...*/)
		tankController->m_stateMachine.ChangeState(Chasing::GetInstance());

	// Fighting
	// Rapid shooting
	// Move to enemy x/y position
	if(detectEnemy->m_targetEnemy)
	{
		tankController->m_direction = autoTankManager->GetShootDirection(detectEnemy->m_targetEnemy->m_transform->m_position);
		if(abs(detectEnemy->m_targetEnemy->m_transform->m_position.x - _entity->m_transform->m_position.x) <= 64
			|| abs(detectEnemy->m_targetEnemy->m_transform->m_position.y - _entity->m_transform->m_position.y) <= 64)
		{
			if(tankController->m_canShoot)
			{
				Factory::GetInstance()->CreateBullet(tankController->m_team, _entity->m_transform->m_position, tankController->m_direction,
					tankController->m_bullet, tankController->m_shootSpeed, tankController->m_shootRange, tankController->m_damage);

				tankController->m_canShoot = false;
				tankController->m_previousTime = clock();
			}
		}
	}
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
	DetectEnemy* detectEnemy = static_cast<DetectEnemy*>(_entity->GetComponent(CompType::COMP_DETECTENEMY));
	AutoTankManager* autoTankManager = static_cast<AutoTankManager*>(_entity->GetComponent(CompType::COMP_AUTOTANKANAGER));

	if(!detectEnemy->m_targetEnemy)
		tankController->m_stateMachine.ChangeState(Roaming::GetInstance());
	else if(_entity->m_transform->CalculateDistance(detectEnemy->m_targetEnemy->m_transform) /*< ...*/)
		tankController->m_stateMachine.ChangeState(Fighting::GetInstance());

	// Chasing
	// Move to enemy x/y position
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
	DetectEnemy* detectEnemy = static_cast<DetectEnemy*>(_entity->GetComponent(CompType::COMP_DETECTENEMY));
	AutoTankManager* autoTankManager = static_cast<AutoTankManager*>(_entity->GetComponent(CompType::COMP_AUTOTANKANAGER));

	if(healthControl->m_health <= 20.0f && healthControl->m_health <
		0.2 * static_cast<HealthControl*>(detectEnemy->m_targetEnemy->GetComponent(CompType::COMP_HEALTHCONTROL))->m_health)
		tankController->m_stateMachine.ChangeState(Fighting::GetInstance());

	// Fleeing
	// Get suitable direction and move
}

void Fleeing::Exit(Entity* _entity)
{

}
//////////////////////////////////////////////////////////