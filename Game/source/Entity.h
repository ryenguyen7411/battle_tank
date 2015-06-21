#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <vector>

class Component;
class Transform;
class Renderer;
class Rigidbody2D;
class Animator;
class Collider2D;

class Entity
{
public:
	char			m_tag[256];

	Transform*		m_transform;
	Renderer*		m_renderer;
	Rigidbody2D*	m_rigidbody2d;
	Animator*		m_animator;
	Collider2D*		m_collider2d;

	std::vector<Component*>		m_componentList;

	Entity();
	virtual ~Entity();

	void			Release();

	void						AddComponent(Component* _component);
	Component*					GetComponent(CompType _type);
	std::vector<Component*>		GetComponents(CompType _type);

	void			SetTag(const char* _tag);
	bool			IsTaggedAs(const char* _tag);

	void			Update();
	void			Draw(Graphics* g);
};

#endif