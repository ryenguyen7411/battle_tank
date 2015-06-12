#ifndef __FACTORY_H__
#define __FACTORY_H__

class Entity;

class Factory : public Singleton<Factory>
{
public:
	Factory();
	virtual ~Factory();

	Entity*		CreateTank(Team _team, Vec3 _position, Control _control = Control::CTRL_AUTO, Tank _tankType = Tank::TANK_NORMAL);
	Entity*		CreateBullet(Vec3 _position, Direction _direction, Bullet _type, float _speed, float _range, float _damage);
};

#endif