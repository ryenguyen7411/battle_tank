#include "stdafx.h"
#include "Entity.h"
#include "EntitiesSystem.h"
#include "Quadtree.h"
#include <ctime>
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
					EntitiesSystem::GetInstance()->m_entitiesList[i] = NULL;

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

	if(!m_baseEntity->IsTaggedAs("Bullet") && !m_baseEntity->IsTaggedAs("Tank"))
		return;

	std::vector<Entity*> detectEntityList = EntitiesSystem::GetInstance()->m_quadtree->Retrieve(m_baseEntity);
	for(int i = 0; i < detectEntityList.size(); i++)
	{
		std::vector<Component*> collider2dList = detectEntityList[i]->GetComponents(CompType::COMP_COLLIDER2D);
		for(int j = 0; j < collider2dList.size(); j++)
		{
			if(CheckAABB(static_cast<Collider2D*>(collider2dList[j])))
			{
				m_collisionObject = detectEntityList[i];
				
				if(m_baseEntity->IsTaggedAs("Tank") && (m_collisionObject->IsTaggedAs("Tank") || m_collisionObject->IsTaggedAs("Brick")))
				{
					TankController* tankController = static_cast<TankController*>(m_baseEntity->GetComponent(CompType::COMP_TANKCONTROLLER));
					tankController->m_lockDirection = tankController->m_direction;
				}

				detectEntityList.clear();
				return;
			}
		}
	}

	detectEntityList.clear();
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