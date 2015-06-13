#include "stdafx.h"
#include "ResourcesManager.h"

ResourcesManager::ResourcesManager()
{

}

ResourcesManager::~ResourcesManager()
{

}

void ResourcesManager::LoadResources()
{
	m_tank1[0] = new Image(SPR_TANK_1_UP);
	m_tank1[0]->loadImage();
	m_tank1[1] = new Image(SPR_TANK_1_DOWN);
	m_tank1[1]->loadImage();
	m_tank1[2] = new Image(SPR_TANK_1_LEFT);
	m_tank1[2]->loadImage();
	m_tank1[3] = new Image(SPR_TANK_1_RIGHT);
	m_tank1[3]->loadImage();

	m_bullet = new Image(SPR_BULLET_NORMAL);
	m_bullet->loadImage();
}

void ResourcesManager::Release()
{
	for(int i = 0; i < 4; i++)
	{
		m_tank1[i]->unloadImage();
		delete m_tank1[i];
	}

	m_bullet->unloadImage();
	delete m_bullet;

	delete s_instance;
}