#include "stdafx.h"
#include "Factory.h"
#include "Map.h"

#include "Entity.h"
#include "EntitiesSystem.h"

#include <ctime>
#include "Scripts.h"

#pragma region TankController
TankController::TankController(Tank _tankType)
{
	m_type = CompType::COMP_TANKCONTROLLER;

	m_tank = _tankType;
	m_bullet = Bullet::BULLET_NORMAL;

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

	if(m_control == Control::CTRL_AUTO)
	{
		m_stateMachine = StateMachine(m_baseEntity);
		//m_stateMachine.ChangeState()
	}
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
			if(entity && (entity->IsTaggedAs("Tank") || entity->IsTaggedAs("MapPart")))
				break;
		}

		if(GetAsyncKeyState(VK_UP))
		{
			if(m_lockDirection != Direction::DIR_UP)
			{
				if(m_lockDirection == Direction::DIR_LEFT)
					m_baseEntity->m_transform->m_position.x = entity->m_transform->m_position.x + 33;
				if(m_lockDirection == Direction::DIR_RIGHT)
					m_baseEntity->m_transform->m_position.x = entity->m_transform->m_position.x - 33;

				m_baseEntity->m_transform->m_position.y -= m_speed;
			}
			m_direction = Direction::DIR_UP;
			m_lockDirection = Direction::DIR_NONE;

			m_baseEntity->m_animator->m_currentFrame = 0;
			m_baseEntity->m_renderer->m_sprite = m_baseEntity->m_animator->m_frameList[m_baseEntity->m_animator->m_currentFrame];
			m_baseEntity->m_renderer->UpdateBound();
		}
		else if(GetAsyncKeyState(VK_DOWN))
		{
			if(m_lockDirection != Direction::DIR_DOWN)
			{
				if(m_lockDirection == Direction::DIR_LEFT)
					m_baseEntity->m_transform->m_position.x = entity->m_transform->m_position.x + 33;
				if(m_lockDirection == Direction::DIR_RIGHT)
					m_baseEntity->m_transform->m_position.x = entity->m_transform->m_position.x - 33;

				m_baseEntity->m_transform->m_position.y += m_speed;
			}
			m_direction = Direction::DIR_DOWN;
			m_lockDirection = Direction::DIR_NONE;

			m_baseEntity->m_animator->m_currentFrame = 1;
			m_baseEntity->m_renderer->m_sprite = m_baseEntity->m_animator->m_frameList[m_baseEntity->m_animator->m_currentFrame];
			m_baseEntity->m_renderer->UpdateBound();
		}
		else if(GetAsyncKeyState(VK_LEFT))
		{
			if(m_lockDirection != Direction::DIR_LEFT)
			{
				if(m_lockDirection == Direction::DIR_UP)
					m_baseEntity->m_transform->m_position.y = entity->m_transform->m_position.y + 33;
				if(m_lockDirection == Direction::DIR_DOWN)
					m_baseEntity->m_transform->m_position.y = entity->m_transform->m_position.y - 33;

				m_baseEntity->m_transform->m_position.x -= m_speed;
			}
			m_direction = Direction::DIR_LEFT;
			m_lockDirection = Direction::DIR_NONE;

			m_baseEntity->m_animator->m_currentFrame = 2;
			m_baseEntity->m_renderer->m_sprite = m_baseEntity->m_animator->m_frameList[m_baseEntity->m_animator->m_currentFrame];
			m_baseEntity->m_renderer->UpdateBound();
		}
		else if(GetAsyncKeyState(VK_RIGHT))
		{
			if(m_lockDirection != Direction::DIR_RIGHT)
			{
				if(m_lockDirection == Direction::DIR_UP)
					m_baseEntity->m_transform->m_position.y = entity->m_transform->m_position.y + 33;
				if(m_lockDirection == Direction::DIR_DOWN)
					m_baseEntity->m_transform->m_position.y = entity->m_transform->m_position.y - 33;

				m_baseEntity->m_transform->m_position.x += m_speed;
			}
			m_direction = Direction::DIR_RIGHT;
			m_lockDirection = Direction::DIR_NONE;

			m_baseEntity->m_animator->m_currentFrame = 3;
			m_baseEntity->m_renderer->m_sprite = m_baseEntity->m_animator->m_frameList[m_baseEntity->m_animator->m_currentFrame];
			m_baseEntity->m_renderer->UpdateBound();
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
			EntitiesSystem::GetInstance()->Remove(m_baseEntity);
	}
	else if(m_direction == Direction::DIR_DOWN)
	{
		m_baseEntity->m_transform->m_position.y += m_speed;

		if(m_baseEntity->m_transform->m_position.y - m_savePosition.y >= m_range)
			EntitiesSystem::GetInstance()->Remove(m_baseEntity);
	}
	else if(m_direction == Direction::DIR_LEFT)
	{
		m_baseEntity->m_transform->m_position.x -= m_speed;

		if(m_savePosition.x - m_baseEntity->m_transform->m_position.x >= m_range)
			EntitiesSystem::GetInstance()->Remove(m_baseEntity);
	}
	else if(m_direction == Direction::DIR_RIGHT)
	{
		m_baseEntity->m_transform->m_position.x += m_speed;

		if(m_baseEntity->m_transform->m_position.x - m_savePosition.x >= m_range)
			EntitiesSystem::GetInstance()->Remove(m_baseEntity);
	}
}
#pragma endregion


#pragma region CheckCollideWithBullet
CheckCollideWithBullet::CheckCollideWithBullet()
{
	m_type = CompType::COMP_CHECKCOLLIDEWITHBULET;
}

CheckCollideWithBullet:: ~CheckCollideWithBullet()
{

}

void CheckCollideWithBullet::Release()
{

}

void CheckCollideWithBullet::Update()
{

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
	std::vector<Transform*> childList = m_baseEntity->m_transform->m_childList;
	for(int i = 0; i < childList.size(); i++)
	{
		if(childList[i]->m_baseEntity->IsTaggedAs("HP"))
		{
			char* uiText = static_cast<UIText*>(childList[i]->m_baseEntity->GetComponent(CompType::COMP_UITEXT))->m_text;
			uiText[0] = '\0';
			strcat(uiText, "HP = ");
			strcat(uiText, convertToString(m_health));

			break;
		}
	}

	std::vector<Component*> collider2dList = m_baseEntity->GetComponents(CompType::COMP_COLLIDER2D);
	Entity* bullet = NULL;

	for(int i = 0; i < collider2dList.size(); i++)
	{
		Entity* bullet = static_cast<Collider2D*>(collider2dList[i])->m_collisionObject;
		if(bullet && bullet->IsTaggedAs("Bullet"))
		{
			BulletController* bulletController = static_cast<BulletController*>(bullet->GetComponent(CompType::COMP_BULLETCONTROLLER));

			if(static_cast<TankController*>(m_baseEntity->GetComponent(CompType::COMP_TANKCONTROLLER))->m_team != bulletController->m_team)
			{
				m_health -= (bulletController->m_damage - m_defense);
				EntitiesSystem::GetInstance()->Remove(bullet);
			}

			break;
		}
	}

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
	std::vector<Component*> collider2dList = m_baseEntity->GetComponents(CompType::COMP_COLLIDER2D);
	Entity* bullet = NULL;

	for(int i = 0; i < collider2dList.size(); i++)
	{
		Entity* x = static_cast<Collider2D*>(collider2dList[i])->m_collisionObject;
		if(x && x->IsTaggedAs("Bullet"))
		{
			bullet = x;
			BulletController* bulletController = static_cast<BulletController*>(bullet->GetComponent(CompType::COMP_BULLETCONTROLLER));
			m_health -= (bulletController->m_damage);
			EntitiesSystem::GetInstance()->Remove(bullet);

			break;
		}
	}

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