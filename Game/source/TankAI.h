#ifndef __TANK_AI_H__
#define __TANK_AI_H__

class State;
class Roaming : public State, public Singleton<Roaming>
{
public:
	Roaming();
	virtual ~Roaming();

	virtual void	Enter(Entity* _entity);
	virtual void	Execute(Entity* _entity);
	virtual void	Exit(Entity* _entity);
};


class Fighting : public State, public Singleton<Fighting>
{
public:
	Fighting();
	virtual ~Fighting();

	virtual void	Enter(Entity* _entity);
	virtual void	Execute(Entity* _entity);
	virtual void	Exit(Entity* _entity);
};


class Chasing : public State, public Singleton<Chasing>
{
public:
	Chasing();
	virtual ~Chasing();

	virtual void	Enter(Entity* _entity);
	virtual void	Execute(Entity* _entity);
	virtual void	Exit(Entity* _entity);
};


class Fleeing : public State, public Singleton<Fleeing>
{
public:
	Fleeing();
	virtual ~Fleeing();

	virtual void	Enter(Entity* _entity);
	virtual void	Execute(Entity* _entity);
	virtual void	Exit(Entity* _entity);
};

#endif