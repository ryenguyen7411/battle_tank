#ifndef __STATE_H__
#define __STATE_H__

class Entity;

class State
{
public:
	State(){}
	virtual			~State(){}

	virtual void	Enter(Entity* _entity)		= 0;
	virtual void	Execute(Entity* _entity)	= 0;
	virtual void	Exit(Entity* _entity)		= 0;
};

#endif