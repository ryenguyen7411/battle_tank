#include "stdafx.h"
#include "Entity.h"
#include "EntitiesSystem.h"
#include "Components.h"
#include "Scripts.h"

#include "Factory.h"

using namespace stdio_fw;

Factory::Factory()
{

}

Factory::~Factory()
{

}

Entity* Factory::CreateTank(Team _team, Vec3 _position, Control _control, Tank _tankType)
{
	Entity* tank = new Entity();
	tank->SetTag("Tank");
	
	tank->m_transform->m_position = _position;

	Image* sprite = new Image(SPR_TANK_1_UP);
	sprite->loadImage();
	Renderer* renderer = new Renderer(sprite);
	tank->AddComponent(renderer);

	Animator* animator = new Animator();
	animator->SetFrameList(4, SPR_TANK_1_UP, SPR_TANK_1_DOWN, SPR_TANK_1_LEFT, SPR_TANK_1_RIGHT);
	tank->AddComponent(animator);

	Collider2D* collider2d = new Collider2D(renderer->m_bound);
	tank->AddComponent(collider2d);

	//if(_control == Control::CTRL_ARROW)
	//{
		TankController* tankController = new TankController(_tankType);
		tankController->m_team = _team;
		tankController->m_control = _control;
		tank->AddComponent(tankController);
	//}

	HealthControl* healthControl = new HealthControl(_tankType);
	tank->AddComponent(healthControl);

	EntitiesSystem::GetInstance()->m_entitiesList.push_back(tank);

	return tank;
}

Entity* Factory::CreateBullet(Vec3 _position, Direction _direction, Bullet _type, float _speed, float _range, float _damage)
{
	Entity* bullet = new Entity();
	bullet->SetTag("Bullet");

	bullet->m_transform->m_position = _position;

	Image* sprite = NULL;
	if(_type == Bullet::BULLET_NORMAL)
		sprite = new Image(SPR_BULLET_NORMAL);
	else
		sprite = new Image(SPR_BULLET_NORMAL); // Fix later
	sprite->loadImage();
	Renderer* renderer = new Renderer(sprite);
	bullet->AddComponent(renderer);

	Collider2D* collider2d = new Collider2D(renderer->m_bound);
	bullet->AddComponent(collider2d);

	BulletController* bulletController = new BulletController();
	bullet->AddComponent(bulletController);
	bulletController->m_speed = _speed;
	bulletController->m_range = _range;
	bulletController->m_damage = _damage;
	bulletController->m_direction = _direction;
	bulletController->m_savePosition = bullet->m_transform->m_position;

	EntitiesSystem::GetInstance()->m_entitiesList.push_back(bullet);

	return bullet;
}