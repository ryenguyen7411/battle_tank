#include "stdafx.h"

#include <ctime>

#include "ResourcesManager.h"
#include "Map.h"
#include "Factory.h"
#include "EntitiesSystem.h"

#include "Entity.h"
#include "Components.h"

#include "State.h"
#include "TankAI.h"

#include "Game.h"

Game::Game()
{
	
}

Game::~Game()
{

}

ErrorCode Game::init(int screenW, int screenH, const char* title)
{
	ErrorCode errCode = Application::init(screenW, screenH, title);

	srand((unsigned)time(NULL));
	ResourcesManager::GetInstance()->LoadResources();
	Map::GetInstance()->ChangeMap(MAP_1);

	Factory::GetInstance()->CreateManager(Team::TEAM_RED);
	Factory::GetInstance()->CreateManager(Team::TEAM_BLUE);

	m_state = GameState::STATE_PLAY;
	m_itemTimer = clock();
	
	return errCode;
}


// EntitiesList will update size after all entities updated
// NULL entity will be remove
void Game::update(float deltaTime)
{
	switch(m_state)
	{
		case GameState::STATE_PLAY:
		{
			EntitiesSystem::GetInstance()->UpdateQuadtree();
			std::vector<Entity*>* entitiesList = &EntitiesSystem::GetInstance()->m_entitiesList;
			for(int i = 0; i < entitiesList->size(); i++)
			{
				if(entitiesList->at(i))
					entitiesList->at(i)->Update();
			}

			for(int i = 0; i < entitiesList->size(); i++)
			{
				if(!entitiesList->at(i))
				{
					entitiesList->at(i) = entitiesList->back();
					entitiesList->pop_back();
				}
			}

			if(1.0f * (clock() - m_itemTimer) / CLOCKS_PER_SEC >= ITEM_TIME)
			{
				Factory::GetInstance()->CreateItem(Item(rand() % Item::ITEM_COUNT));
				m_itemTimer = clock();
			}
		}
			break;
		case GameState::STATE_WIN:

			break;
		case GameState::STATE_GAME_OVER:
			break;
	}
	

	/////////////////////////////////////////////////
	//Coder: Rye
	//Purpose: manage FPS
	if(1000.0f / FPS > deltaTime)
		Sleep(1000.0f / FPS - deltaTime);
}

void Game::render(Graphics* g)
{
	g->cleanScreen();
	g->setClearColor(WHITE);

	std::vector<Entity*> entitiesList = EntitiesSystem::GetInstance()->m_entitiesList;
	for(int i = 0; i < entitiesList.size(); i++)
	{
		if(entitiesList[i])
			entitiesList[i]->Draw(g);
	}

	Map::GetInstance()->Draw(g);	// Bullet will be behind map - Fix later

	switch(m_state)
	{
		case GameState::STATE_WIN:
			break;
		case GameState::STATE_GAME_OVER:
			break;
	}
}

void Game::exit()
{
	Factory::GetInstance()->Release();
	Factory::ReleaseInstance();

	EntitiesSystem::GetInstance()->Release();
	EntitiesSystem::ReleaseInstance();

	ResourcesManager::GetInstance()->Release();
	ResourcesManager::ReleaseInstance();

	Map::GetInstance()->Release();
	Map::ReleaseInstance();

	Roaming::ReleaseInstance();
	Fighting::ReleaseInstance();
	Chasing::ReleaseInstance();
	Fleeing::ReleaseInstance();
}

void Game::onKeyProc(KeyCode key, KeyState state)
{

}