#include "stdafx.h"

#include "Entity.h"

#include "Components.h"
#include "Scripts.h"

#include "Quadtree.h"

Quadtree::Quadtree(int _level, Rect _region)
{
	m_level = _level;
	m_region = _region;
}

Quadtree::~Quadtree()
{
	
}

bool Quadtree::IsContain(Entity* _entity)
{
	for(int i = 0; i < _entity->m_componentList.size(); i++)
	{
		if(_entity->m_componentList[i]->m_type == COMP_COLLIDER2D)
		{
			Rect bound = static_cast<Collider2D*>(_entity->m_componentList[i])->m_bound;

			if(!(bound.x + bound.width < m_region.x || bound.y + bound.height < m_region.y
				|| bound.x > m_region.x + m_region.width || bound.y > m_region.y + m_region.height))
				return true;
		}
	}

	return false;
}

void Quadtree::Split()
{
	m_subRegion[0] = new Quadtree(m_level + 1, 
									Rect(m_region.x, m_region.y, m_region.width / 2, m_region.height / 2));
	m_subRegion[1] = new Quadtree(m_level + 1, 
									Rect(m_region.x + m_region.width / 2, m_region.y, m_region.width / 2, m_region.height / 2));
	m_subRegion[2] = new Quadtree(m_level + 1, 
									Rect(m_region.x, m_region.y + m_region.height / 2, m_region.width / 2, m_region.height / 2));
	m_subRegion[3] = new Quadtree(m_level + 1, 
									Rect(m_region.x + m_region.width / 2, m_region.y + m_region.height / 2, m_region.width / 2, m_region.height / 2));
}

void Quadtree::Clear()
{
	for(int i = 0; i < 4; i++)
	{
 		if(m_subRegion[i] != NULL)
		{
			m_subRegion[i]->Clear();
			delete m_subRegion[i];
		}
	}

	m_entityList.clear();
}

void Quadtree::Insert(Entity* _entity) 
{
	if(!_entity)
		return;

	if(m_subRegion[0])
	{
		for(int i = 0; i < 4; i++)
		{
			if(m_subRegion[i]->IsContain(_entity))
				m_subRegion[i]->Insert(_entity);
		}
	}
	else
	{
		if(IsContain(_entity))
			m_entityList.push_back(_entity);
	}

	if(m_entityList.size() > MAX_ENTITY && m_level < MAX_LEVEL)
	{
		Split();

		while(!m_entityList.empty())
		{
			for(int i = 0; i < 4; i++)
			{
				if(m_subRegion[i]->IsContain(m_entityList.back()))
					m_subRegion[i]->Insert(m_entityList.back());
			}

			m_entityList.pop_back();
		}
	}
}

std::vector<Entity*> Quadtree::Retrieve(Entity* _entity)
{
	std::vector<Entity*> returnList;

	if(m_subRegion[0])
	{
		for(int i = 0; i < 4; i++)
		{
			if(m_subRegion[i]->IsContain(_entity))
			{
				std::vector<Entity*> list = m_subRegion[i]->Retrieve(_entity);

				for(int j = 0; j < list.size(); j++)
					returnList.push_back(list[j]);
			}
		}
	}
	else if(IsContain(_entity))
	{
		for(int i = 0; i < m_entityList.size(); i++)
		{
			if(m_entityList[i] != _entity)
			{
				if(m_entityList[i]->IsTaggedAs(TAG_TANK) || m_entityList[i]->IsTaggedAs(TAG_BULLET) || m_entityList[i]->IsTaggedAs(TAG_BRICK)
					|| m_entityList[i]->IsTaggedAs(TAG_CONCRETE) || m_entityList[i]->IsTaggedAs(TAG_OCEAN) || m_entityList[i]->IsTaggedAs(TAG_ITEM))
					returnList.push_back(m_entityList[i]);
			}
		}
	}

	return returnList;
}