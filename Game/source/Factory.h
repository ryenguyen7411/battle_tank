#ifndef __FACTORY_H__
#define __FACTORY_H__

class Entity;

class Factory : public Singleton<Factory>
{
public:
	Factory();
	virtual ~Factory();

	Entity*		CreateTank(Team _team, Vec3 _position = Vec3().zero());
};

#endif