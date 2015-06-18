#ifndef __RESOURCE_MANAER_H__
#define __RESOURCE_MANAER_H__

#include <vector>
using namespace stdio_fw;

class ResourcesManager : public Singleton<ResourcesManager>
{
public:
	Image*		m_tank1[4];
	Image*		m_tank2[4];
	Image*		m_tank3[4];
	Image*		m_bulletNormal;
	Image*		m_bulletExplode[4];

	Image*		m_fontBlack;
	Image*		m_fontRed;
	Image*		m_fontBlue;
	FontChar	m_fontChar[128];

	Image*		m_mapPart[7];

	ResourcesManager();
	virtual ~ResourcesManager();

	void		LoadResources();
	void		Release();

	ErrorCode		LoadFont(const char* _path);
};

#endif