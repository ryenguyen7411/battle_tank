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
		if(detectEnemy->m_targetEnemy && autoTankManager->IsInShootRange(detectEnemy->m_targetEnemy->m_transform->m_position))
		{
			if(tankController->m_heuristicValue < 0.5f * static_cast<TankController*>(detectEnemy->m_encounterEnemy->GetComponent(CompType::COMP_TANKCONTROLLER))->m_heuristicValue)
				tankController->m_stateMachine.ChangeState(Fleeing::GetInstance());
		}
	}
	else if(detectEnemy->m_targetEnemy && autoTankManager->IsInShootRange(detectEnemy->m_targetEnemy->m_transform->m_position))
	{
 		tankController->m_stateMachine.ChangeState(Fighting::GetInstance());
	}
	
	// Roaming
	else
	{
		autoTankManager->m_virtualKey = autoTankManager->GetNextRandomKey();
		autoTankManager->Move();
	}
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
	else if(healthControl->m_health <= 20.0f && 
		healthControl->m_health < 0.5 * static_cast<HealthControl*>(detectEnemy->m_targetEnemy->GetComponent(CompType::COMP_HEALTHCONTROL))->m_health &&
		healthControl->m_health >= 0.25 * static_cast<HealthControl*>(detectEnemy->m_targetEnemy->GetComponent(CompType::COMP_HEALTHCONTROL))->m_health)
	{
		if(autoTankManager->IsInShootRange(detectEnemy->m_targetEnemy->m_transform->m_position))
			tankController->m_stateMachine.ChangeState(Fleeing::GetInstance());
	}
	else if(!autoTankManager->IsInShootRange(detectEnemy->m_targetEnemy->m_transform->m_position))
		tankController->m_stateMachine.ChangeState(Chasing::GetInstance());

	// Fighting
	else
	{
		tankController->m_direction = autoTankManager->GetShootDirection(detectEnemy->m_targetEnemy->m_transform->m_position);

		_entity->m_animator->m_currentFrame = (int)tankController->m_direction;
		_entity->m_renderer->m_sprite = _entity->m_animator->m_frameList[_entity->m_animator->m_currentFrame];

		if(autoTankManager->IsInShootRange(detectEnemy->m_targetEnemy->m_transform->m_position))
		{
			if(tankController->m_canShoot && rand() % 100 < 10)
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
	else if(autoTankManager->IsInShootRange(detectEnemy->m_targetEnemy->m_transform->m_position))
		tankController->m_stateMachine.ChangeState(Fighting::GetInstance());

	// Chasing
	else
	{
		autoTankManager->SetKeyForDirection(autoTankManager->GetDirectionToEnemy(detectEnemy->m_targetEnemy->m_transform->m_position));
		autoTankManager->Move();
	}
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

	if(detectEnemy->m_targetEnemy && healthControl->m_health <= 20.0f && healthControl->m_health <
		0.25 * static_cast<HealthControl*>(detectEnemy->m_targetEnemy->GetComponent(CompType::COMP_HEALTHCONTROL))->m_health)
		tankController->m_stateMachine.ChangeState(Fighting::GetInstance());

	// Fleeing
	else if(detectEnemy->m_targetEnemy)
	{
		autoTankManager->SetKeyForDirection(autoTankManager->GetDirectionAwayFromEnemy(detectEnemy->m_targetEnemy->m_transform->m_position));
		autoTankManager->Move();
	}
}

void Fleeing::Exit(Entity* _entity)
{

}
//////////////////////////////////////////////////////////