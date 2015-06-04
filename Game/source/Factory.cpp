#include "stdafx.h"
#include "Entity.h"
#include "Components.h"

#include "Factory.h"

using namespace stdio_fw;

Factory::Factory()
{

}

Factory::~Factory()
{

}

Entity* Factory::CreateTank(Team _team, Vec3 _position)
{
	Entity* tank = new Entity();
	tank->m_team = _team;
	
	Component* transform = new Transform(_position);
	tank->AddComponent(transform);

	Image* sprite = new Image("image//spr_tank1.png");
	sprite->loadImage();

	Component* renderer = new Renderer(sprite);
	tank->AddComponent(renderer);

	return tank;
}