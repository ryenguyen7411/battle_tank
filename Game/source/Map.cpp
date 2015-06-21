#include "stdafx.h"
#include "EntitiesSystem.h"
#include "Entity.h"

#include "Map.h"

Map::Map()
{
	m_currentMap = 0;
	m_offset = Vec2(12, 12);
}

Map::~Map()
{

}

void Map::Release()
{

}

void Map::ChangeMap(const char* _path)
{
	UnloadMap();
	strcpy(m_mapPath, _path);
	LoadMap();

	m_currentMap++;
}

ErrorCode Map::LoadMap()
{
	FILE* f = fopen(m_mapPath, "rb");

	if(!f)
		return ErrorCode::ERR_CANT_OPEN_FILE;

	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);

	char* buffer = new char[size + 1];
	fread(buffer, sizeof(char), size, f);
	buffer[size] = NULL;

	fclose(f);

	char* temp = buffer;
	
	// Map Info
	char* mapInfo = strstr(temp, "[MapInfo]");
	mapInfo = strstr(temp, "width=");
	mapInfo += strlen("width=");
	m_mapWidth = GetNumber(mapInfo);

	mapInfo = strstr(temp, "height=");
	mapInfo += strlen("height=");
	m_mapHeight = GetNumber(mapInfo);

	mapInfo = strstr(temp, "tilewidth=");
	mapInfo += strlen("tilewidth=");
	m_tileWidth = GetNumber(mapInfo);

	mapInfo = strstr(temp, "tileheight=");
	mapInfo += strlen("tileheight=");
	m_tileHeight = GetNumber(mapInfo);

	// Map
	char* map = strstr(temp, "[Map]");
	map += strlen("[Map]") + 2;
	for(int i = 0; i < m_mapHeight; i++)
	{
		for(int j = 0; j < m_mapWidth; j++)
		{
			m_map[i][j] = GetNumber(map);
			map += 2;
		}
		map += 2;
	}

	// Team Red
	char* teamRed = strstr(temp, "[TeamRed]");
	teamRed = strstr(teamRed, "tanktype_1=");
	teamRed += strlen("tanktype_1=");
	m_teamRed[0] = GetNumber(teamRed);
	teamRed = strstr(teamRed, "tanktype_2=");
	teamRed += strlen("tanktype_2=");
	m_teamRed[1] = GetNumber(teamRed);
	teamRed = strstr(teamRed, "tanktype_3=");
	teamRed += strlen("tanktype_3=");
	m_teamRed[2] = GetNumber(teamRed);


	// Team Blue
	char* teamBlue = strstr(temp, "[TeamBlue]");
	teamBlue = strstr(teamBlue, "tanktype_1=");
	teamBlue += strlen("tanktype_1=");
	m_teamBlue[0] = GetNumber(teamBlue);
	teamBlue = strstr(teamBlue, "tanktype_2=");
	teamBlue += strlen("tanktype_2=");
	m_teamBlue[1] = GetNumber(teamBlue);
	teamBlue = strstr(teamBlue, "tanktype_3=");
	teamBlue += strlen("tanktype_3=");
	m_teamBlue[2] = GetNumber(teamBlue);


	// Collider
	char* collider = strstr(temp, "[Collider]");
	while(collider = strstr(collider, "collider="))
	{
		collider += strlen("collider=");

		Rect bound;
		bound.x = GetNumber(collider) * m_tileWidth + m_offset.x;
		while(*collider++ != ',');
		bound.y = GetNumber(collider) * m_tileHeight + m_offset.y;
		while(*collider++ != ',');
		bound.width = GetNumber(collider) * m_tileWidth - 1;
		while(*collider++ != ',');
		bound.height = GetNumber(collider) * m_tileHeight - 1;
		while(*collider++ != ',');

		int type = GetNumber(collider);

		char tag[256];
		if(type == 2)
			strcpy(tag, TAG_OCEAN);
		else if(type == 3)
			strcpy(tag, TAG_ROCK);

		m_mapPartList.push_back(Factory::GetInstance()->CreateCollider(tag, bound));
	}


	// Default Location
	char* defaultLocation = strstr(temp, "[DefaultLocation]");
	for(int i = 0; i < 4; i++)
	{
		defaultLocation = strstr(defaultLocation, "location=");
		defaultLocation += strlen("location=");

		m_redDefaultLocation[i].x = (GetNumber(defaultLocation) + 0.5f) * m_tileWidth + m_offset.x;
		while(*defaultLocation++ != ',');
		m_redDefaultLocation[i].y = (GetNumber(defaultLocation) + 0.5f) * m_tileHeight + m_offset.y;
	}
	for(int i = 0; i < 4; i++)
	{
		defaultLocation = strstr(defaultLocation, "location=");
		defaultLocation += strlen("location=");

		m_blueDefaultLocation[i].x = (GetNumber(defaultLocation) + 0.5f) * m_tileWidth + m_offset.x;
		while(*defaultLocation++ != ',');
		m_blueDefaultLocation[i].y = (GetNumber(defaultLocation) + 0.5f) * m_tileHeight + m_offset.y;
	}

	SAFE_DEL_ARR(buffer);

	CreateCollider();

	return ErrorCode::ERR_NO_ERROR;
}

void Map::UnloadMap()
{
	m_mapWidth = 0;
	m_mapHeight = 0;

	m_tileWidth = 0;
	m_tileHeight = 0;

	m_teamRed[0] = 0;
	m_teamRed[1] = 0;
	m_teamRed[2] = 0;

	m_teamBlue[0] = 0;
	m_teamBlue[1] = 0;
	m_teamBlue[2] = 0;

	while(!m_mapPartList.empty())
	{
		EntitiesSystem::GetInstance()->Remove(m_mapPartList.back());
		m_mapPartList.pop_back();
	}
}

void Map::CreateCollider()
{
	for(int i = 0; i < m_mapHeight; i++)
	{
		for(int j = 0; j < m_mapHeight; j++)
		{
			if(m_map[i][j] == 4)
			{
				Rect rect = Rect(j * m_tileWidth + m_offset.x, i * m_tileHeight + m_offset.y, m_tileWidth - 1, m_tileHeight - 1);
				m_mapPartList.push_back(Factory::GetInstance()->CreateCollider(TAG_BRICK, rect, true, Vec2(i, j)));
			}
		}
	}
}

void Map::Update()
{

}

void Map::Draw(Graphics* g)
{
	g->setColor(BLACK);
	g->drawRect(Rect(m_offset.x - 5, m_offset.y - 5, m_mapWidth * m_tileWidth + 10, m_mapHeight * m_tileHeight + 10), 5);

	for(int i = 0; i < m_mapHeight; i++)
	{
		for(int j = 0; j < m_mapWidth; j++)
		{
			if(m_map[i][j] != 0)
			{
				Image* image = ResourcesManager::GetInstance()->m_mapPart[m_map[i][j] - 1];
				Rect rect = Rect(j * m_tileWidth + m_offset.x, i * m_tileHeight + m_offset.y, m_tileWidth, m_tileHeight);
				g->drawImage(image, rect);
			}
		}
	}
}