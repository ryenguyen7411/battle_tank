#ifndef __MAP_H__
#define __MAP_H__

class Map
{
private:
	char		m_mapPath[256];

	// Define needed variables
	
public:
	Map(const char* path);		// Set path
	~Map();			// Release

	void			changeMap(const char* path);	// Unload, change path and load again

	void			loadMap();	// Load map, save to variables
	void			unloadMap(); // Release map

	void			update();	// Do later
	//void			drawMap(Graphics* g);
};

#endif