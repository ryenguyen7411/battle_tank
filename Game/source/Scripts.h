#ifndef __SCRIPTS_H__
#define __SCRIPTS_H__

#include "StateMachine.h"
#include "Components.h"

#pragma region TankController
class TankController : public Component
{
public:
	Team		m_team;
	Control		m_control;

	float		m_speed;
	float		m_damage;
	float		m_shootSpeed;
	float		m_shootRange;

	int			m_shootPerSec;
	bool		m_canShoot;
	long		m_previousTime;

	Direction	m_direction;
	int			m_lockDirection;

	bool		m_invisible;
	long		m_timer;
	float		m_expTime;

	Tank		m_tank;
	Bullet		m_bullet;

	float			m_heuristicValue;
	StateMachine	m_stateMachine;

	TankController(Tank _tankType = Tank::TANK_NORMAL);
	~TankController();

	virtual void	Release();
	virtual void	Update();

	void			CalculateHeuristic();
};
#pragma endregion


#pragma region BulletController
class BulletController : public Component
{
public:
	Team		m_team;

	float		m_speed;
	float		m_range;

	float		m_damage;
	Direction	m_direction;

	Vec3		m_savePosition;

	BulletController();
	virtual ~BulletController();

	virtual void	Release();
	virtual void	Update();
};
#pragma endregion


#pragma region HealthControl
class HealthControl : public Component
{
public:
	float		m_health;

	HealthControl(Tank _type = Tank::TANK_NORMAL);
	virtual ~HealthControl();

	virtual void		Release();
	virtual void		Update();
};
#pragma endregion


#pragma region BrickControl
class BrickControl : public Component
{
public:
	float		m_health;
	Vec2		m_position;

	BrickControl();
	virtual ~BrickControl();

	virtual void		Release();
	virtual void		Update();
};
#pragma endregion


#pragma region Manager
class Manager : public Component
{
public:
	Team			m_team;

	Entity*			m_teamRed[4];
	Entity*			m_teamBlue[4];

	Entity*			m_player;

	Manager();
	virtual ~Manager();

	virtual void	Release();
	virtual void	Update();
};
#pragma endregion


#pragma region ItemManager
class ItemManager : public Component
{
public:
	float		m_plusHP;
	float		m_plusSpeed;
	float		m_plusDamage;
	bool		m_plusTank;
	bool		m_plusBullet;
	bool		m_invisible;
	float		m_expTime;

	Item		m_item;

	ItemManager(Item _type = Item::ITEM_NONE);
	virtual ~ItemManager();

	virtual void	Release();
	virtual void	Update();
};
#pragma endregion


#pragma region DetectEnemy
class DetectEnemy : public Component
{
public:
	Entity*		m_targetEnemy;
	Entity*		m_encounterEnemy;

	DetectEnemy();
	virtual ~DetectEnemy();

	virtual void	Release();
	virtual void	Update();
};
#pragma endregion


#pragma region AutoTankManager
class AutoTankManager : public Component
{
public:
	KeyCode			m_virtualKey;

	AutoTankManager();
	virtual ~AutoTankManager();

	virtual void	Release();
	virtual void	Update();

	void			Move();
	KeyCode			GetNextRandomKey();
	Direction		GetShootDirection(Vec3 _targetPosition);
	Direction		GetDirectionToEnemy(Vec3 _targetPosition);
	Direction		GetDirectionAwayFromEnemy(Vec3 _targetPosition);

	bool			IsInShootRange(Vec3 _targetPosition);
	void			SetKeyForDirection(Direction _direction);
};
#pragma endregion

#endif