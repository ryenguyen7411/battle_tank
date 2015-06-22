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
	COMP_RIGIDBODY2D = 2,
	COMP_COLLIDER2D = 3,
	COMP_ANIMATOR = 4,
	COMP_UITEXT = 5,

	COMP_TANKCONTROLLER = 10,
	COMP_BULLETCONTROLLER = 11,
	COMP_HEALTHCONTROL = 12,
	COMP_BRICKCONTROL = 13,
	COMP_MANAGER = 14,
	COMP_ITEMMANAGER = 15,
	COMP_FINDENEMY = 16,
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

enum Direction
{
	DIR_UNKNOWN = -1,
	DIR_NONE = 0,
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
};

enum Control
{
	CTRL_AUTO = 0,
	CTRL_ARROW = 1,
	CTRL_WSAD = 2
};

enum Bullet
{
	BULLET_NORMAL = 0,
	BULLET_EXPLODE = 1,
};

enum Tank
{
	TANK_NORMAL = 0,
	TANK_DEFENSE = 1,
	TANK_BOLT = 2
};

enum Anchor
{
	ANCHOR_CENTER = 0,
	ANCHOR_LEFT = 1,
	ANCHOR_RIGHT = 2
};

enum Item
{
	ITEM_NONE = -1,
	ITEM_HP = 0,
	ITEM_SPEED = 1,
	ITEM_DAMAGE = 2,
	ITEM_TANK = 3,
	ITEM_INVISIBLE = 4,
	ITEM_BULLET = 5,
	ITEM_COUNT,
};

struct MecanimKey
{

};

struct FontChar
{
	int		m_id;
	Rect	m_rect;
	Vec2	m_offset;
	int		m_xAdvance;

	FontChar(){}
	~FontChar(){}
};

Direction	g_isCollide(Rect st, Rect nd, Vec2 stVeloc, Vec2 ndVeloc = Vec2(0, 0));
int			GetNumber(char* s);

bool		g_CheckAABB(Rect box1, Rect box2);

bool		isInRect(Rect _rect, Vec2 _position);
bool		isInRect(Rect _rect, Vec3 _position);

int			convertToInt(char* _sNumber);
char*		convertToString(int _number);

#endif