//#pragma once
//
////////////////////////////////////////////////////////
////Coder: Rye
////Purpose: Load map (prototype)
//#include <vector>
//#include "LuckyBox.h"
//#include "Enemy.h"
//
//using namespace stdio_fw;
//class Map
//{
//private:
//	char		m_mapPath[256];
//
//	Image*		m_tileSet;
//	uint		m_tileWidth;
//	uint		m_tileHeight;
//
//	uint**		m_map;
//	uint		m_mapWidth;
//	uint		m_mapHeight;
//
//	int			m_vpx;
//	int			m_vpy;
//
//	std::vector<InformationObject>	m_informationObjects;
//	std::vector<LuckyBox*>			m_frameItem;
//	std::vector<Enemy*>				m_frameEnemy;
//
//	std::vector<Enemy*>				m_frameEnemyOnCamera;
//
//public:
//	Map(const char* path);
//	~Map();
//
//
//	void			initMap();
//	void			update();
//
//
//	void			changeMap(const char* path);
//
//	ErrorCode		loadMap();
//	void			unloadMap();
//
//	uint			getWidth(){ return m_mapWidth; }
//	uint			getHeight(){ return m_mapHeight; }
//
//
//	std::vector<InformationObject>		getInformationObjectsOnCamera();
//	std::vector<LuckyBox*>				getItemsOnCamera();
//	std::vector<Enemy*>					getEnemysOnCamera();
//
//
//	void			setCamera(int vpx, int vpy);
//
//
//	void			drawMap(Graphics* g);
//};
////////////////////////////////////////////////////////