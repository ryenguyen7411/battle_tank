#include "stdafx.h"
#include "ResourcesManager.h"

ResourcesManager::ResourcesManager()
{

}

ResourcesManager::~ResourcesManager()
{

}

void ResourcesManager::LoadResources()
{
	m_tank1[0] = new Image(SPR_TANK_1_UP);
	m_tank1[0]->loadImage();
	m_tank1[1] = new Image(SPR_TANK_1_DOWN);
	m_tank1[1]->loadImage();
	m_tank1[2] = new Image(SPR_TANK_1_LEFT);
	m_tank1[2]->loadImage();
	m_tank1[3] = new Image(SPR_TANK_1_RIGHT);
	m_tank1[3]->loadImage();


	m_tank2[0] = new Image(SPR_TANK_2_UP);
	m_tank2[0]->loadImage();
	m_tank2[1] = new Image(SPR_TANK_2_DOWN);
	m_tank2[1]->loadImage();
	m_tank2[2] = new Image(SPR_TANK_2_LEFT);
	m_tank2[2]->loadImage();
	m_tank2[3] = new Image(SPR_TANK_2_RIGHT);
	m_tank2[3]->loadImage();


	m_tank3[0] = new Image(SPR_TANK_3_UP);
	m_tank3[0]->loadImage();
	m_tank3[1] = new Image(SPR_TANK_3_DOWN);
	m_tank3[1]->loadImage();
	m_tank3[2] = new Image(SPR_TANK_3_LEFT);
	m_tank3[2]->loadImage();
	m_tank3[3] = new Image(SPR_TANK_3_RIGHT);
	m_tank3[3]->loadImage();


	m_bulletNormal = new Image(SPR_BULLET_NORMAL);
	m_bulletNormal->loadImage();
	m_bulletExplode[0] = new Image(SPR_BULLET_EXPLODE_UP);
	m_bulletExplode[0]->loadImage();
	m_bulletExplode[1] = new Image(SPR_BULLET_EXPLODE_DOWN);
	m_bulletExplode[1]->loadImage();
	m_bulletExplode[2] = new Image(SPR_BULLET_EXPLODE_LEFT);
	m_bulletExplode[2]->loadImage();
	m_bulletExplode[3] = new Image(SPR_BULLET_EXPLODE_RIGHT);
	m_bulletExplode[3]->loadImage();


	m_mapPart[0] = new Image(SPR_GRASS);
	m_mapPart[1] = new Image(SPR_WATER);
	m_mapPart[2] = new Image(SPR_ROCK);
	m_mapPart[3] = new Image(SPR_BRICK_1);
	m_mapPart[4] = new Image(SPR_BRICK_2);
	m_mapPart[5] = new Image(SPR_BRICK_3);
	m_mapPart[6] = new Image(SPR_BRICK_4);
	for(int i = 0; i < 7; i++)
		m_mapPart[i]->loadImage();


	m_item[0] = new Image(SPR_ITEM_HP);
	m_item[1] = new Image(SPR_ITEM_SPEED);
	m_item[2] = new Image(SPR_ITEM_DAMAGE);
	m_item[3] = new Image(SPR_ITEM_TANK);
	m_item[4] = new Image(SPR_ITEM_INVI);
	m_item[5] = new Image(SPR_ITEM_BULLET);
	for(int i = 0; i < Item::ITEM_COUNT; i++)
	{
		m_item[i]->loadImage();
	}

	LoadFont(FNT_DEFINE);
}

void ResourcesManager::Release()
{
	for(int i = 0; i < 4; i++)
	{
		m_tank1[i]->unloadImage();
		SAFE_DEL(m_tank1[i]);
		m_tank2[i]->unloadImage();
		SAFE_DEL(m_tank2[i]);
		m_tank3[i]->unloadImage();
		SAFE_DEL(m_tank3[i]);

		m_bulletExplode[i]->unloadImage();
		SAFE_DEL(m_bulletExplode[i]);
	}


	m_bulletNormal->unloadImage();
	SAFE_DEL(m_bulletNormal);


	m_fontBlack->unloadImage();
	SAFE_DEL(m_fontBlack);
	m_fontRed->unloadImage();
	SAFE_DEL(m_fontRed);
	m_fontBlue->unloadImage();
	SAFE_DEL(m_fontBlue);

	for(int i = 0; i < 7; i++)
	{
		m_mapPart[i]->unloadImage();
		SAFE_DEL(m_mapPart[i]);
	}
	for(int i = 0; i < Item::ITEM_COUNT; i++)
	{
		m_item[i]->unloadImage();
		SAFE_DEL(m_item[i]);
	}
}

ErrorCode ResourcesManager::LoadFont(const char* _path)
{
	m_fontBlack = new Image(FNT_BLACK);
	m_fontBlack->loadImage();
	m_fontRed = new Image(FNT_RED);
	m_fontRed->loadImage();
	m_fontBlue = new Image(FNT_BLUE);
	m_fontBlue->loadImage();

	FILE* f = fopen(_path, "rb");

	if(!f)
		return ErrorCode::ERR_CANT_LOAD_FONT;

	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);

	char* buffer = new char[size + 1];
	fread(buffer, sizeof(char), size, f);
	buffer[size] = NULL;

	fclose(f);

	char* temp = buffer;

	while(temp)
	{
		char* id = strstr(temp, "char id=");
		if(!id)
			break;

		id += strlen("char id=");
		int idNumber = GetNumber(id);
		m_fontChar[idNumber].m_id = idNumber;
		temp = id;

		// Rect
		char* x = strstr(temp, "x=");
		x += strlen("x=");
		m_fontChar[idNumber].m_rect.x = GetNumber(x);

		char* y = strstr(temp, "y=");
		y += strlen("y=");
		m_fontChar[idNumber].m_rect.y = GetNumber(y);

		char* width = strstr(temp, "width=");
		width += strlen("width=");
		m_fontChar[idNumber].m_rect.width = GetNumber(width);

		char* height = strstr(temp, "height=");
		height += strlen("height=");
		m_fontChar[idNumber].m_rect.height = GetNumber(height);
		///////////////////////////////////////////////////

		// Offset
		char* offsetX = strstr(temp, "xoffset=");
		offsetX += strlen("xoffset=");
		m_fontChar[idNumber].m_offset.x = GetNumber(offsetX);

		char* offsetY = strstr(temp, "yoffset=");
		offsetY += strlen("yoffset=");
		m_fontChar[idNumber].m_offset.y = GetNumber(offsetY);
		///////////////////////////////////////////////////

		char* xAdvance = strstr(temp, "xadvance=");
		xAdvance += strlen("xadvance=");
		m_fontChar[idNumber].m_xAdvance = GetNumber(xAdvance);
	}

	SAFE_DEL_ARR(buffer);

	return ErrorCode::ERR_NO_ERROR;
}