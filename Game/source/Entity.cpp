#include "stdafx.h"

#include "ResourcesManager.h"

#include "Components.h"
#include "Scripts.h"

#include "Entity.h"

Entity::Entity()
{
	strcpy(m_tag, "Untagged");

	m_transform = new Transform();
	m_transform->m_baseEntity = this;
	m_componentList.push_back(static_cast<Component*>(m_transform));

	m_renderer = NULL;
	m_rigidbody2d = NULL;
	m_animator = NULL;
	m_collider2d = NULL;
}

Entity::~Entity()
{
	
}

void Entity::Release()
{
	while(!m_componentList.empty())
	{
		m_componentList.back()->Release();
		SAFE_DEL(m_componentList.back());

		m_componentList.pop_back();
	}

	m_transform = NULL;
	m_renderer = NULL;
	m_rigidbody2d = NULL;
	m_animator = NULL;
	m_collider2d = NULL;
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
	else if(_component->m_type == CompType::COMP_COLLIDER2D)
	{
		if(!m_collider2d)
			m_collider2d = dynamic_cast<Collider2D*>(_component);
	}

	m_componentList.push_back(_component);
	_component->m_baseEntity = this;
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
	if(m_renderer)
	{
		Rect rect;
		rect.width = m_renderer->m_sprite->getWidth();
		rect.height = m_renderer->m_sprite->getHeight();
		rect.x = m_transform->m_position.x - rect.width / 2;
		rect.y = m_transform->m_position.y - rect.height / 2;

		Transform* base = m_transform->m_parent;
		while(base)
		{
			rect.x += m_transform->m_parent->m_position.x;
			rect.y += m_transform->m_parent->m_position.y;

			base = base->m_parent;
		}

		g->drawImage(m_renderer->m_sprite, rect);
	}
	
	std::vector<Component*> uiTexts = GetComponents(CompType::COMP_UITEXT);
	for(int i = 0; i < uiTexts.size(); i++)
	{
		UIText* uiText = static_cast<UIText*>(uiTexts[i]);

		Vec3 drawPosition = m_transform->m_position;
		Transform* base = m_transform->m_parent;
		while(base)
		{
			drawPosition.x += base->m_position.x;
			drawPosition.y += base->m_position.y;

			base = base->m_parent;
		}

		if(uiText->m_anchor == Anchor::ANCHOR_RIGHT)
		{
			for(int i = 0; i < strlen(uiText->m_text); i++)
			{
				FontChar fontChar = ResourcesManager::GetInstance()->m_fontChar[uiText->m_text[i]];
				drawPosition.x -= fontChar.m_xAdvance * uiText->m_fontSize;
			}
		}
		else if(uiText->m_anchor == Anchor::ANCHOR_CENTER)
		{
			for(int i = 0; i < strlen(uiText->m_text); i++)
			{
				FontChar fontChar = ResourcesManager::GetInstance()->m_fontChar[uiText->m_text[i]];
				drawPosition.x -= fontChar.m_xAdvance / 2 * uiText->m_fontSize;
			}
		}

		for(int i = 0; i < strlen(uiText->m_text); i++)
		{
			FontChar fontChar = ResourcesManager::GetInstance()->m_fontChar[uiText->m_text[i]];
			Rect dest = Rect(drawPosition.x + fontChar.m_offset.x * uiText->m_fontSize, drawPosition.y + fontChar.m_offset.y * uiText->m_fontSize,
				fontChar.m_rect.width * uiText->m_fontSize, fontChar.m_rect.height * uiText->m_fontSize);

			g->drawRegion(uiText->m_font, dest, fontChar.m_rect);

			drawPosition.x += fontChar.m_xAdvance * uiText->m_fontSize;
		}
	}
}