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
	m_bulletLevel = 1;

	switch(m_tank)
	{
		case Tank::TANK_NORMAL:
			m_speed = 5.0f;
			m_damage = 20.0f;

			m_shootSpeed = 10.0f;
			m_shootRange = 400.0f;
			m_shootDelay = 1.0f;
			break;
		case Tank::TANK_DEFENSE:
			m_speed = 2.0f;
			m_damage = 80.0f;

			m_shootSpeed = 10.0f;
			m_shootRange = 200.0f;
			m_shootDelay = 4.0f;
			break;
		case Tank::TANK_BOLT:
			m_speed = 8.0f;
			m_damage = 20.0f;

			m_shootSpeed = 20.0f;
			m_shootRange = 300.0f;
			m_shootDelay = 0.5f;
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
			if(entity && (entity->IsTaggedAs("Tank") || entity->IsTaggedAs("Brick") || entity->IsTaggedAs("Rock") || entity->IsTaggedAs("Ocean")))
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
		//m_stateMachine.Update();
	}

	if(1000.0f * (clock() - m_previousTime) / CLOCKS_PER_SEC > m_shootDelay)
		m_canShoot = true;
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
		if(collider->m_collisionObject->IsTaggedAs("Tank"))
		{
			if(m_team != static_cast<TankController*>(collider->m_collisionObject->GetComponent(CompType::COMP_TANKCONTROLLER))->m_team)
			{
				HealthControl* healthControl = static_cast<HealthControl*>(collider->m_collisionObject->GetComponent(CompType::COMP_HEALTHCONTROL));
				healthControl->m_health -= (m_damage - healthControl->m_defense);

				EntitiesSystem::GetInstance()->Remove(m_baseEntity);
			}
		}
		else if(collider->m_collisionObject->IsTaggedAs("Brick"))
		{
			BrickControl* brickControl = static_cast<BrickControl*>(collider->m_collisionObject->GetComponent(CompType::COMP_BRICKCONTROL));
			brickControl->m_health -= m_damage;

			EntitiesSystem::GetInstance()->Remove(m_baseEntity);
		}
		else if(collider->m_collisionObject->IsTaggedAs("Rock"))
		{
			EntitiesSystem::GetInstance()->Remove(m_baseEntity);
		}
		else if(collider->m_collisionObject->IsTaggedAs("ScreenCollider"))
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
			m_defense = 10.0f;
			break;
		case Tank::TANK_DEFENSE:
			m_health = 60.0f;
			m_defense = 15.0f;
			break;
		case Tank::TANK_BOLT:
			m_health = 80.0f;
			m_defense = 5.0f;
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
		EntitiesSystem::GetInstance()->Remove(m_baseEntity);
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

	for(int i = 0; i < 3; i++)
	{
		m_teamRedCount[i] = Map::GetInstance()->m_teamRed[i];
		m_teamBlueCount[i] = Map::GetInstance()->m_teamBlue[i];
	}
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

	for(int i = 0; i < 4; i++)
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