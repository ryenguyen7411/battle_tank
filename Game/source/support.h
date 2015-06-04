#ifndef __SUPPORT_H__
#define __SUPPORT_H__

////////////////////////////////////////////////////////////
//Coder: Rye
//Purpose: Game support

using namespace stdio_fw;

enum CompType
{
	COMP_UNKNOWN = -1,
	COMP_TRANSFORM = 0,
	COMP_RENDERER = 1,
	COMP_COLLIDER2D = 2
};

enum Team
{
	TEAM_NONE = 0,
	TEAM_RED = 1,
	TEAM_BLUE = 2
};

enum GameState
{
	STATE_PLAY,
	STATE_WIN,
	STATE_GAME_OVER,
};

enum SpriteSheet
{
	SHEET_MARIO,
	SHEET_ENEMIES,
	SHEET_ITEM,
	SHEET_TILESET,
};

enum Direction
{
	DIR_UNKNOWN = -1,
	DIR_NONE = 0,
	DIR_TOP,
	DIR_BOTTOM,
	DIR_LEFT,
	DIR_RIGHT,
};

Direction	g_isCollide(Rect st, Rect nd, Vec2 stVeloc, Vec2 ndVeloc = Vec2(0, 0));
int			g_getNumber(char* s);

bool		g_CheckAABB(Rect box1, Rect box2);

#endif