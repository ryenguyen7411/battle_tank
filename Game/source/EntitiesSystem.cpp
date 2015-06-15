#include "stdafx.h"
#include "Quadtree.h"
#include "Entity.h"
#include "Components.h"

#include "EntitiesSystem.h"

EntitiesSystem::EntitiesSystem()
{
	
}

EntitiesSystem::~EntitiesSystem()
{
	
}

void EntitiesSystem::Release()
{
	while(!m_entitiesList.empty())
		Remove(m_entitiesList.back());
	
	if(m_quadtree)
	{
		m_quadtree->Clear();
		SAFE_DEL(m_quadtree);
	}

	delete s_instance;
}

void EntitiesSystem::Remove(Entity* _entity)
{
	for(int i = 0; i < m_entitiesList.size(); i++)
	{
		if(m_entitiesList[i] == _entity)
		{
			m_entitiesList[i]->Release();
			SAFE_DEL(m_entitiesList[i]);

			m_entitiesList[i] = m_entitiesList.back();
			m_entitiesList.pop_back();

			break;
		}
	}

	for(int i = 0; i < m_entitiesList.size(); i++)
	{
		if(m_entitiesList[i] == NULL)
		{
			m_entitiesList[i] = m_entitiesList.back();
			m_entitiesList.pop_back();
		}
	}
}

Quadtree* EntitiesSystem::UpdateQuadtree()
{
	if(m_quadtree)
	{
		m_quadtree->Clear();
		SAFE_DEL(m_quadtree);
	}

	m_quadtree = new Quadtree(1, Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

	for(int i = 0; i < m_entitiesList.size(); i++)
	{
		m_quadtree->Insert(m_entitiesList[i]);
	}

	return m_quadtree;
}