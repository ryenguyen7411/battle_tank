#ifndef __ENTITY_SYSTEM_H__
#define __ENTITY_SYSTEM_H__

#include <vector>

class Quadtree;
class Entity;

class EntitiesSystem : public Singleton<EntitiesSystem>
{
public:
	std::vector<Entity*>		m_entitiesList;
	Quadtree*					m_quadtree;

	Entity*			m_teamRedManager;
	Entity*			m_teamBlueManager;

	EntitiesSystem();
	virtual ~EntitiesSystem();

	void			Release();
	void			Remove(Entity* _entity);

	Quadtree*		UpdateQuadtree();

	std::vector<Entity*>		Retrieve(Rect rect, Team _team);
	std::vector<Entity*>		Retrieve(Rect _rect, const char* _tag);
};

#endif