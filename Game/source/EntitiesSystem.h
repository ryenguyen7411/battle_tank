#ifndef __ENTITY_SYSTEM_H__
#define __ENTITY_SYSTEM_H__

#include <vector>

class EntitiesSystem : public Singleton<EntitiesSystem>
{
public:
	EntitiesSystem();
	virtual ~EntitiesSystem();

	std::vector<Entity*>		m_entitiesList;

	//std::vector<Entity*>		GetReds();
	//std::vector<Entity*>		GetBlue();
};

#endif