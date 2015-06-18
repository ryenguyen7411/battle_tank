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

	float		m_shootDelay;
	bool		m_canShoot;
	long		m_previousTime;

	Direction	m_direction;
	int			m_lockDirection;

	Tank		m_tank;
	Bullet		m_bullet;

	StateMachine	m_stateMachine;

	TankController(Tank _tankType = Tank::TANK_NORMAL);
	~TankController();

	virtual void	Release();
	virtual void	Update();
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
	float		m_defense;

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

#endif