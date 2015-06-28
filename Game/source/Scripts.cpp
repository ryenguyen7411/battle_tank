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

	switch(m_tank)
	{
		case Tank::TANK_NORMAL:
			m_speed = 4.0f;
			m_damage = 15.0f;

			m_shootSpeed = 10.0f;
			m_shootRange = 400.0f;
			m_shootPerSec = 2;

			m_bullet = Bullet::BULLET_NORMAL;
			break;
		case Tank::TANK_DEFENSE:
			m_speed = 2.0f;
			m_damage = 40.0f;

			m_shootSpeed = 10.0f;
			m_shootRange = 200.0f;
			m_shootPerSec = 1;

			m_bullet = Bullet::BULLET_EXPLODE;
			break;
		case Tank::TANK_BOLT:
			m_speed = 7.0f;
			m_damage = 10.0f;

			m_shootSpeed = 20.0f;
			m_shootRange = 300.0f;
			m_shootPerSec = 4;

			m_bullet = Bullet::BULLET_NORMAL;
			break;
	}

	m_timer = 0;
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
			if(entity && (entity->IsTaggedAs(TAG_TANK) || 
				entity->IsTaggedAs(TAG_BRICK) || 
				entity->IsTaggedAs(TAG_CONCRETE) || 
				entity->IsTaggedAs(TAG_OCEAN) ||
				entity->IsTaggedAs(TAG_SCREENCOLLIDER)))
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
		else if(collider->m_collisionObject->IsTaggedAs(TAG_CONCRETE))
		{
			EntitiesSystem::GetInstance()->Remove(m_baseEntity);
		}
		else if(collider->m_collisionObject->IsTaggedAs(TAG_SCREENCOLLIDER))
		{
			EntitiesSystem::GetInstance()->Remove(m_baseEntity);
		}

		// Explosion effect
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
	if(m_health == 100.0f)
	{
		Map::GetInstance()->m_map[(int)m_position.x][(int)m_position.y] = 4;
	}
	else if(m_health >= 75.0f)
	{
		Map::GetInstance()->m_map[(int)m_position.x][(int)m_position.y] = 5;
	}
	else if(m_health >= 50.0f)
	{
		Map::GetInstance()->m_map[(int)m_position.x][(int)m_position.y] = 6;
	}
	else if(m_health >= 25.0f)
	{
		Map::GetInstance()->m_map[(int)m_position.x][(int)m_position.y] = 7;
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

	std::vector<Entity*> obstacleList = EntitiesSystem::GetInstance()->Retrieve(radar, TAG_CONCRETE);

	float minH = 10000.0f;
	if(!m_targetEnemy)
	{
		for(int i = 0; i < enemyList.size(); i++)
		{
			float h = static_cast<TankController*>(enemyList[i]->GetComponent(CompType::COMP_TANKCONTROLLER))->m_heuristicValue;
			for(int j = 0; j < obstacleList.size(); j++)
			{
				if(obstacleList[j]->m_transform->IsMiddle(m_baseEntity->m_transform, enemyList[i]->m_transform))
				{
					h += obstacleList[j]->m_collider2d->m_bound.width + obstacleList[j]->m_collider2d->m_bound.height;
				}
			}

			if(h < minH)
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

	m_virtualKey = KeyCode::KEY_UNKNOWN;
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

void AutoTankManager::Move()
{
	std::vector<Component*> collider2dList = m_baseEntity->GetComponents(CompType::COMP_COLLIDER2D);
	Entity* entity = NULL;

	for(int i = 0; i < collider2dList.size(); i++)
	{
		entity = static_cast<Collider2D*>(collider2dList[i])->m_collisionObject;
		if(entity && (entity->IsTaggedAs(TAG_TANK) || 
			entity->IsTaggedAs(TAG_BRICK) || 
			entity->IsTaggedAs(TAG_CONCRETE) || 
			entity->IsTaggedAs(TAG_OCEAN) ||
			entity->IsTaggedAs(TAG_SCREENCOLLIDER)))
			break;
	}

	TankController* tankController = static_cast<TankController*>(m_baseEntity->GetComponent(CompType::COMP_TANKCONTROLLER));
	if(m_virtualKey == KeyCode::KEY_UP)
	{
		if(tankController->m_lockDirection != Direction::DIR_UP)
		{
			if(tankController->m_lockDirection == Direction::DIR_LEFT)
				m_baseEntity->m_transform->m_position.x = entity->m_transform->m_position.x + entity->m_collider2d->m_bound.width / 2
				+ m_baseEntity->m_collider2d->m_bound.width / 2 + 1;
			if(tankController->m_lockDirection == Direction::DIR_RIGHT)
				m_baseEntity->m_transform->m_position.x = entity->m_transform->m_position.x - entity->m_collider2d->m_bound.width / 2
				- m_baseEntity->m_collider2d->m_bound.width / 2 - 1;

			m_baseEntity->m_transform->m_position.y -= tankController->m_speed;
		}
		tankController->m_direction = Direction::DIR_UP;
		tankController->m_lockDirection = Direction::DIR_NONE;

		m_baseEntity->m_animator->m_currentFrame = 0;
		m_baseEntity->m_renderer->m_sprite = m_baseEntity->m_animator->m_frameList[m_baseEntity->m_animator->m_currentFrame];
	}
	else if(m_virtualKey == KeyCode::KEY_DOWN)
	{
		if(tankController->m_lockDirection != Direction::DIR_DOWN)
		{
			if(tankController->m_lockDirection == Direction::DIR_LEFT)
				m_baseEntity->m_transform->m_position.x = entity->m_transform->m_position.x + entity->m_collider2d->m_bound.width / 2
				+ m_baseEntity->m_collider2d->m_bound.width / 2 + 1;
			if(tankController->m_lockDirection == Direction::DIR_RIGHT)
				m_baseEntity->m_transform->m_position.x = entity->m_transform->m_position.x - entity->m_collider2d->m_bound.width / 2
				- m_baseEntity->m_collider2d->m_bound.width / 2 - 1;

			m_baseEntity->m_transform->m_position.y += tankController->m_speed;
		}
		tankController->m_direction = Direction::DIR_DOWN;
		tankController->m_lockDirection = Direction::DIR_NONE;

		m_baseEntity->m_animator->m_currentFrame = 1;
		m_baseEntity->m_renderer->m_sprite = m_baseEntity->m_animator->m_frameList[m_baseEntity->m_animator->m_currentFrame];
	}
	else if(m_virtualKey == KeyCode::KEY_LEFT)
	{
		if(tankController->m_lockDirection != Direction::DIR_LEFT)
		{
			if(tankController->m_lockDirection == Direction::DIR_UP)
				m_baseEntity->m_transform->m_position.y = entity->m_transform->m_position.y + entity->m_collider2d->m_bound.height / 2
				+ m_baseEntity->m_collider2d->m_bound.height / 2 + 1;
			if(tankController->m_lockDirection == Direction::DIR_DOWN)
				m_baseEntity->m_transform->m_position.y = entity->m_transform->m_position.y - entity->m_collider2d->m_bound.height / 2
				- m_baseEntity->m_collider2d->m_bound.height / 2 - 1;

			m_baseEntity->m_transform->m_position.x -= tankController->m_speed;
		}
		tankController->m_direction = Direction::DIR_LEFT;
		tankController->m_lockDirection = Direction::DIR_NONE;

		m_baseEntity->m_animator->m_currentFrame = 2;
		m_baseEntity->m_renderer->m_sprite = m_baseEntity->m_animator->m_frameList[m_baseEntity->m_animator->m_currentFrame];
	}
	else if(m_virtualKey == KeyCode::KEY_RIGHT)
	{
		if(tankController->m_lockDirection != Direction::DIR_RIGHT)
		{
			if(tankController->m_lockDirection == Direction::DIR_UP)
				m_baseEntity->m_transform->m_position.y = entity->m_transform->m_position.y + entity->m_collider2d->m_bound.height / 2
				+ m_baseEntity->m_collider2d->m_bound.height / 2 + 1;
			if(tankController->m_lockDirection == Direction::DIR_DOWN)
				m_baseEntity->m_transform->m_position.y = entity->m_transform->m_position.y - entity->m_collider2d->m_bound.height / 2
				- m_baseEntity->m_collider2d->m_bound.height / 2 - 1;

			m_baseEntity->m_transform->m_position.x += tankController->m_speed;
		}
		tankController->m_direction = Direction::DIR_RIGHT;
		tankController->m_lockDirection = Direction::DIR_NONE;

		m_baseEntity->m_animator->m_currentFrame = 3;
		m_baseEntity->m_renderer->m_sprite = m_baseEntity->m_animator->m_frameList[m_baseEntity->m_animator->m_currentFrame];
	}
}

void AutoTankManager::Shoot()
{
	TankController* tankController = static_cast<TankController*>(m_baseEntity->GetComponent(CompType::COMP_TANKCONTROLLER));

	if(tankController->m_canShoot && rand() % 100 < 10)
	{
		Factory::GetInstance()->CreateBullet(tankController->m_team, m_baseEntity->m_transform->m_position, tankController->m_direction,
			tankController->m_bullet, tankController->m_shootSpeed, tankController->m_shootRange, tankController->m_damage);

		tankController->m_canShoot = false;
		tankController->m_previousTime = clock();
	}
}

void AutoTankManager::ChangeDirection()
{
	std::vector<Component*> collider2dList = m_baseEntity->GetComponents(CompType::COMP_COLLIDER2D);
	Entity* entity = NULL;

	for(int i = 0; i < collider2dList.size(); i++)
	{
		entity = static_cast<Collider2D*>(collider2dList[i])->m_collisionObject;
		if(entity && (entity->IsTaggedAs(TAG_TANK) ||
			entity->IsTaggedAs(TAG_BRICK) ||
			entity->IsTaggedAs(TAG_CONCRETE) ||
			entity->IsTaggedAs(TAG_OCEAN) ||
			entity->IsTaggedAs(TAG_SCREENCOLLIDER)))
			break;
	}

	TankController* tankController = static_cast<TankController*>(m_baseEntity->GetComponent(CompType::COMP_TANKCONTROLLER));
	if(m_virtualKey == KeyCode::KEY_UP)
	{
		if(tankController->m_lockDirection != Direction::DIR_UP)
		{
			if(tankController->m_lockDirection == Direction::DIR_LEFT)
				m_baseEntity->m_transform->m_position.x = entity->m_transform->m_position.x + entity->m_collider2d->m_bound.width / 2
				+ m_baseEntity->m_collider2d->m_bound.width / 2 + 1;
			if(tankController->m_lockDirection == Direction::DIR_RIGHT)
				m_baseEntity->m_transform->m_position.x = entity->m_transform->m_position.x - entity->m_collider2d->m_bound.width / 2
				- m_baseEntity->m_collider2d->m_bound.width / 2 - 1;
		}
		tankController->m_direction = Direction::DIR_UP;
		tankController->m_lockDirection = Direction::DIR_NONE;

		m_baseEntity->m_animator->m_currentFrame = 0;
		m_baseEntity->m_renderer->m_sprite = m_baseEntity->m_animator->m_frameList[m_baseEntity->m_animator->m_currentFrame];
	}
	else if(m_virtualKey == KeyCode::KEY_DOWN)
	{
		if(tankController->m_lockDirection != Direction::DIR_DOWN)
		{
			if(tankController->m_lockDirection == Direction::DIR_LEFT)
				m_baseEntity->m_transform->m_position.x = entity->m_transform->m_position.x + entity->m_collider2d->m_bound.width / 2
				+ m_baseEntity->m_collider2d->m_bound.width / 2 + 1;
			if(tankController->m_lockDirection == Direction::DIR_RIGHT)
				m_baseEntity->m_transform->m_position.x = entity->m_transform->m_position.x - entity->m_collider2d->m_bound.width / 2
				- m_baseEntity->m_collider2d->m_bound.width / 2 - 1;
		}
		tankController->m_direction = Direction::DIR_DOWN;
		tankController->m_lockDirection = Direction::DIR_NONE;

		m_baseEntity->m_animator->m_currentFrame = 1;
		m_baseEntity->m_renderer->m_sprite = m_baseEntity->m_animator->m_frameList[m_baseEntity->m_animator->m_currentFrame];
	}
	else if(m_virtualKey == KeyCode::KEY_LEFT)
	{
		if(tankController->m_lockDirection != Direction::DIR_LEFT)
		{
			if(tankController->m_lockDirection == Direction::DIR_UP)
				m_baseEntity->m_transform->m_position.y = entity->m_transform->m_position.y + entity->m_collider2d->m_bound.height / 2
				+ m_baseEntity->m_collider2d->m_bound.height / 2 + 1;
			if(tankController->m_lockDirection == Direction::DIR_DOWN)
				m_baseEntity->m_transform->m_position.y = entity->m_transform->m_position.y - entity->m_collider2d->m_bound.height / 2
				- m_baseEntity->m_collider2d->m_bound.height / 2 - 1;
		}
		tankController->m_direction = Direction::DIR_LEFT;
		tankController->m_lockDirection = Direction::DIR_NONE;

		m_baseEntity->m_animator->m_currentFrame = 2;
		m_baseEntity->m_renderer->m_sprite = m_baseEntity->m_animator->m_frameList[m_baseEntity->m_animator->m_currentFrame];
	}
	else if(m_virtualKey == KeyCode::KEY_RIGHT)
	{
		if(tankController->m_lockDirection != Direction::DIR_RIGHT)
		{
			if(tankController->m_lockDirection == Direction::DIR_UP)
				m_baseEntity->m_transform->m_position.y = entity->m_transform->m_position.y + entity->m_collider2d->m_bound.height / 2
				+ m_baseEntity->m_collider2d->m_bound.height / 2 + 1;
			if(tankController->m_lockDirection == Direction::DIR_DOWN)
				m_baseEntity->m_transform->m_position.y = entity->m_transform->m_position.y - entity->m_collider2d->m_bound.height / 2
				- m_baseEntity->m_collider2d->m_bound.height / 2 - 1;
		}
		tankController->m_direction = Direction::DIR_RIGHT;
		tankController->m_lockDirection = Direction::DIR_NONE;

		m_baseEntity->m_animator->m_currentFrame = 3;
		m_baseEntity->m_renderer->m_sprite = m_baseEntity->m_animator->m_frameList[m_baseEntity->m_animator->m_currentFrame];
	}
}

KeyCode AutoTankManager::GetNextRandomKey()
{
	int x = rand() % 100;
	if(x < 95)
	{
		return m_virtualKey;
	}
	else if(x < 96)
	{
		return KeyCode::KEY_UP;
	}
	else if(x < 97)
	{
		return KeyCode::KEY_DOWN;
	}
	else if(x < 98)
	{
		return KeyCode::KEY_LEFT;
	}
	else if(x < 99)
	{
		return KeyCode::KEY_RIGHT;
	}

	return KeyCode::KEY_UNKNOWN;
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
	TankController* tankController = static_cast<TankController*>(m_baseEntity->GetComponent(CompType::COMP_TANKCONTROLLER));
	Vec3 targetMapPosition = Map::GetInstance()->GetMapPosition(_targetPosition);

	Rect bound = m_baseEntity->m_collider2d->m_bound;

	int canMove[4] = {0};
	int distance[4] = {0};
	int deltaDistance[4] = {0};

	int optimalDirection = -1;

	int	nextMapValue[4] = {0};

	if(nextMapValue[0] = Map::GetInstance()->GetMapValue(Map::GetInstance()->GetMapPosition(
		Vec3(bound.x + bound.width / 2, bound.y - tankController->m_speed, 0))) < 2 || nextMapValue[0] >= 4)
	{
		canMove[0] = 1;
		distance[0] = abs(bound.x + bound.width / 2 - _targetPosition.x) + abs(bound.y - tankController->m_speed - _targetPosition.y);
		deltaDistance[0] = abs(abs(m_baseEntity->m_transform->m_position.x - _targetPosition.x) - abs(m_baseEntity->m_transform->m_position.y - tankController->m_speed - _targetPosition.y));
	}
	if(nextMapValue[1] = Map::GetInstance()->GetMapValue(Map::GetInstance()->GetMapPosition(
		Vec3(bound.x + bound.width / 2, bound.y + bound.height + tankController->m_speed, 0))) < 2 || nextMapValue[1] >= 4)
	{
		canMove[1] = 1;
		distance[1] = abs(bound.x + bound.width / 2 - _targetPosition.x) + abs(bound.y + bound.height + tankController->m_speed - _targetPosition.y);
		deltaDistance[1] = abs(abs(m_baseEntity->m_transform->m_position.x - _targetPosition.x) - abs(m_baseEntity->m_transform->m_position.y + tankController->m_speed - _targetPosition.y));
	}
	if(nextMapValue[2] = Map::GetInstance()->GetMapValue(Map::GetInstance()->GetMapPosition(
		Vec3(bound.x - tankController->m_speed, bound.y + bound.height / 2, 0))) < 2 || nextMapValue[2] >= 4)
	{
		canMove[2] = 1;
		distance[2] = abs(bound.x - tankController->m_speed - _targetPosition.x) + abs(bound.y + bound.height / 2 - tankController->m_speed - _targetPosition.y);
		deltaDistance[2] = abs(abs(m_baseEntity->m_transform->m_position.x - tankController->m_speed - _targetPosition.x) - abs(m_baseEntity->m_transform->m_position.y - _targetPosition.y));
	}
	if(nextMapValue[3] = Map::GetInstance()->GetMapValue(Map::GetInstance()->GetMapPosition(
		Vec3(bound.x + bound.width + tankController->m_speed, bound.y + bound.height / 2, 0))) < 2 || nextMapValue[3] >= 4)
	{
		canMove[3] = 1;
		distance[3] = abs(bound.x + bound.width + tankController->m_speed - _targetPosition.x) + abs(bound.y + bound.height / 2 - _targetPosition.y);
		deltaDistance[3] = abs(abs(m_baseEntity->m_transform->m_position.x + tankController->m_speed - _targetPosition.x) - abs(m_baseEntity->m_transform->m_position.y - _targetPosition.y));
	}
	
	

	if(canMove[tankController->m_direction])
		optimalDirection = tankController->m_direction;
	else
	for(int i = 0; i < Direction::DIR_COUNT; i++)
	{
		if(canMove[i])
		{
			if(optimalDirection == -1)
				optimalDirection = i;
			else
			{
				if(distance[optimalDirection] > distance[i])
					optimalDirection = i;
				else if(distance[optimalDirection] == distance[i] && deltaDistance[optimalDirection] < deltaDistance[i])
					optimalDirection = i;
			}
		}
	}

	if(nextMapValue[optimalDirection] >= 4)
	{
		Shoot();
	}

	return (Direction)optimalDirection;
}

Direction AutoTankManager::GetDirectionAwayFromEnemy(Vec3 _targetPosition)
{
	TankController* tankController = static_cast<TankController*>(m_baseEntity->GetComponent(CompType::COMP_TANKCONTROLLER));
	Vec3 targetMapPosition = Map::GetInstance()->GetMapPosition(_targetPosition);

	Rect bound = m_baseEntity->m_collider2d->m_bound;

	int canMove[4] = {0};
	int distance[4] = {0};
	int deltaDistance[4] = {0};

	int optimalDirection = -1;

	int	nextMapValue[4] = {0};

	if(nextMapValue[0] = Map::GetInstance()->GetMapValue(Map::GetInstance()->GetMapPosition(
		Vec3(bound.x + bound.width / 2, bound.y - tankController->m_speed, 0))) < 2 || nextMapValue[0] >= 4)
	{
		canMove[0] = 1;
		distance[0] = abs(bound.x + bound.width / 2 - _targetPosition.x) + abs(bound.y - tankController->m_speed - _targetPosition.y);
		deltaDistance[0] = abs(abs(m_baseEntity->m_transform->m_position.x - _targetPosition.x) - abs(m_baseEntity->m_transform->m_position.y - tankController->m_speed - _targetPosition.y));
	}
	if(nextMapValue[1] = Map::GetInstance()->GetMapValue(Map::GetInstance()->GetMapPosition(
		Vec3(bound.x + bound.width / 2, bound.y + bound.height + tankController->m_speed, 0))) < 2 || nextMapValue[1] >= 4)
	{
		canMove[1] = 1;
		distance[1] = abs(bound.x + bound.width / 2 - _targetPosition.x) + abs(bound.y + bound.height + tankController->m_speed - _targetPosition.y);
		deltaDistance[1] = abs(abs(m_baseEntity->m_transform->m_position.x - _targetPosition.x) - abs(m_baseEntity->m_transform->m_position.y + tankController->m_speed - _targetPosition.y));
	}
	if(nextMapValue[2] = Map::GetInstance()->GetMapValue(Map::GetInstance()->GetMapPosition(
		Vec3(bound.x - tankController->m_speed, bound.y + bound.height / 2, 0))) < 2 || nextMapValue[2] >= 4)
	{
		canMove[2] = 1;
		distance[2] = abs(bound.x - tankController->m_speed - _targetPosition.x) + abs(bound.y + bound.height / 2 - tankController->m_speed - _targetPosition.y);
		deltaDistance[2] = abs(abs(m_baseEntity->m_transform->m_position.x - tankController->m_speed - _targetPosition.x) - abs(m_baseEntity->m_transform->m_position.y - _targetPosition.y));
	}
	if(nextMapValue[3] = Map::GetInstance()->GetMapValue(Map::GetInstance()->GetMapPosition(
		Vec3(bound.x + bound.width + tankController->m_speed, bound.y + bound.height / 2, 0))) < 2 || nextMapValue[3] >= 4)
	{
		canMove[3] = 1;
		distance[3] = abs(bound.x + bound.width + tankController->m_speed - _targetPosition.x) + abs(bound.y + bound.height / 2 - _targetPosition.y);
		deltaDistance[3] = abs(abs(m_baseEntity->m_transform->m_position.x + tankController->m_speed - _targetPosition.x) - abs(m_baseEntity->m_transform->m_position.y - _targetPosition.y));
	}



	if(canMove[tankController->m_direction])
		optimalDirection = tankController->m_direction;
	else
		for(int i = 0; i < Direction::DIR_COUNT; i++)
		{
			if(canMove[i])
			{
				if(optimalDirection == -1)
					optimalDirection = i;
				else
				{
					if(distance[optimalDirection] < distance[i])
						optimalDirection = i;
					else if(distance[optimalDirection] == distance[i] && deltaDistance[optimalDirection] > deltaDistance[i])
						optimalDirection = i;
				}
			}
		}

	if(nextMapValue[optimalDirection] >= 4)
	{
		Shoot();
	}

	return (Direction)optimalDirection;
}

bool AutoTankManager::IsInShootRange(Vec3 _targetPosition)
{
	DetectEnemy* detectEnemy = static_cast<DetectEnemy*>(m_baseEntity->GetComponent(CompType::COMP_DETECTENEMY));
	if(abs(detectEnemy->m_targetEnemy->m_transform->m_position.x - m_baseEntity->m_transform->m_position.x) <= 16
		|| abs(detectEnemy->m_targetEnemy->m_transform->m_position.y - m_baseEntity->m_transform->m_position.y) <= 16)
		return true;
	return false;
}

bool AutoTankManager::IsInShootRegion(Vec3 _targetPosition)
{
	DetectEnemy* detectEnemy = static_cast<DetectEnemy*>(m_baseEntity->GetComponent(CompType::COMP_DETECTENEMY));
	if(abs(detectEnemy->m_targetEnemy->m_transform->m_position.x - m_baseEntity->m_transform->m_position.x) <= 64
		|| abs(detectEnemy->m_targetEnemy->m_transform->m_position.y - m_baseEntity->m_transform->m_position.y) <= 64)
		return true;
	return false;
}

void AutoTankManager::SetKeyForDirection(Direction _direction)
{
	if(_direction == Direction::DIR_UP)
		m_virtualKey = KeyCode::KEY_UP;
	else if(_direction == Direction::DIR_DOWN)
		m_virtualKey = KeyCode::KEY_DOWN;
	else if(_direction == Direction::DIR_LEFT)
		m_virtualKey = KeyCode::KEY_LEFT;
	else if(_direction == Direction::DIR_RIGHT)
		m_virtualKey = KeyCode::KEY_RIGHT;
	else
		m_virtualKey = KeyCode::KEY_UNKNOWN;
}
#pragma endregion