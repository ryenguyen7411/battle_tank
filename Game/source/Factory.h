#ifndef __FACTORY_H__
#define __FACTORY_H__

class Entity;

class Factory : public Singleton<Factory>
{
public:
	Factory();
	virtual ~Factory();
	
	void		Release();

	Entity*		CreateTank(Team _team, Vec3 _position, Control _control = Control::CTRL_AUTO, Tank _tankType = Tank::TANK_NORMAL);
	Entity*		CreateBullet(Team _team, Vec3 _position, Direction _direction, Bullet _type, float _speed, float _range, float _damage);
	Entity*		CreateCollider(const char* _tag, Rect _bound, bool _isBreakable = false, Vec2 _position = Vec2());

	Entity*		CreateManager(Team _team);
};

#endif