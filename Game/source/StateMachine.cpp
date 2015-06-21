#include "stdafx.h"
#include "Entity.h"
#include "State.h"

#include <typeinfo>

#include "StateMachine.h"

StateMachine::StateMachine(Entity* _owner)
{
	m_owner = _owner;

	m_currentState = NULL;
	m_previousState = NULL;
}

StateMachine::~StateMachine()
{
	m_owner = NULL;

	m_currentState = NULL;
	m_previousState = NULL;
}

void StateMachine::Update()
{
	if(m_currentState)
		m_currentState->Execute(m_owner);
}

void StateMachine::ChangeState(State* _state)
{
	if(m_currentState)
	{
		m_previousState = m_currentState;
		m_currentState->Exit(m_owner);
	}

	m_currentState = _state;
	m_currentState->Enter(m_owner);
}

bool StateMachine::IsInState(State* _state)
{
	return typeid(*m_currentState) == typeid(_state);
}