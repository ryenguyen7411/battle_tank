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
	{
		if(m_entitiesList.back())
		{
			if(m_entitiesList.back()->m_transform->m_parent)
			{
				for(int i = 0; i < m_entitiesList.back()->m_transform->m_parent->m_childCount; i++)
				{
					if(m_entitiesList.back()->m_transform->m_parent->m_childList[i] == m_entitiesList.back()->m_transform)
					{
						m_entitiesList.back()->m_transform->m_parent->m_childList[i] = m_entitiesList.back()->m_transform->m_parent->m_childList.back();
						m_entitiesList.back()->m_transform->m_parent->m_childList.pop_back();
						m_entitiesList.back()->m_transform->m_parent->m_childCount--;
					}
				}
			}
			m_entitiesList.back()->Release();
			SAFE_DEL(m_entitiesList.back());
		}
		m_entitiesList.pop_back();
	}
	
	//for(int i = 0; i < m_entitiesList.size(); i++)
	//{
	//	SAFE_DEL(m_entitiesList[i]);
	//}

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

			break;
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