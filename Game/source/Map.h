#ifndef __MAP_H__
#define __MAP_H__

using namespace stdio_fw;

class Map : public Singleton<Map>
{
public:
	char		m_mapPath[256];
	int			m_currentMap;

	int			m_mapWidth;
	int			m_mapHeight;

	int			m_tileWidth;
	int			m_tileHeight;

	int			m_map[128][128];

	Vec2		m_offset;

	int			m_teamRed[3];
	int			m_teamBlue[3];

	Vec3		m_redDefaultLocation[4];
	Vec3		m_blueDefaultLocation[4];

	std::vector<Entity*>	m_mapPartList;
public:
	Map();
	virtual ~Map();

	virtual void	Release();

	void			ChangeMap(const char* _path);

	ErrorCode		LoadMap();
	void			UnloadMap();

	void			CreateCollider();
	Vec3			GetMapPosition(Vec3 _position);
	Vec3			GetMapRandomPosition();

	Vec3			GetPosition(Vec3 _mapPosition);
	int				MinCost(Vec3 _startPosition, Vec3 _endPosition);

	void			Update();
	void			Draw(Graphics* g);
};

#endif