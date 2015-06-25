#include "stdafx.h"
#include <ctime>

#include "Factory.h"
#include "Map.h"
#include "Entity.h"
#include "EntitiesSystem.h"

#include "State.h"
#include "TankAI.h"

#include "Scripts.h"

#pragma region TankController
TankController::TankController(Tank _tankType)
{
	m_type = CompType::COMP_TANKCONTROLLER;

	m_tank = _tankType;
	m_bullet = Bullet::BULLET_NORMAL;

	m_timer = 0;

	switch(m_tank)
	{
		case Tank::TANK_NORMAL:
			m_speed = 5.0f;
			m_damage = 20.0f;

			m_shootSpeed = 10.0f;
			m_shootRange = 400.0f;
			m_shootPerSec = 2;
			break;
		case Tank::TANK_DEFENSE:
			m_speed = 2.0f;
			m_damage = 80.0f;

			m_shootSpeed = 10.0f;
			m_shootRange = 200.0f;
			m_shootPerSec = 1;
			break;
		case Tank::TANK_BOLT:
			m_speed = 8.0f;
			m_damage = 20.0f;

			m_shootSpeed = 20.0f;
			m_shootRange = 300.0f;
			m_shootPerSec = 4;
			break;
	}

	m_previousTime = clock();
	m_canShoot = true;
	m_lockDirection = Direction::DIR_NONE;
}

TankController::~TankController()
{

}

void TankController::Release()
{

}

void TankController::Update()
{
	if(m_control == Control::CTRL_ARROW)
	{
		std::vector<Component*> collider2dList = m_baseEntity->GetComponents(CompType::COMP_COLLIDER2D);
		Entity* entity = NULL;

		for(int i = 0; i < collider2dList.size(); i++)
		{
			entity = static_cast<Collider2D*>(collider2dList[i])->m_collisionObject;
			if(entity && (entity->IsTaggedAs(TAG_TANK) || entity->IsTaggedAs(TAG_BRICK) || entity->IsTaggedAs(TAG_ROCK) || entity->IsTaggedAs(TAG_OCEAN)))
				break;
		}

		if(GetAsyncKeyState(VK_UP))
		{
			if(m_lockDirection != Direction::DIR_UP)
			{
				if(m_lockDirection == Direction::DIR_LEFT)
					m_baseEntity->m_transform->m_position.x = entity->m_transform->m_position.x + entity->m_collider2d->m_bound.width / 2
					+ m_baseEntity->m_collider2d->m_bound.width / 2 + 1;
				if(m_lockDirection == Direction::DIR_RIGHT)
					m_baseEntity->m_transform->m_position.x = entity->m_transform->m_position.x - entity->m_collider2d->m_bound.width / 2
					- m_baseEntity->m_collider2d->m_bound.width / 2 - 1;

				m_baseEntity->m_transform->m_position.y -= m_speed;
			}
			m_direction = Direction::DIR_UP;
			m_lockDirection = Direction::DIR_NONE;

			m_baseEntity->m_animator->m_currentFrame = 0;
			m_baseEntity->m_renderer->m_sprite = m_baseEntity->m_animator->m_frameList[m_baseEntity->m_animator->m_currentFrame];
		}
		else if(GetAsyncKeyState(VK_DOWN))
		{
			if(m_lockDirection != Direction::DIR_DOWN)
			{
				if(m_lockDirection == Direction::DIR_LEFT)
					m_baseEntity->m_transform->m_position.x = entity->m_transform->m_position.x + entity->m_collider2d->m_bound.width / 2
					+ m_baseEntity->m_collider2d->m_bound.width / 2 + 1;
				if(m_lockDirection == Direction::DIR_RIGHT)
					m_baseEntity->m_transform->m_position.x = entity->m_transform->m_position.x - entity->m_collider2d->m_bound.width / 2
					- m_baseEntity->m_collider2d->m_bound.width / 2 - 1;

				m_baseEntity->m_transform->m_position.y += m_speed;
			}
			m_direction = Direction::DIR_DOWN;
			m_lockDirection = Direction::DIR_NONE;

			m_baseEntity->m_animator->m_currentFrame = 1;
			m_baseEntity->m_renderer->m_sprite = m_baseEntity->m_animator->m_frameList[m_baseEntity->m_animator->m_currentFrame];
		}
		else if(GetAsyncKeyState(VK_LEFT))
		{
			if(m_lockDirection != Direction::DIR_LEFT)
			{
				if(m_lockDirection == Direction::DIR_UP)
					m_baseEntity->m_transform->m_position.y = entity->m_transform->m_position.y + entity->m_collider2d->m_bound.height / 2 
					+ m_baseEntity->m_collider2d->m_bound.height / 2 + 1;
				if(m_lockDirection == Direction::DIR_DOWN)
					m_baseEntity->m_transform->m_position.y = entity->m_transform->m_position.y - entity->m_collider2d->m_bound.height / 2
					- m_baseEntity->m_collider2d->m_bound.height / 2 - 1;

				m_baseEntity->m_transform->m_position.x -= m_speed;
			}
			m_direction = Direction::DIR_LEFT;
			m_lockDirection = Direction::DIR_NONE;

			m_baseEntity->m_animator->m_currentFrame = 2;
			m_baseEntity->m_renderer->m_sprite = m_baseEntity->m_animator->m_frameList[m_baseEntity->m_animator->m_currentFrame];
		}
		else if(GetAsyncKeyState(VK_RIGHT))
		{
			if(m_lockDirection != Direction::DIR_RIGHT)
			{
				if(m_lockDirection == Direction::DIR_UP)
					m_baseEntity->m_transform->m_position.y = entity->m_transform->m_position.y + entity->m_collider2d->m_bound.height / 2
					+ m_baseEntity->m_collider2d->m_bound.height / 2 + 1;
				if(m_lockDirection == Direction::DIR_DOWN)
					m_baseEntity->m_transform->m_position.y = entity->m_transform->m_position.y - entity->m_collider2d->m_bound.height / 2
					- m_baseEntity->m_collider2d->m_bound.height / 2 - 1;

				m_baseEntity->m_transform->m_position.x += m_speed;
			}
			m_direction = Direction::DIR_RIGHT;
			m_lockDirection = Direction::DIR_NONE;

			m_baseEntity->m_animator->m_currentFrame = 3;
			m_baseEntity->m_renderer->m_sprite = m_baseEntity->m_animator->m_frameList[m_baseEntity->m_animator->m_currentFrame];
		}

		if(GetAsyncKeyState(VK_SPACE))
		{
			if(m_canShoot)
			{
				Factory::GetInstance()->CreateBullet(m_team, m_baseEntity->m_transform->m_position, m_direction, m_bullet, m_shootSpeed, m_shootRange, m_damage);

				m_canShoot = false;
				m_previousTime = clock();
			}
		}
	}
	else if(m_control == Control::CTRL_WSAD)
	{

	}
	else if(m_control == Control::CTRL_AUTO)
	{
		m_stateMachine.Update();
	}

	if(m_invisible)
	{
		if(1.0f * (clock() - m_timer) / CLOCKS_PER_SEC >= m_expTime)
			m_invisible = false;
	}

	if(1.0f * (clock() - m_previousTime) / CLOCKS_PER_SEC >= 1.0f / m_shootPerSec)
		m_canShoot = true;
}

void TankController::CalculateHeuristic()
{
	int hp = static_cast<HealthControl*>(m_baseEntity->GetComponent(CompType::COMP_HEALTHCONTROL))->m_health;

	m_heuristicValue = hp / MAX_HP * 100.0f + m_speed / MAX_SPEED * 100 
		+ m_damage / MAX_DAMAGE * 100.0f + m_shootPerSec / MAX_SHOOT_PER_SEC * 100.0f;
	if(m_invisible)
		m_heuristicValue += 100.0f;
}
#pragma endregion


#pragma region BulletController
BulletController::BulletController()
{
	m_type = CompType::COMP_BULLETCONTROLLER;
}

BulletController::~BulletController()
{

}

void BulletController::Release()
{

}

void BulletController::Update()
{
	if(m_direction == Direction::DIR_UP)
	{
		m_baseEntity->m_transform->m_position.y -= m_speed;
		if(m_savePosition.y - m_baseEntity->m_transform->m_position.y >= m_range)
		{
			EntitiesSystem::GetInstance()->Remove(m_baseEntity);
			return;
		}
	}
	else if(m_direction == Direction::DIR_DOWN)
	{
		m_baseEntity->m_transform->m_position.y += m_speed;
		if(m_baseEntity->m_transform->m_position.y - m_savePosition.y >= m_range)
		{
			EntitiesSystem::GetInstance()->Remove(m_baseEntity);
			return;
		}
	}
	else if(m_direction == Direction::DIR_LEFT)
	{
		m_baseEntity->m_transform->m_position.x -= m_speed;
		if(m_savePosition.x - m_baseEntity->m_transform->m_position.x >= m_range)
		{
			EntitiesSystem::GetInstance()->Remove(m_baseEntity);
			return;
		}
	}
	else if(m_direction == Direction::DIR_RIGHT)
	{
		m_baseEntity->m_transform->m_position.x += m_speed;
		if(m_baseEntity->m_transform->m_position.x - m_savePosition.x >= m_range)
		{
			EntitiesSystem::GetInstance()->Remove(m_baseEntity);
			return;
		}
	}

	Collider2D* collider = m_baseEntity->m_collider2d;
	if(collider->m_collisionObject)
	{
		if(collider->m_collisionObject->IsTaggedAs(TAG_TANK))
		{
			if(!static_cast<TankController*>(collider->m_collisionObject->GetComponent(CompType::COMP_TANKCONTROLLER))->m_invisible)
			{
				if(m_team != static_cast<TankController*>(collider->m_collisionObject->GetComponent(CompType::COMP_TANKCONTROLLER))->m_team)
				{
					HealthControl* healthControl = static_cast<HealthControl*>(collider->m_collisionObject->GetComponent(CompType::COMP_HEALTHCONTROL));
					healthControl->m_health -= m_damage;

					EntitiesSystem::GetInstance()->Remove(m_baseEntity);
				}
			}
		}
		else if(collider->m_collisionObject->IsTaggedAs(TAG_BRICK))
		{
			BrickControl* brickControl = static_cast<BrickControl*>(collider->m_collisionObject->GetComponent(CompType::COMP_BRICKCONTROL));
			brickControl->m_health -= m_damage;

			EntitiesSystem::GetInstance()->Remove(m_baseEntity);
		}
		else if(collider->m_collisionObject->IsTaggedAs(TAG_ROCK))
		{
			EntitiesSystem::GetInstance()->Remove(m_baseEntity);
		}
		else if(collider->m_collisionObject->IsTaggedAs(TAG_SCREENCOLLIDER))
		{

		}
	}
}
#pragma endregion


#pragma region HealthControl
HealthControl::HealthControl(Tank _type)
{
	m_type = CompType::COMP_HEALTHCONTROL;

	switch(_type)
	{
		case Tank::TANK_NORMAL:
			m_health = 100.0f;
			break;
		case Tank::TANK_DEFENSE:
			m_health = 60.0f;
			break;
		case Tank::TANK_BOLT:
			m_health = 80.0f;
			break;
	}
}

HealthControl::~HealthControl()
{

}

void HealthControl::Release()
{

}

void HealthControl::Update()
{
	char* uiText = static_cast<UIText*>(m_baseEntity->m_transform->m_childList[0]->m_baseEntity->GetComponent(CompType::COMP_UITEXT))->m_text;
	uiText[0] = '\0';
	strcat(uiText, "HP = ");
	strcat(uiText, convertToString(m_health));

	if(m_health <= 0)
	{
		DetectEnemy* detectEnemy = static_cast<DetectEnemy*>(m_baseEntity->GetComponent(CompType::COMP_DETECTENEMY));
		if(detectEnemy->m_encounterEnemy)
			static_cast<DetectEnemy*>(detectEnemy->m_encounterEnemy->GetComponent(CompType::COMP_DETECTENEMY))->m_targetEnemy = NULL;
		EntitiesSystem::GetInstance()->Remove(m_baseEntity);
	}
}
#pragma endregion


#pragma region BrickControl
BrickControl::BrickControl()
{
	m_type = CompType::COMP_BRICKCONTROL;
	m_position = Vec2(0, 0);
}

BrickControl::~BrickControl()
{

}

void BrickControl::Release()
{

}

void BrickControl::Update()
{
	if(m_health >= 75.0f)
	{
		Map::GetInstance()->m_map[(int)m_position.x][(int)m_position.y] = 4;
	}
	else if(m_health >= 50.0f)
	{

	}
	else if(m_health >= 25.0f)
	{

	}
	else if(m_health >= 0.0f)
	{
		
	}
	else
	{
		Map::GetInstance()->m_map[(int)m_position.x][(int)m_position.y] = 0;
		EntitiesSystem::GetInstance()->Remove(m_baseEntity);
	}
}
#pragma endregion


#pragma region Manager
Manager::Manager()
{
	m_type = CompType::COMP_MANAGER;
}

Manager::~Manager()
{
	
}

void Manager::Release()
{

}

void Manager::Update()
{
	std::vector<Transform*> childList = m_baseEntity->m_transform->m_childList;
	char* tank1 = static_cast<UIText*>(childList[0]->m_baseEntity->GetComponent(CompType::COMP_UITEXT))->m_text;
	tank1[0] = '\0';

	char* tank2 = static_cast<UIText*>(childList[1]->m_baseEntity->GetComponent(CompType::COMP_UITEXT))->m_text;
	tank2[0] = '\0';

	char* tank3 = static_cast<UIText*>(childList[2]->m_baseEntity->GetComponent(CompType::COMP_UITEXT))->m_text;
	tank3[0] = '\0';

	if(m_team == Team::TEAM_RED)
	{
		strcat(tank1, convertToString(Map::GetInstance()->m_teamRed[0]));
		strcat(tank2, convertToString(Map::GetInstance()->m_teamRed[1]));
		strcat(tank3, convertToString(Map::GetInstance()->m_teamRed[2]));
	}
	else
	{
		strcat(tank1, convertToString(Map::GetInstance()->m_teamBlue[0]));
		strcat(tank2, convertToString(Map::GetInstance()->m_teamBlue[1]));
		strcat(tank3, convertToString(Map::GetInstance()->m_teamBlue[2]));
	}

	for(int i = 0; i < MAX_TANK; i++)
	{
		if(m_team == Team::TEAM_RED)
		{
			if(!m_teamRed[i])
			{
				if(Map::GetInstance()->m_teamRed[0])
				{
					if(m_player)
					{
						m_teamRed[i] = Factory::GetInstance()->CreateTank(Team::TEAM_RED, Vec3(), Control::CTRL_AUTO, Tank::TANK_NORMAL);
						Map::GetInstance()->m_teamRed[0]--;
					}
					else
					{
						m_teamRed[i] = Factory::GetInstance()->CreateTank(Team::TEAM_RED, Vec3(), Control::CTRL_ARROW, Tank::TANK_NORMAL);
						m_player = m_teamRed[i];
						Map::GetInstance()->m_teamRed[0]--;
					}
				}
			}
		}

		if(m_team == Team::TEAM_BLUE)
		{
			if(!m_teamBlue[i])
			{
				if(Map::GetInstance()->m_teamBlue[0])
				{
					m_teamBlue[i] = Factory::GetInstance()->CreateTank(Team::TEAM_BLUE, Vec3(), CTRL_AUTO, Tank::TANK_NORMAL);	// Choose type later
					Map::GetInstance()->m_teamBlue[0]--;
				}
			}
		}
	}
}
#pragma endregion


#pragma region ItemManager
ItemManager::ItemManager(Item _type)
{
	m_type = CompType::COMP_ITEMMANAGER;
	m_item = _type;

	m_plusHP = 0.0f;
	m_plusSpeed = 0.0f;
	m_plusDamage = 0.0f;
	m_plusTank = false;
	m_plusBullet = false;
	m_invisible = false;
	m_expTime = 0.0f;

	switch(m_item)
	{
		case Item::ITEM_HP:
			m_plusHP = 50.0f;
			break;
		case Item::ITEM_SPEED:
			m_plusSpeed = 3.0f;
			break;
		case Item::ITEM_DAMAGE:
			m_plusDamage = 10.0f;
			break;
		case Item::ITEM_TANK:
			m_plusTank = true;
			break;
		case Item::ITEM_INVISIBLE:
			m_invisible = true;
			m_expTime = 15.0f;
			break;
		case Item::ITEM_BULLET:
			m_plusBullet = true;
			break;
	}
}

ItemManager::~ItemManager()
{

}

void ItemManager::Release()
{

}

void ItemManager::Update()
{

}
#pragma endregion


#pragma region DetectEnemy
DetectEnemy::DetectEnemy()
{
	m_type = CompType::COMP_DETECTENEMY;

	m_targetEnemy = NULL;
	m_encounterEnemy = NULL;
}

DetectEnemy::~DetectEnemy()
{

}

void DetectEnemy::Release()
{

}

void DetectEnemy::Update()
{
	std::vector<Entity*> enemyList;
	Rect radar;
	radar.width = radar.height = static_cast<TankController*>(m_baseEntity->GetComponent(CompType::COMP_TANKCONTROLLER))->m_shootRange;
	radar.x = m_baseEntity->m_transform->m_position.x - radar.width / 2;
	radar.y = m_baseEntity->m_transform->m_position.y - radar.height / 2;

	if(static_cast<TankController*>(m_baseEntity->GetComponent(CompType::COMP_TANKCONTROLLER))->m_team == Team::TEAM_RED)
		enemyList = EntitiesSystem::GetInstance()->Retrieve(radar, Team::TEAM_BLUE);
	else
		enemyList = EntitiesSystem::GetInstance()->Retrieve(radar, Team::TEAM_RED);

	std::vector<Entity*> obstacleList = EntitiesSystem::GetInstance()->Retrieve(radar, TAG_ROCK);

	float minH = 10000.0f;
	if(!m_targetEnemy)
	{
		for(int i = 0; i < enemyList.size(); i++)
		{
			float h = static_cast<TankController*>(enemyList[i]->GetComponent(CompType::COMP_TANKCONTROLLER))->m_heuristicValue;
			for(int j = 0; j < obstacleList.size(); j++)
			{
				if(obstacleList[j]->m_transform->IsMiddle(m_baseEntity->m_transform, enemyList[i]->m_transform))
					h += obstacleList[j]->m_collider2d->m_bound.width + obstacleList[j]->m_collider2d->m_bound.height;
			}

			if(h * 0.75f <= static_cast<TankController*>(m_baseEntity->GetComponent(CompType::COMP_TANKCONTROLLER))->m_heuristicValue && h < minH)
			{
				minH = h;
				m_targetEnemy = enemyList[i];
				static_cast<DetectEnemy*>(m_targetEnemy->GetComponent(CompType::COMP_DETECTENEMY))->m_encounterEnemy = m_baseEntity;
			}
		}
	}
	else if(!radar.checkAABB(m_targetEnemy->m_collider2d->m_bound))
	{
		static_cast<DetectEnemy*>(m_targetEnemy->GetComponent(CompType::COMP_DETECTENEMY))->m_encounterEnemy = NULL;
		m_targetEnemy = NULL;
	}
}
#pragma endregion


#pragma region AutoTankManager
AutoTankManager::AutoTankManager()
{
	m_type = CompType::COMP_AUTOTANKANAGER;
}

AutoTankManager::~AutoTankManager()
{

}

void AutoTankManager::Release()
{

}

void AutoTankManager::Update()
{
	
}

void AutoTankManager::Move(Direction _direction)
{
	std::vector<Component*> collider2dList = m_baseEntity->GetComponents(CompType::COMP_COLLIDER2D);
	Entity* entity = NULL;

	for(int i = 0; i < collider2dList.size(); i++)
	{
		entity = static_cast<Collider2D*>(collider2dList[i])->m_collisionObject;
		if(entity && (entity->IsTaggedAs(TAG_TANK) || entity->IsTaggedAs(TAG_BRICK) || entity->IsTaggedAs(TAG_ROCK) || entity->IsTaggedAs(TAG_OCEAN)))
			break;
	}

	TankController* tankController = static_cast<TankController*>(m_baseEntity->GetComponent(CompType::COMP_TANKCONTROLLER));
	if(_direction == Direction::DIR_UP)
	{
		if(tankController->m_lockDirection == Direction::DIR_LEFT)
			m_baseEntity->m_transform->m_position.x = entity->m_transform->m_position.x + entity->m_collider2d->m_bound.width / 2
			+ m_baseEntity->m_collider2d->m_bound.width / 2 + 1;
		if(tankController->m_lockDirection == Direction::DIR_RIGHT)
			m_baseEntity->m_transform->m_position.x = entity->m_transform->m_position.x - entity->m_collider2d->m_bound.width / 2
			- m_baseEntity->m_collider2d->m_bound.width / 2 - 1;

		m_baseEntity->m_transform->m_position.y -= tankController->m_speed;
		tankController->m_lockDirection = Direction::DIR_NONE;

		m_baseEntity->m_animator->m_currentFrame = 0;
		m_baseEntity->m_renderer->m_sprite = m_baseEntity->m_animator->m_frameList[m_baseEntity->m_animator->m_currentFrame];
	}
	else if(_direction == Direction::DIR_DOWN)
	{
		if(tankController->m_lockDirection == Direction::DIR_LEFT)
			m_baseEntity->m_transform->m_position.x = entity->m_transform->m_position.x + entity->m_collider2d->m_bound.width / 2
			+ m_baseEntity->m_collider2d->m_bound.width / 2 + 1;
		if(tankController->m_lockDirection == Direction::DIR_RIGHT)
			m_baseEntity->m_transform->m_position.x = entity->m_transform->m_position.x - entity->m_collider2d->m_bound.width / 2
			- m_baseEntity->m_collider2d->m_bound.width / 2 - 1;

		m_baseEntity->m_transform->m_position.y += tankController->m_speed;
		tankController->m_lockDirection = Direction::DIR_NONE;

		m_baseEntity->m_animator->m_currentFrame = 1;
		m_baseEntity->m_renderer->m_sprite = m_baseEntity->m_animator->m_frameList[m_baseEntity->m_animator->m_currentFrame];
	}
	else if(_direction == Direction::DIR_LEFT)
	{
		if(tankController->m_lockDirection == Direction::DIR_UP)
			m_baseEntity->m_transform->m_position.y = entity->m_transform->m_position.y - entity->m_collider2d->m_bound.height / 2
			- m_baseEntity->m_collider2d->m_bound.height / 2 - 1;
		if(tankController->m_lockDirection == Direction::DIR_DOWN)
			m_baseEntity->m_transform->m_position.y = entity->m_transform->m_position.y + entity->m_collider2d->m_bound.height / 2
			+ m_baseEntity->m_collider2d->m_bound.height / 2 + 1;

		m_baseEntity->m_transform->m_position.x -= tankController->m_speed;
		tankController->m_lockDirection = Direction::DIR_NONE;

		m_baseEntity->m_animator->m_currentFrame = 2;
		m_baseEntity->m_renderer->m_sprite = m_baseEntity->m_animator->m_frameList[m_baseEntity->m_animator->m_currentFrame];
	}
	else if(_direction == Direction::DIR_RIGHT)
	{
		if(tankController->m_lockDirection == Direction::DIR_UP)
			m_baseEntity->m_transform->m_position.y = entity->m_transform->m_position.y - entity->m_collider2d->m_bound.height / 2
			- m_baseEntity->m_collider2d->m_bound.height / 2 - 1;
		if(tankController->m_lockDirection == Direction::DIR_DOWN)
			m_baseEntity->m_transform->m_position.y = entity->m_transform->m_position.y + entity->m_collider2d->m_bound.height / 2
			+ m_baseEntity->m_collider2d->m_bound.height / 2 + 1;

		m_baseEntity->m_transform->m_position.x += tankController->m_speed;
		tankController->m_lockDirection = Direction::DIR_NONE;

		m_baseEntity->m_animator->m_currentFrame = 3;
		m_baseEntity->m_renderer->m_sprite = m_baseEntity->m_animator->m_frameList[m_baseEntity->m_animator->m_currentFrame];
	}
}

Direction AutoTankManager::GetNextRandomDirection(Direction _currentDirection)
{
	TankController* tankController = static_cast<TankController*>(m_baseEntity->GetComponent(CompType::COMP_TANKCONTROLLER));
	int x = rand() % 100;
	if(x < 85)
	{
		if(tankController->m_lockDirection != _currentDirection)
			return _currentDirection;
	}
	else if(x < 86)
	{
		if(tankController->m_lockDirection != Direction::DIR_UP)
			return Direction::DIR_UP;
	}
	else if(x < 87)
	{
		if(tankController->m_lockDirection != Direction::DIR_DOWN)
			return Direction::DIR_DOWN;
	}
	else if(x < 88)
	{
		if(tankController->m_lockDirection != Direction::DIR_LEFT)
			return Direction::DIR_LEFT;
	}
	else if(x < 89)
	{
		if(tankController->m_lockDirection != Direction::DIR_RIGHT)
			return Direction::DIR_RIGHT;
	}

	return Direction::DIR_NONE;
}

Direction AutoTankManager::GetShootDirection(Vec3 _targetPosition)
{
	if(abs(m_baseEntity->m_transform->m_position.x - _targetPosition.x) > abs(m_baseEntity->m_transform->m_position.y - _targetPosition.y))
	{
		if(m_baseEntity->m_transform->m_position.x > _targetPosition.x)
			return Direction::DIR_LEFT;
		else
			return Direction::DIR_RIGHT;
	}
	else
	{
		if(m_baseEntity->m_transform->m_position.y > _targetPosition.y)
			return Direction::DIR_UP;
		else 
			return Direction::DIR_DOWN;
	}
}

Direction AutoTankManager::GetDirectionToEnemy(Vec3 _targetPosition)
{
	return Direction::DIR_NONE;
}

Direction AutoTankManager::GetDirectionAwayFromEnemy(Vec3 _targetPosition)
{
	return Direction::DIR_NONE;
}

bool AutoTankManager::IsInShootRange(Vec3 _targetPosition)
{
	DetectEnemy* detectEnemy = static_cast<DetectEnemy*>(m_baseEntity->GetComponent(CompType::COMP_DETECTENEMY));
	if(abs(detectEnemy->m_targetEnemy->m_transform->m_position.x - m_baseEntity->m_transform->m_position.x) <= 64
		|| abs(detectEnemy->m_targetEnemy->m_transform->m_position.y - m_baseEntity->m_transform->m_position.y) <= 64)
		return true;
	return false;
}

bool AutoTankManager::IsEnemyInShootRange(Vec3 _targetPosition)
{
	DetectEnemy* detectEnemy = static_cast<DetectEnemy*>(m_baseEntity->GetComponent(CompType::COMP_DETECTENEMY));
	if(abs(detectEnemy->m_targetEnemy->m_transform->m_position.x - m_baseEntity->m_transform->m_position.x) <= 64
		|| abs(detectEnemy->m_targetEnemy->m_transform->m_position.y - m_baseEntity->m_transform->m_position.y) <= 64)
		return true;
	return false;
}
#pragma endregion