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

	EntitiesSystem();
	virtual ~EntitiesSystem();

	void			Release();

	//std::vector<Entity*>		GetReds();
	//std::vector<Entity*>		GetBlue();

	void			Remove(Entity* _entity);

	Quadtree*		UpdateQuadtree();
};

#endif