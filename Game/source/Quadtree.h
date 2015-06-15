#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#define MAX_LEVEL		5
#define MAX_ENTITY		3

#include <vector>

class Entity;

class Quadtree
{
private:
	int			m_level;
	Rect		m_region;

	std::vector<Entity*>	m_entityList;
	Quadtree*				m_subRegion[4];

	bool		IsContain(Entity* _entity);
	void		Split();
	
public:
	Quadtree(int _level, Rect _region);
	virtual ~Quadtree();

	void		Clear();
	void		Insert(Entity* _entity);
	std::vector<Entity*>	Retrieve(Entity* _entity);
};

#endif