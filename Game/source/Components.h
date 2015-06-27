#ifndef __COMPONENTS_H__
#define __COMPONENTS_H__

using namespace stdio_fw;

#include <vector>

class Entity;
class Transform;
class Renderer;
class Rigidbody2D;
class Collider2D;
class Animator;

class Component
{
public:
	CompType	m_type;
	Entity*		m_baseEntity;

	Component();
	virtual ~Component();

	virtual void	Release() = 0;
	virtual void	Update() = 0;
};

// Basic components
class Transform : public Component
{
public:
	Vec3	m_position;
	Vec3	m_rotation;
	Vec3	m_scale;

	Transform*				m_parent;
	int						m_childCount;
	std::vector<Transform*>	m_childList;

	Transform(Vec3 _position = Vec3().zero(), Vec3 _rotation = Vec3().zero(), Vec3 _scale = Vec3().one());
	virtual ~Transform();

	virtual void	Release();
	virtual void	Update();

	void			SetParent(Transform* _parent);
	bool			IsMiddle(Transform* a, Transform* b);
};


class Renderer : public Component
{
public:
	Image*			m_sprite;

	Renderer(Image* _sprite = NULL);
	virtual ~Renderer();

	virtual void	Release();
	virtual void	Update();
};


class Rigidbody2D : public Component
{
public:
	float		m_gravity;
	Vec3		m_velocity;
	Vec3		m_friction;

	Rigidbody2D();
	virtual ~Rigidbody2D();

	virtual void	Release();
	virtual void	Update();
};


class Collider2D : public Component
{
public:
	Rect		m_bound;
	Entity*		m_collisionObject;

	Collider2D(Rect _bound = Rect());
	virtual ~Collider2D();

	virtual void	Release();
	virtual void	Update();

	bool			CheckAABB(Collider2D* _collider2d);
};


class Animator : public Component
{
public:
	std::vector<Image*>		m_frameList;
	std::vector<float>		m_frameTime;

	int				m_currentFrame;
	long			m_previousTime;

	Animator();
	virtual ~Animator();

	virtual void	Release();
	virtual void	Update();

	void			SetFrameList(int _count, ...);
	void			SetFrameTime(int _count, ...);
};

class UIText : public Component
{
public:
	char		m_text[256];
	Anchor		m_anchor;

	Image*		m_font;
	float		m_fontSize;

	UIText();
	virtual ~UIText();

	virtual void	Release();
	virtual void	Update();
};

#endif