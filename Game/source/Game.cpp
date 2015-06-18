#include "stdafx.h"

#include "ResourcesManager.h"
#include "Factory.h"
#include "Entity.h"
#include "EntitiesSystem.h"
#include "Components.h"
#include "Map.h"

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

	ResourcesManager::GetInstance()->LoadResources();
	Map::GetInstance()->ChangeMap(MAP_1);

	Factory::GetInstance()->CreateTank(Team::TEAM_RED, Vec3(200, 200, 1), Control::CTRL_ARROW);
	Factory::GetInstance()->CreateTank(Team::TEAM_BLUE, Vec3(100, 100, 1), Control::CTRL_WSAD);
	
	return errCode;
}


void Game::update(float deltaTime)
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

	Map::GetInstance()->Draw(g);
}

void Game::exit()
{
	Factory::GetInstance()->Release();
	EntitiesSystem::GetInstance()->Release();
	ResourcesManager::GetInstance()->Release();
	Map::GetInstance()->Release();
}

void Game::onKeyProc(KeyCode key, KeyState state)
{

}