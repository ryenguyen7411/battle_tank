#include "stdafx.h"

#include "Map.h"
#include "ResourcesManager.h"
#include "Factory.h"
#include "EntitiesSystem.h"
#include "Entity.h"

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

	Entity* player = Factory::GetInstance()->CreateTank(Team::TEAM_RED, Vec3(300, 300, 1));
	EntitiesSystem::GetInstance()->m_entitiesList.push_back(player);

	return errCode;
}


void Game::update(float deltaTime)
{
	

	/////////////////////////////////////////////////
	//Coder: Rye
	//Purpose: manage FPS
	if(1000.0f / FPS > deltaTime)
		Sleep(1000.0f / FPS - deltaTime);
}

void Game::render(Graphics* g)
{
	g->cleanScreen();
	g->setClearColor(0xFFFFFFFF);
	//g->setColor(0xFFFFFFFF);

	std::vector<Entity*> entitiesList = EntitiesSystem::GetInstance()->m_entitiesList;
	for(int i = 0; i < entitiesList.size(); i++)
	{
		entitiesList[i]->Draw(g);
	}
}

void Game::exit()
{

	//ResourcesManager::getInstance()->unloadResources();
}

void Game::onKeyProc(KeyCode key, KeyState state)
{
}