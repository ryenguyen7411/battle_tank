#include "stdafx.h"

#include "Factory.h"
#include "Entity.h"
#include "EntitiesSystem.h"

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

	Factory::GetInstance()->CreateTank(Team::TEAM_RED, Vec3(200, 200, 1), Control::CTRL_ARROW);
	Factory::GetInstance()->CreateTank(Team::TEAM_BLUE, Vec3(100, 100, 1), Control::CTRL_WSAD);
	
	return errCode;
}


void Game::update(float deltaTime)
{
	EntitiesSystem::GetInstance()->UpdateQuadtree();
	std::vector<Entity*> entitiesList = EntitiesSystem::GetInstance()->m_entitiesList;
	for(int i = 0; i < entitiesList.size(); i++)
	{
		entitiesList[i]->Update();
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
	g->setClearColor(0xFFFFFFFF);

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