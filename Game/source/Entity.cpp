#include "stdafx.h"
#include "Components.h"

#include "Entity.h"

Entity::Entity()
{
	strcpy(m_tag, "Untagged");

	m_transform = new Transform();
	m_componentList.push_back(static_cast<Component*>(m_transform));

	m_renderer = NULL;
	m_rigidbody2d = NULL;
}

Entity::~Entity()
{
	m_transform = NULL;
	m_renderer = NULL;
	m_rigidbody2d = NULL;

	while(!m_componentList.empty())
	{
		delete m_componentList.back();
		m_componentList.pop_back();
	}
}

void Entity::AddComponent(Component* _component)
{
	if(_component->m_type == CompType::COMP_TRANSFORM)
	{
		printf("Can't add Transform because there's already have a Transform in this entity\n");
		return;
	}
	if(_component->m_type == CompType::COMP_RENDERER)
	{
		if(!m_renderer)
			m_renderer = dynamic_cast<Renderer*>(_component);
		else
		{
			printf("Can't add Renderer because there's already have a Renderer in this entity\n");
			return;
		}
	}
	else if(_component->m_type == CompType::COMP_RIGIDBODY2D)
	{
		if(!m_rigidbody2d)
			m_rigidbody2d = dynamic_cast<Rigidbody2D*>(_component);
		else
		{
			printf("Can't add Rigidbody2D because there's already have a Rigidbody2D in this entity\n");
			return;
		}
	}
	else if(_component->m_type == CompType::COMP_ANIMATOR)
	{
		if(!m_animator)
			m_animator = dynamic_cast<Animator*>(_component);
		else
		{
			printf("Can't add Animator because there's already have a Animator in this entity\n");
			return;
		}
	}

	m_componentList.push_back(_component);
	_component->m_parent = this;
}

Component* Entity::GetComponent(CompType _type)
{
	if(_type == CompType::COMP_TRANSFORM)
		return m_transform;
	if(_type == CompType::COMP_RENDERER)
		return m_renderer;
	if(_type == CompType::COMP_RIGIDBODY2D)
		return m_rigidbody2d;
	if(_type == CompType::COMP_ANIMATOR)
		return m_animator;

	for(int i = 0; i < m_componentList.size(); i++)
	{
		if(m_componentList[i]->m_type == _type)
			return m_componentList[i];
	}

	return NULL;
}

std::vector<Component*> Entity::GetComponents(CompType _type)
{
	std::vector<Component*> returnList;

	for(int i = 0; i < m_componentList.size(); i++)
	{
		if(m_componentList[i]->m_type == _type)
			returnList.push_back(m_componentList[i]);
	}

	return returnList;
}

void Entity::SetTag(const char* _tag)
{
	strcpy(m_tag, _tag);
}

bool Entity::IsTaggedAs(const char* _tag)
{
	if(strcmp(m_tag, _tag) == 0)
		return true;
	return false;
}

void Entity::Update()
{
	for(int i = 0; i < m_componentList.size(); i++)
	{
		m_componentList[i]->Update();
	}
}

void Entity::Draw(Graphics* g)
{
	Rect rect;
	rect.width = m_renderer->m_bound.width;
	rect.height = m_renderer->m_bound.height;
	rect.x = m_transform->m_position.x - rect.width / 2;
	rect.y = m_transform->m_position.y - rect.height / 2;

	g->drawImage(m_renderer->m_sprite, rect);
}