#include "stdafx.h"
#include <ctime>

#include "ResourcesManager.h"
#include "Map.h"
#include "Factory.h"
#include "Entity.h"
#include "EntitiesSystem.h"

#include "Components.h"
#include "Scripts.h"

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
	Map::GetInstance()->ChangeMap(MAP, 1);

	Factory::GetInstance()->CreateManager(Team::TEAM_RED);
	Factory::GetInstance()->CreateManager(Team::TEAM_BLUE);

	m_itemTimer = clock();
	
	return errCode;
}


// EntitiesList will update size after all entities updated
// NULL entity will be remove
void Game::update(float deltaTime)
{
	switch(Map::GetInstance()->m_gameState)
	{
		case GameState::STATE_READY:
			if(GetAsyncKeyState(VK_SPACE))
				Map::GetInstance()->m_gameState = GameState::STATE_PLAY;
			break;
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
				Factory::GetInstance()->CreateItem(/*Item(rand() % Item::ITEM_COUNT)*/Item::ITEM_INVISIBLE);
				m_itemTimer = clock();
			}
		}
			break;
		case GameState::STATE_RED_WIN:
		case GameState::STATE_BLUE_WIN:
		case GameState::STATE_DRAW:
			if(GetAsyncKeyState(VK_SPACE))
				Map::GetInstance()->ChangeMap(MAP, Map::GetInstance()->m_currentMap);
			if(GetAsyncKeyState(VK_RETURN))
				Map::GetInstance()->ChangeMap(MAP, Map::GetInstance()->m_currentMap + 1);
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

	switch(Map::GetInstance()->m_gameState)
	{
		case GameState::STATE_READY:
			g->drawImage(ResourcesManager::GetInstance()->m_message[0], Rect(44, 172, 512, 256));
			break;
		case GameState::STATE_RED_WIN:
			g->drawImage(ResourcesManager::GetInstance()->m_message[1], Rect(44, 172, 512, 256));
			break;
		case GameState::STATE_BLUE_WIN:
			g->drawImage(ResourcesManager::GetInstance()->m_message[2], Rect(44, 172, 512, 256));
			break;
		case GameState::STATE_DRAW:
			g->drawImage(ResourcesManager::GetInstance()->m_message[3], Rect(44, 172, 512, 256));
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