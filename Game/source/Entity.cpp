#include "stdafx.h"

#include "Components.h"

#include "Entity.h"

Entity::Entity()
{
	m_transform = NULL;
	m_renderer = NULL;
}

Entity::~Entity()
{

}

void Entity::AddComponent(Component* _component)
{
	if(_component->m_type == CompType::COMP_TRANSFORM && m_transform == NULL)
	{
		m_transform = dynamic_cast<Transform*>(_component);
		m_componentList.push_back(_component);
	}
	else if(_component->m_type == CompType::COMP_RENDERER && m_renderer == NULL)
	{
		m_renderer = dynamic_cast<Renderer*>(_component);
		m_componentList.push_back(_component);
	}
}

Component* Entity::GetComponent(CompType _type)
{
	if(_type == CompType::COMP_TRANSFORM)
		return m_transform;
	if(_type == CompType::COMP_RENDERER)
		return m_renderer;
}

std::vector<Component*> Entity::GetComponents(CompType _type)
{
	std::vector<Component*> res;

	for(int i = 0; i < m_componentList.size(); i++)
	{
		if(m_componentList[i]->m_type == _type)
			res.push_back(m_componentList[i]);
	}

	return res;
}

void Entity::Draw(Graphics* g)
{
	g->drawImage(m_renderer->m_sprite, m_transform->m_position.x, m_transform->m_position.y);
}