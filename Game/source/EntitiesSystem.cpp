#include "stdafx.h"
#include "Quadtree.h"
#include "Entity.h"

#include "EntitiesSystem.h"

EntitiesSystem::EntitiesSystem()
{
	
}

EntitiesSystem::~EntitiesSystem()
{

}

void EntitiesSystem::Remove(Entity* _entity)
{
	for(int i = 0; i < m_entitiesList.size(); i++)
	{
		if(m_entitiesList[i] == _entity)
		{
			delete m_entitiesList[i];
			m_entitiesList[i] = m_entitiesList.back();
			m_entitiesList.pop_back();
			break;
		}
	}
}

Quadtree* EntitiesSystem::UpdateQuadtree()
{
	if(m_quadtree)
		m_quadtree->Clear();

	m_quadtree = new Quadtree(1, Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

	for(int i = 0; i < m_entitiesList.size(); i++)
	{
		m_quadtree->Insert(m_entitiesList[i]);
	}

	return m_quadtree;
}