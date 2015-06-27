#include "stdafx.h"
#include <ctime>

#include "Map.h"
#include "Entity.h"
#include "EntitiesSystem.h"

#include "Quadtree.h"
#include "Scripts.h"

#include "Components.h"

using namespace stdio_fw;

///////////////////////////////////////////
// Component
Component::Component()
{
	m_type = CompType::COMP_UNKNOWN;
}

Component::~Component()
{
	m_baseEntity = NULL;
}
///////////////////////////////////////////


///////////////////////////////////////////
// Transform
Transform::Transform(Vec3 _position, Vec3 _rotation, Vec3 _scale)
{
	m_type = CompType::COMP_TRANSFORM;

	m_position = _position;
	m_rotation = _rotation;
	m_scale = _scale;

	m_parent = NULL;
	m_childCount = 0;
}

Transform::~Transform()
{

}

void Transform::Release()
{
	while(!m_childList.empty())
	{
		if(m_childList.back()->m_baseEntity)
		{
			for(int i = 0; i < EntitiesSystem::GetInstance()->m_entitiesList.size(); i++)
			{
				if(m_childList.back()->m_baseEntity == EntitiesSystem::GetInstance()->m_entitiesList[i])
				{
					m_childList.back()->m_baseEntity->Release();
					SAFE_DEL(EntitiesSystem::GetInstance()->m_entitiesList[i]);

					break;
				}
			}
		}
		m_childList.pop_back();
	}

	m_parent = NULL;
}

void Transform::Update()
{

}

void Transform::SetParent(Transform* _parent)
{
	m_parent = _parent;
	m_parent->m_childCount++;
	m_parent->m_childList.push_back(this);
}

bool Transform::IsMiddle(Transform* a, Transform* b)
{
	Vec3 posA = a->m_position;
	Vec3 posB = b->m_position;

	if((posA.x < m_position.x && m_position.x < posB.x) || (posA.x > m_position.x && m_position.x > posB.x))
	{
		if(abs(posA.y - posB.y) <= 160 && abs(posA.y - m_position.y) <= 96 && abs(posB.y - m_position.y) <= 96)
			return true;
	}
	if((posA.y < m_position.y && m_position.y < posB.y) || (posA.y > m_position.y && m_position.y > posB.y))
	{
		if(abs(posA.x - posB.x) <= 160 && abs(posA.x - m_position.x) <= 96 && abs(posB.x - m_position.x) <= 96)
			return true;
	}

	return false;
}
///////////////////////////////////////////


///////////////////////////////////////////
// Renderer
Renderer::Renderer(Image* _sprite)
{
	m_type = CompType::COMP_RENDERER;

	m_sprite = _sprite;
}

Renderer::~Renderer()
{

}

void Renderer::Release()
{
	m_sprite = NULL;
}

void Renderer::Update()
{

}
///////////////////////////////////////////


///////////////////////////////////////////
// Rigidbody2D
Rigidbody2D::Rigidbody2D()
{
	m_type = CompType::COMP_RIGIDBODY2D;
}

Rigidbody2D::~Rigidbody2D()
{

}

void Rigidbody2D::Release()
{

}

void Rigidbody2D::Update()
{

}
///////////////////////////////////////////


///////////////////////////////////////////
// Collider2D
Collider2D::Collider2D(Rect _bound)
{
	m_type = CompType::COMP_COLLIDER2D;
	m_bound = _bound;

	m_collisionObject = NULL;
}

Collider2D::~Collider2D()
{

}

void Collider2D::Release()
{
	m_collisionObject = NULL;
}

void Collider2D::Update()
{
	m_bound.x = m_baseEntity->m_transform->m_position.x - m_bound.width / 2;
	m_bound.y = m_baseEntity->m_transform->m_position.y - m_bound.height / 2;

	if(!m_baseEntity->IsTaggedAs(TAG_BULLET) && !m_baseEntity->IsTaggedAs(TAG_TANK))
		return;

	std::vector<Entity*> detectEntityList = EntitiesSystem::GetInstance()->m_quadtree->Retrieve(m_baseEntity);
	for(int i = 0; i < detectEntityList.size(); i++)
	{
		if(CheckAABB(detectEntityList[i]->m_collider2d))
		{
			m_collisionObject = detectEntityList[i];

			if(m_baseEntity->IsTaggedAs(TAG_TANK) &&
				(m_collisionObject->IsTaggedAs(TAG_BRICK) || m_collisionObject->IsTaggedAs(TAG_ROCK) ||
				m_collisionObject->IsTaggedAs(TAG_OCEAN) || m_collisionObject->IsTaggedAs(TAG_SCREENCOLLIDER)))
			{
				TankController* tankController = static_cast<TankController*>(m_baseEntity->GetComponent(CompType::COMP_TANKCONTROLLER));
				tankController->m_lockDirection = tankController->m_direction;

				if(tankController->m_direction == Direction::DIR_UP)
				{
					m_baseEntity->m_transform->m_position.y = m_collisionObject->m_transform->m_position.y 
						+ m_collisionObject->m_collider2d->m_bound.height / 2 + m_baseEntity->m_collider2d->m_bound.height / 2;
				}
				else if(tankController->m_direction == Direction::DIR_DOWN)
				{
					m_baseEntity->m_transform->m_position.y = m_collisionObject->m_transform->m_position.y
						- m_collisionObject->m_collider2d->m_bound.height / 2 - m_baseEntity->m_collider2d->m_bound.height / 2;
				}
				else if(tankController->m_direction == Direction::DIR_LEFT)
				{
					m_baseEntity->m_transform->m_position.x = m_collisionObject->m_transform->m_position.x
						+ m_collisionObject->m_collider2d->m_bound.width / 2 + m_baseEntity->m_collider2d->m_bound.width / 2;
				}
				else if(tankController->m_direction == Direction::DIR_RIGHT)
				{
					m_baseEntity->m_transform->m_position.x = m_collisionObject->m_transform->m_position.x
						- m_collisionObject->m_collider2d->m_bound.width / 2 - m_baseEntity->m_collider2d->m_bound.width / 2;
				}

				m_bound.x = m_baseEntity->m_transform->m_position.x - m_bound.width / 2;
				m_bound.y = m_baseEntity->m_transform->m_position.y - m_bound.height / 2;
			}

			if(m_baseEntity->IsTaggedAs(TAG_TANK) && m_collisionObject->IsTaggedAs(TAG_ITEM))
			{
				ItemManager* itemManager = static_cast<ItemManager*>(m_collisionObject->GetComponent(CompType::COMP_ITEMMANAGER));
				switch(itemManager->m_item)
				{
					case Item::ITEM_HP:
						static_cast<HealthControl*>(m_baseEntity->GetComponent(CompType::COMP_HEALTHCONTROL))->m_health += itemManager->m_plusHP;
						break;
					case Item::ITEM_SPEED:
						static_cast<TankController*>(m_baseEntity->GetComponent(CompType::COMP_TANKCONTROLLER))->m_speed += itemManager->m_plusSpeed;
						break;
					case Item::ITEM_DAMAGE:
						static_cast<TankController*>(m_baseEntity->GetComponent(CompType::COMP_TANKCONTROLLER))->m_damage += itemManager->m_plusDamage;
						break;
					case Item::ITEM_TANK:
					{
						TankController* tankController = static_cast<TankController*>(m_baseEntity->GetComponent(CompType::COMP_TANKCONTROLLER));
						if(tankController->m_team == Team::TEAM_RED)
							Map::GetInstance()->m_teamRed[tankController->m_tank]++;
						else
							Map::GetInstance()->m_teamBlue[tankController->m_tank]++;
					}
					break;
					case Item::ITEM_INVISIBLE:
						static_cast<TankController*>(m_baseEntity->GetComponent(CompType::COMP_TANKCONTROLLER))->m_invisible = true;
						static_cast<TankController*>(m_baseEntity->GetComponent(CompType::COMP_TANKCONTROLLER))->m_timer = clock();
						static_cast<TankController*>(m_baseEntity->GetComponent(CompType::COMP_TANKCONTROLLER))->m_expTime = 10.0f;
						break;
					case Item::ITEM_BULLET:
						static_cast<TankController*>(m_baseEntity->GetComponent(CompType::COMP_TANKCONTROLLER))->m_shootPerSec += 2;
						break;
				}
				static_cast<TankController*>(m_baseEntity->GetComponent(CompType::COMP_TANKCONTROLLER))->CalculateHeuristic();

				EntitiesSystem::GetInstance()->Remove(m_collisionObject);
				m_collisionObject = NULL;
			}

			detectEntityList.clear();
			return;
		}
	}
}

bool Collider2D::CheckAABB(Collider2D* _collider2d)
{
	return !(m_bound.x + m_bound.width < _collider2d->m_bound.x
		|| m_bound.y + m_bound.height < _collider2d->m_bound.y
		|| m_bound.x > _collider2d->m_bound.x + _collider2d->m_bound.width
		|| m_bound.y > _collider2d->m_bound.y + _collider2d->m_bound.height);
}
///////////////////////////////////////////


///////////////////////////////////////////
// Animator
Animator::Animator()
{
	m_type = CompType::COMP_ANIMATOR;
}

Animator::~Animator()
{

}

void Animator::Release()
{
	m_frameList.clear();
	m_frameTime.clear();
}

void Animator::Update()
{

}

void Animator::SetFrameList(int _count, ...)
{
	va_list ap;
	va_start(ap, _count);

	for(int i = 0; i < _count; i++)
	{
		Image* image = va_arg(ap, Image*);
		m_frameList.push_back(image);

		m_frameTime.push_back(-1);
	}

	va_end(ap);
}

void Animator::SetFrameTime(int _count, ...)
{

}
///////////////////////////////////////////


///////////////////////////////////////////
// UIText
UIText::UIText()
{
	m_type = CompType::COMP_UITEXT;
	m_fontSize = FNT_SIZE_DESIGN;
}

UIText::~UIText()
{

}

void UIText::Release()
{

}


void UIText::Update()
{

}
///////////////////////////////////////////