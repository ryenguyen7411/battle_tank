#include "stdafx.h"

#include "ResourcesManager.h"
#include "Map.h"
#include "EntitiesSystem.h"
#include "Entity.h"

#include "Components.h"
#include "Scripts.h"
#include "State.h"
#include "TankAI.h"

#include "Factory.h"

using namespace stdio_fw;

Factory::Factory()
{

}

Factory::~Factory()
{
	
}

void Factory::Release()
{
	
}

Entity* Factory::CreateTank(Team _team, Vec3 _position, Control _control, Tank _tankType)
{
	Entity* tank = new Entity();
	tank->SetTag(TAG_TANK);

	if(_team == Team::TEAM_RED)
		tank->m_transform->m_position = Map::GetInstance()->m_redDefaultLocation[rand() % 4];
	else if(_team == Team::TEAM_BLUE)
		tank->m_transform->m_position = Map::GetInstance()->m_blueDefaultLocation[rand() % 4];

	Renderer* renderer = new Renderer(ResourcesManager::GetInstance()->m_tank1[0]);
	tank->AddComponent(renderer);

	Animator* animator = new Animator();
	tank->AddComponent(animator);
	animator->SetFrameList(4, ResourcesManager::GetInstance()->m_tank1[0], ResourcesManager::GetInstance()->m_tank1[1],
		ResourcesManager::GetInstance()->m_tank1[2], ResourcesManager::GetInstance()->m_tank1[3]);

	Rect bound = Rect(_position.x - renderer->m_sprite->getWidth() / 2, _position.y - renderer->m_sprite->getHeight() / 2,
		renderer->m_sprite->getWidth(), renderer->m_sprite->getHeight());
	Collider2D* collider2d = new Collider2D(bound);
	tank->AddComponent(collider2d);

	TankController* tankController = new TankController(_tankType);
	tank->AddComponent(tankController);
	tankController->m_team = _team;
	tankController->m_control = _control;
	if(_control == Control::CTRL_AUTO)
	{
		//tankController->m_stateMachine = StateMachine(tankController->m_baseEntity);
		//tankController->m_stateMachine.ChangeState(new Roaming());
	}

	HealthControl* healthControl = new HealthControl(_tankType);
	tank->AddComponent(healthControl);


	Entity* hp = new Entity();
	hp->SetTag(TAG_HP);
	hp->m_transform->m_position = Vec3(0, -25, 0);
	UIText* hpText = new UIText();
	hp->AddComponent(hpText);
	hpText->m_fontSize = FNT_SIZE_SMALL;
	hpText->m_anchor = Anchor::ANCHOR_CENTER;
	if(_team == Team::TEAM_RED)
		hpText->m_font = ResourcesManager::GetInstance()->m_fontRed;
	else
		hpText->m_font = ResourcesManager::GetInstance()->m_fontBlue;
	hp->m_transform->SetParent(tank->m_transform);
	EntitiesSystem::GetInstance()->m_entitiesList.push_back(hp);


	EntitiesSystem::GetInstance()->m_entitiesList.push_back(tank);

	return tank;
}

Entity* Factory::CreateBullet(Team _team, Vec3 _position, Direction _direction, Bullet _type, float _speed, float _range, float _damage)
{
	Entity* bullet = new Entity();
	bullet->SetTag(TAG_BULLET);
	bullet->m_transform->m_position = _position;

	Renderer* renderer = new Renderer(ResourcesManager::GetInstance()->m_bulletNormal);
	bullet->AddComponent(renderer);

	Rect bound = Rect(_position.x - renderer->m_sprite->getWidth() / 2, _position.y - renderer->m_sprite->getHeight() / 2,
		renderer->m_sprite->getWidth(), renderer->m_sprite->getHeight());
	Collider2D* collider2d = new Collider2D(bound);
	bullet->AddComponent(collider2d);

	BulletController* bulletController = new BulletController();
	bullet->AddComponent(bulletController);
	bulletController->m_team = _team;
	bulletController->m_speed = _speed;
	bulletController->m_range = _range;
	bulletController->m_damage = _damage;
	bulletController->m_direction = _direction;
	bulletController->m_savePosition = bullet->m_transform->m_position;

	EntitiesSystem::GetInstance()->m_entitiesList.push_back(bullet);

	return bullet;
}

Entity* Factory::CreateCollider(const char* _tag, Rect _bound, bool _isBreakable, Vec2 _position)
{
	Entity* mapPart = new Entity();
	mapPart->SetTag(_tag);

	mapPart->m_transform->m_position = Vec3(_bound.x + _bound.width / 2, _bound.y + _bound.height / 2, 0);

	Collider2D* colider2d = new Collider2D(_bound);
	mapPart->AddComponent(colider2d);

	if(_isBreakable)
	{
		BrickControl* brickControl = new BrickControl();
		mapPart->AddComponent(brickControl);
		brickControl->m_health = 100.0f;
		brickControl->m_position = _position;
	}

	EntitiesSystem::GetInstance()->m_entitiesList.push_back(mapPart);

	return mapPart;
}


Entity*	Factory::CreateItem(Item _type)
{
	Entity* item = new Entity();
	item->SetTag(TAG_ITEM);
	while(true)
	{
		int x = rand() % Map::GetInstance()->m_mapWidth;
		int y = rand() % Map::GetInstance()->m_mapHeight;

		if(Map::GetInstance()->m_map[y][x] == 0)
		{
			item->m_transform->m_position = Vec3((x + 0.5f) * Map::GetInstance()->m_tileWidth + Map::GetInstance()->m_offset.x,
												(y + 0.5f) * Map::GetInstance()->m_tileHeight + Map::GetInstance()->m_offset.y,
												0);
			break;
		}
	}

	Renderer* renderer = new Renderer(ResourcesManager::GetInstance()->m_item[_type]);
	item->AddComponent(renderer);

	Rect bound = Rect(item->m_transform->m_position.x - Map::GetInstance()->m_tileWidth / 2,
						item->m_transform->m_position.y - Map::GetInstance()->m_tileHeight / 2,
						Map::GetInstance()->m_tileWidth,
						Map::GetInstance()->m_tileHeight);
	Collider2D* collider2d = new Collider2D(bound);
	item->AddComponent(collider2d);

	ItemManager* itemManager = new ItemManager(_type);
	item->AddComponent(itemManager);

	EntitiesSystem::GetInstance()->m_entitiesList.push_back(item);

	return item;
}

Entity* Factory::CreateManager(Team _team)
{
	Entity* teamManager = new Entity();
	teamManager->SetTag(TAG_TEAM_MANAGER);
	if(_team == Team::TEAM_RED)
		teamManager->m_transform->m_position = Vec3(700, 450, 0);
	else if(_team == Team::TEAM_BLUE)
		teamManager->m_transform->m_position = Vec3(700, 150, 0);

	Manager* manager = new Manager();
	teamManager->AddComponent(manager);
	manager->m_team = _team;

	Entity* tank1 = new Entity();
	tank1->SetTag(TAG_UITEXT);
	tank1->m_transform->m_position = Vec3(-50, 0, 0);
	UIText* uiText1 = new UIText();
	tank1->AddComponent(uiText1);
	uiText1->m_fontSize = FNT_SIZE_BIG;
	uiText1->m_anchor = Anchor::ANCHOR_CENTER;
	tank1->m_transform->SetParent(teamManager->m_transform);
	EntitiesSystem::GetInstance()->m_entitiesList.push_back(tank1);


	Entity* tank2 = new Entity();
	tank2->SetTag(TAG_UITEXT);
	tank2->m_transform->m_position = Vec3(0, 0, 0);
	UIText* uiText2 = new UIText();
	tank2->AddComponent(uiText2);
	uiText2->m_fontSize = FNT_SIZE_BIG;
	uiText2->m_anchor = Anchor::ANCHOR_CENTER;
	tank2->m_transform->SetParent(teamManager->m_transform);
	EntitiesSystem::GetInstance()->m_entitiesList.push_back(tank2);


	Entity* tank3 = new Entity();
	tank3->SetTag(TAG_UITEXT);
	tank3->m_transform->m_position = Vec3(50, 0, 0);
	UIText* uiText3 = new UIText();
	tank3->AddComponent(uiText3);
	uiText3->m_fontSize = FNT_SIZE_BIG;
	uiText3->m_anchor = Anchor::ANCHOR_CENTER;
	tank3->m_transform->SetParent(teamManager->m_transform);
	EntitiesSystem::GetInstance()->m_entitiesList.push_back(tank3);


	if(_team == Team::TEAM_RED)
	{
		uiText1->m_font = ResourcesManager::GetInstance()->m_fontRed;
		uiText2->m_font = ResourcesManager::GetInstance()->m_fontRed;
		uiText3->m_font = ResourcesManager::GetInstance()->m_fontRed;
	}
	else
	{
		uiText1->m_font = ResourcesManager::GetInstance()->m_fontBlue;
		uiText2->m_font = ResourcesManager::GetInstance()->m_fontBlue;
		uiText3->m_font = ResourcesManager::GetInstance()->m_fontBlue;
	}


	EntitiesSystem::GetInstance()->m_entitiesList.push_back(teamManager);
	if(_team == Team::TEAM_RED)
		EntitiesSystem::GetInstance()->m_teamRedManager = teamManager;
	else
		EntitiesSystem::GetInstance()->m_teamBlueManager = teamManager;

	return teamManager;
}