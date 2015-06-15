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

	m_bullet = new Image(SPR_BULLET_NORMAL);
	m_bullet->loadImage();

	LoadFont(FNT_DEFINE);

}

void ResourcesManager::Release()
{
	for(int i = 0; i < 4; i++)
	{
		m_tank1[i]->unloadImage();
		delete m_tank1[i];
	}

	m_bullet->unloadImage();
	delete m_bullet;

	m_font->unloadImage();
	SAFE_DEL(m_font);

	delete s_instance;
}

ErrorCode ResourcesManager::LoadFont(const char* _path)
{
	m_font = new Image(FNT_IMAGE);
	m_font->loadImage();

	FILE* f = fopen(_path, "rb");

	if(!f)
		return ErrorCode::ERR_CANT_LOAD_FONT;

	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);

	char* buffer = new char[size];
	fread(buffer, sizeof(char), size, f);

	fclose(f);

	while(buffer)
	{
		char* id = strstr(buffer, "char id=");
		if(!id)
			break;

		id += strlen("char id=");
		int idNumber = GetNumber(id);
		m_fontChar[idNumber].m_id = idNumber;
		buffer = id;

		// Rect
		char* x = strstr(buffer, "x=");
		x += strlen("x=");
		m_fontChar[idNumber].m_rect.x = GetNumber(x);

		char* y = strstr(buffer, "y=");
		y += strlen("y=");
		m_fontChar[idNumber].m_rect.y = GetNumber(y);

		char* width = strstr(buffer, "width=");
		width += strlen("width=");
		m_fontChar[idNumber].m_rect.width = GetNumber(width);

		char* height = strstr(buffer, "height=");
		height += strlen("height=");
		m_fontChar[idNumber].m_rect.height = GetNumber(height);
		///////////////////////////////////////////////////

		// Offset
		char* offsetX = strstr(buffer, "xoffset=");
		offsetX += strlen("xoffset=");
		m_fontChar[idNumber].m_offset.x = GetNumber(offsetX);

		char* offsetY = strstr(buffer, "yoffset=");
		offsetY += strlen("yoffset=");
		m_fontChar[idNumber].m_offset.y = GetNumber(offsetY);
		///////////////////////////////////////////////////

		char* xAdvance = strstr(buffer, "xadvance=");
		xAdvance += strlen("xadvance=");
		m_fontChar[idNumber].m_xAdvance = GetNumber(xAdvance);
	}

	return ErrorCode::ERR_NO_ERROR;
}

void ResourcesManager::LoadMap(const char* _path)
{

}