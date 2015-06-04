#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <vector>

class Component;
class Transform;
class Renderer;

class Entity
{
public:
	Team			m_team;

	Transform*		m_transform;
	Renderer*		m_renderer;
	//Collider2D		m_collider2D;

	std::vector<Component*>		m_componentList;
public:
	Entity();
	virtual ~Entity();

	void						AddComponent(Component* _component);
	Component*					GetComponent(CompType _type);
	std::vector<Component*>		GetComponents(CompType _type);

	void			Draw(Graphics* g);
};

#endif