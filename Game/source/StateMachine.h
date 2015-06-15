#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

class State;
class StateMachine
{
public:
	Entity*		m_owner;
	State*		m_currentState;
	State*		m_previousState;

	StateMachine(Entity* _owner = NULL);
	virtual ~StateMachine();

	virtual void	Update();
	virtual void	ChangeState(State* _state);

	bool			IsInState(State* _state);
};

#endif