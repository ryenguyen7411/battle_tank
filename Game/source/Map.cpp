#include "stdafx.h"
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
	SAFE_DEL(s_instance);
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
	
	char* mapWidth = strstr(temp, "width=");
	mapWidth += strlen("width=");
	m_mapWidth = GetNumber(mapWidth);

	char* mapHeight = strstr(temp, "height=");
	mapHeight += strlen("height=");
	m_mapHeight = GetNumber(mapHeight);

	char* tileWidth = strstr(temp, "tilewidth=");
	tileWidth += strlen("tilewidth=");
	m_tileWidth = GetNumber(tileWidth);

	char* tileHeight = strstr(temp, "tileheight=");
	tileHeight += strlen("tileheight=");
	m_tileHeight = GetNumber(tileHeight);

	char* map = strstr(temp, "map=");
	map += strlen("map=") + 2;

	for(int i = 0; i < m_mapHeight; i++)
	{
		for(int j = 0; j < m_mapWidth; j++)
		{
			m_map[i][j] = GetNumber(map);
			map += 2;
		}

		map += 2;
	}

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
}

void Map::CreateCollider()
{
	for(int i = 0; i < m_mapHeight; i++)
	{
		for(int j = 0; j < m_mapHeight; j++)
		{
			if(m_map[i][j] == 2 || m_map[i][j] == 3)
			{

			}
			else if(m_map[i][j] == 4)
			{

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