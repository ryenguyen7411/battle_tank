//#pragma once
//
//////////////////////////////////////////////////////////////
////Coder: Rye
////Purpose: Load resource for using later
//#include <vector>
//
//using namespace stdio_fw;
//class ResourcesManager
//{
//private:
//	static ResourcesManager*	m_instance;
//
//	Image*					m_mario;
//	std::vector<Frame>*		m_marioFrameList;
//
//	Image*					m_enemies;
//	std::vector<Frame>*		m_enemiesFrameList;
//
//	Image*					m_items;
//	std::vector<Frame>*		m_itemsFrameList;
//
//	Image*		m_tileSet;
//	std::vector<Frame>*		m_tileSetFrameList;
//
//	void		loadFrameList(std::vector<Frame>*& frameList, const char* path);
//public:
//	ResourcesManager();
//	virtual ~ResourcesManager();
//
//	static ResourcesManager* getInstance();
//
//	void		loadResources();
//	void		unloadResources();
//
//	Image*				getResource(SpriteSheet sheet);
//	std::vector<Frame>*	getFrameList(SpriteSheet sheet);
//};
//////////////////////////////////////////////////////////////