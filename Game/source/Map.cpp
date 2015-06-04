#include "stdafx.h"
//
//#include "ResourcesManager.h"
//#include "Map.h"
//#include "config.h"
//Map::Map(const char* path)
//{
//	strcpy_s(m_mapPath, path);
//}
//
//Map::~Map()
//{
//	if (m_map)
//	{
//		for (int i = 0; i < m_mapHeight; i++)
//			delete m_map[i];
//		SAFE_DEL_ARR(m_map);
//	}
//
//	for (std::vector<LuckyBox*>::iterator temp = m_frameItem.begin(); temp != m_frameItem.end(); temp++)
//	{
//		LuckyBox* x = (*temp);
//		delete x;
//		temp = m_frameItem.erase(temp);
//
//		if (temp != m_frameItem.begin())
//			temp--;
//
//		if (m_frameItem.size() == 0) break;
//	}
//
//	for (std::vector<Enemy*>::iterator currentFrame = m_frameEnemyOnCamera.begin(); currentFrame != m_frameEnemyOnCamera.end(); currentFrame++)
//	{
//		Enemy* x = (*currentFrame);
//		delete x;
//		currentFrame = m_frameEnemyOnCamera.erase(currentFrame);
//
//		if (currentFrame != m_frameEnemyOnCamera.begin())
//			currentFrame--;
//
//		if (m_frameEnemyOnCamera.size() == 0) break;
//	}
//
//	for (std::vector<Enemy*>::iterator currentFrame = m_frameEnemy.begin(); currentFrame != m_frameEnemy.end(); currentFrame++)
//	{
//		Enemy* x = (*currentFrame);
//		delete x;
//		currentFrame = m_frameEnemy.erase(currentFrame);
//
//		if (currentFrame != m_frameEnemy.begin())
//			currentFrame--;
//
//		if (m_frameEnemy.size() == 0) break;
//	}
//	
//}
//
//void Map::unloadMap()
//{
//	m_tileSet->unloadImage();
//}
//
//#pragma region loadMap
//
//int getNumber(char *s)
//{
//	char temp[1024] = { 0 };
//	int n = 0;
//	for (int i = 0; i < strlen(s); i++)
//	{
//		if (s[i] >= '0' && s[i] <= '9')
//		{
//			temp[n++] = s[i];
//		}
//	}
//	return atoi(temp);
//}
//
//void setEmpty(char *s, int size)
//{
//	for (int i = 0; i < size; i++)
//		s[i] = 0;
//}
//
//ErrorCode Map::loadMap()
//{
//	FILE *f = fopen(m_mapPath, "rb");
//
//	if (f != NULL)
//	{
//		char s[1024];
//
//		while (!feof(f))
//		{
//			setEmpty(s, 1024);
//			fgets(s, 1024, f);
//
//			if (strstr(s, "tilewidth=") != NULL)
//			{
//				m_tileWidth = g_getNumber(s);
//			}
//			else if (strstr(s, "tileheight=") != NULL)
//			{
//				m_tileHeight = g_getNumber(s);
//			}
//			else if (strstr(s, "height=") != NULL)
//			{
//				m_mapHeight = g_getNumber(s);
//			}
//			else if (strstr(s, "width=") != NULL)
//			{
//				m_mapWidth = g_getNumber(s);
//			}
//			else if (strstr(s, "data=") != NULL)
//			{
//				m_map = new uint*[m_mapHeight];
//				for (int i = 0; i < m_mapHeight; i++)
//					m_map[i] = new uint[m_mapWidth];
//
//				int row = 0;
//				int column = 0;
//
//				while (!feof(f))
//				{
//					setEmpty(s, 1024);
//					fgets(s, 1024, f);
//
//					if (row == m_mapHeight)
//						break;
//
//					char temp[100] = { 0 };
//					int m = 0;
//
//					int size = strlen(s);
//					for (int i = 0; i < size; i++)
//					{
//						if (s[i] != ',')
//							temp[m++] = s[i];
//						else
//						{
//							m_map[row][column] = atoi(temp);
//
//							if (++column >= m_mapWidth)
//							{
//								column = 0;
//							}
//
//							m = 0;
//							setEmpty(temp, 100);
//						}
//					}
//
//					row++;
//				}
//			}
//			else if (strstr(s, "# ") != NULL)
//			{
//				setEmpty(s, 1024);
//
//				InformationObject object;
//
//				fgets(s, 1024, f);
//				if (strstr(s, "type=") != NULL)
//				{
//					object.m_id = g_getNumber(s);
//				}
//
//				setEmpty(s, 1024);
//				fgets(s, 1024, f);
//
//				char temp[100] = { 0 };
//				int m = 0;
//
//				int id = 0;
//
//				for (int i = strlen("location="); i < strlen(s); i++)
//				{
//					if (s[i] >= '0' && s[i] <= '9')
//					{
//						temp[m++] += s[i];
//					}
//					else if (s[i] == ',' || s[i] == '\n')
//					{
//						switch (id)
//						{
//						case 0:
//							object.m_rect.x = getNumber(temp) * m_tileWidth;
//							break;
//						case 1:
//							object.m_rect.y = getNumber(temp) * m_tileHeight;
//							break;
//						case 2:
//							object.m_rect.width = getNumber(temp) * m_tileWidth;
//							break;
//						case 3:
//							object.m_rect.height = getNumber(temp) * m_tileHeight;
//							break;
//						}
//
//						id++;
//						m = 0;
//						setEmpty(temp, 100);
//					}
//				}
//
//				m_informationObjects.push_back(object);
//			}
//		}
//		fclose(f);
//
//		m_tileSet = ResourcesManager::getInstance()->getResource(SpriteSheet::SHEET_TILESET);
//
//		setCamera(0, 0);
//
//		return ErrorCode::ERR_NO_ERROR;
//	}
//
//	return ErrorCode::ERR_CANT_OPEN_FILE;
//}
//
//#pragma endregion
//
//
//void Map::setCamera(int vpx, int vpy)
//{
//	m_vpx = vpx;
//	m_vpy = vpy;
//
//	//if (m_vpx - SCREEN_WIDTH / 2 < 0) m_vpx = 0;
//}
//
//void Map::drawMap(Graphics *g)
//{
//
//	for (std::vector<Enemy*>::iterator temp = m_frameEnemyOnCamera.begin(); temp != m_frameEnemyOnCamera.end(); temp++)
//	{
//		if ((*temp)->getTypeEnemy() == EnemysType::ET_FLOWER)
//		{
//			(*temp)->setCamera(m_vpx, m_vpy);
//			(*temp)->draw(g);
//		}
//	}
//
//
//	Mat3 matrix;
//	matrix.setTranslation(m_vpx, m_vpy);
//
//	Vec3 vector(0, 0, 1);
//	for (int i = 0; i < m_mapHeight; i++)
//	{
//		for (int j = 0; j < m_mapWidth; j++)
//		{
//			if (m_map[i][j] != 0)
//			{
//				int src_x = (m_map[i][j] % (m_tileSet->getWidth() / m_tileWidth) - 1) * m_tileWidth;
//				int src_y = m_map[i][j] / (m_tileSet->getWidth() / m_tileWidth) * m_tileHeight;
//
//				vector.x = j * m_tileWidth;
//				vector.y = i * m_tileHeight;
//				vector.z = 1;
//
//				vector = vector *  matrix;
//				g->drawRegion(m_tileSet, Rect(vector.x, vector.y, m_tileWidth, m_tileHeight), Rect(src_x, src_y, m_tileWidth, m_tileHeight), FLIP_NONE);
//			}
//		}
//	}
//
//	for (std::vector<LuckyBox*>::iterator temp = m_frameItem.begin(); temp != m_frameItem.end(); temp++)
//	{
//		(*temp)->setCamera(m_vpx, m_vpy);
//		(*temp)->draw(g);
//	}
//
//	for (std::vector<Enemy*>::iterator temp = m_frameEnemyOnCamera.begin(); temp != m_frameEnemyOnCamera.end(); temp++)
//	{
//		if ((*temp)->getTypeEnemy() != EnemysType::ET_FLOWER)
//		{
//			(*temp)->setCamera(m_vpx, m_vpy);
//			(*temp)->draw(g);
//		}
//	}
//}
//
//void Map::initMap()
//{
//	for (std::vector<InformationObject>::iterator temp = m_informationObjects.begin(); temp != m_informationObjects.end(); temp++)
//	{
//		if (temp->m_id == ID_BOXMONEY_ON_MAP)
//		{
//			LuckyBox* box = new LuckyBox(ItemsType::IT_COIN);
//			box->setPosition(temp->m_rect.x, temp->m_rect.y);
//			
//			m_frameItem.push_back(box);
//		}
//		else if (temp->m_id ==  ID_ITEM_GROWUP_ON_MAP || temp->m_id == ID_ITEM_GUN_ON_MAP)
//		{
//			LuckyBox* box = new LuckyBox(ItemsType::IT_MUSHROOM_BIGGER);
//			box->setPosition(temp->m_rect.x, temp->m_rect.y);
//
//			m_frameItem.push_back(box);
//		}
//		else if (temp->m_id == ID_BRICK_ON_MAP)
//		{
//			LuckyBox* box = new LuckyBox(ItemsType::IT_BRICK);
//			box->setPosition(temp->m_rect.x, temp->m_rect.y);
//
//			m_frameItem.push_back(box);
//		}
//		else if (temp->m_id == ID_ENEMY_TURTLE_ON_MAP)
//		{
//			Enemy* enemy = new Enemy(EnemysType::ET_TURTLE, Vec2(temp->m_rect.x, temp->m_rect.y));
//
//			m_frameEnemy.push_back(enemy);
//		}
//		else if (temp->m_id == ID_ENEMY_MUSHROOM_ON_MAP)
//		{
//			Enemy* enemy = new Enemy(EnemysType::ET_MUSHROOM, Vec2(temp->m_rect.x, temp->m_rect.y));
//
//			m_frameEnemy.push_back(enemy);
//		}
//		else if (temp->m_id == ID_ENEMY_FLOWER_ON_MAP)
//		{
//			Enemy* enemy = new Enemy(EnemysType::ET_FLOWER, Vec2(temp->m_rect.x + 16 , temp->m_rect.y + temp->m_rect.height + 8));
//
//			m_frameEnemy.push_back(enemy);
//		}
//	}
//}
//
//void Map::update()
//{	
//	for (std::vector<LuckyBox*>::iterator temp = m_frameItem.begin(); temp != m_frameItem.end(); temp++)
//	{
//		if ((*temp)->getActive())
//			(*temp)->update();
//	}
//
//	for (std::vector<Enemy*>::iterator temp = m_frameEnemyOnCamera.begin(); temp != m_frameEnemyOnCamera.end(); temp++)
//	{
//		if ((*temp)->getActive())
//			(*temp)->update();
//	}
//}
//
//
//std::vector<InformationObject> Map::getInformationObjectsOnCamera()
//{
//	std::vector<InformationObject>	m_frame;
//	Rect camera(-m_vpx, m_vpy, SCREEN_WIDTH * 2, SCREEN_HEIGHT);
//
//	for (int i = 0; i < m_informationObjects.size(); i++)
//	{
//		if (m_informationObjects[i].m_id == ID_STAND_ON_MAP
//			|| m_informationObjects[i].m_id == ID_PIPE_ON_MAP || m_informationObjects[i].m_id == ID_STAIR_ON_MAP)
//		{
//			if (g_CheckAABB(m_informationObjects[i].m_rect, camera))
//			{
//				m_frame.push_back(m_informationObjects[i]);
//			}
//		}	
//	}
//
//	return m_frame;
//}
//
//
//std::vector<LuckyBox*> Map::getItemsOnCamera()
//{
//	std::vector<LuckyBox*>	m_frame;
//	Rect camera(-m_vpx, m_vpy, SCREEN_WIDTH, SCREEN_HEIGHT);
//
//	for (int i = 0; i < m_frameItem.size(); i++)
//	{
//		Vec2 position = m_frameItem[i]->getBox()->getPosition();
//		Rect bound = m_frameItem[i]->getBox()->getRect();
//
//		if (g_CheckAABB(Rect(position.x, position.y, bound.width, bound.height), camera) && m_frameItem[i]->getActive())
//		{
//			m_frameItem[i]->setActive(true);
//			m_frame.push_back(m_frameItem[i]);
//		}
//	}
//
//	return m_frame;
//}
//
//
//std::vector<Enemy*> Map::getEnemysOnCamera()
//{
//	Rect camera(-m_vpx, m_vpy, SCREEN_WIDTH, SCREEN_HEIGHT);
//
//	std::vector<Enemy*>::iterator currentFrame = m_frameEnemyOnCamera.begin();
//
//	while (currentFrame != m_frameEnemyOnCamera.end())
//	{
//		if ((*currentFrame)->getPosition().x + (*currentFrame)->getRect().width < -m_vpx ||
//			(*currentFrame)->getPosition().y > camera.y + camera.height || !(*currentFrame)->getActive())
//		{
//			Enemy* x = (*currentFrame);
//			delete x;
//			currentFrame = m_frameEnemyOnCamera.erase(currentFrame);
//
//			if (currentFrame != m_frameEnemyOnCamera.begin())
//				currentFrame--;
//
//			if (m_frameEnemyOnCamera.size() == 0) break;
//		}
//		
//		currentFrame++;
//	}
//
//	for (std::vector<Enemy*>::iterator temp = m_frameEnemy.begin(); temp != m_frameEnemy.end(); temp++)
//	{
//		Vec2 position = (*temp)->getPosition();
//		Rect bound = (*temp)->getRect();
//
//		if (g_CheckAABB(Rect(position.x, position.y, bound.width, bound.height), camera))
//		{
//			(*temp)->setActive(true);
//			m_frameEnemyOnCamera.push_back(*temp);
//
//			temp = m_frameEnemy.erase(temp);
//
//			if (m_frameEnemy.size() == 0) break;
//			if (temp != m_frameEnemy.begin())
//				temp--;
//		}
//	}
//
//
//	return m_frameEnemyOnCamera;
//}
//
