#ifndef __CONFIG_H__
#define __CONFIG_H__

/////////////////////////////////////////////////////////////////////////////
//Coder: Rye Nguyen
//Define some constants
//Purpose: Set basic value for game

#define SCREEN_WIDTH				800
#define SCREEN_HEIGHT				600

#define FPS							30
#define FRAME_TIME					10

#define WHITE		0xFFFFFFFF
#define BLACK		0x000000FF

#define ITEM_TIME		20.0f

#define MAX_HP				100.0f
#define MAX_SPEED			10.0f
#define MAX_DAMAGE			40.0f
#define MAX_SHOOT_PER_SEC	10
#define MAX_TANK			1

#define OUT_OF_MAP			10000


// TANK
static const char*	SPR_TANK_1_UP		= "image//spr_tank1_up.png";
static const char*	SPR_TANK_1_DOWN		= "image//spr_tank1_down.png";
static const char*	SPR_TANK_1_LEFT		= "image//spr_tank1_left.png";
static const char*	SPR_TANK_1_RIGHT	= "image//spr_tank1_right.png";

static const char*	SPR_TANK_2_UP		= "image//spr_tank2_up.png";
static const char*	SPR_TANK_2_DOWN		= "image//spr_tank2_down.png";
static const char*	SPR_TANK_2_LEFT		= "image//spr_tank2_left.png";
static const char*	SPR_TANK_2_RIGHT	= "image//spr_tank2_right.png";

static const char*	SPR_TANK_3_UP		= "image//spr_tank3_up.png";
static const char*	SPR_TANK_3_DOWN		= "image//spr_tank3_down.png";
static const char*	SPR_TANK_3_LEFT		= "image//spr_tank3_left.png";
static const char*	SPR_TANK_3_RIGHT	= "image//spr_tank3_right.png";


// BULLET
static const char*	SPR_BULLET_NORMAL	= "image//spr_normal_bullet.png";

static const char*	SPR_BULLET_EXPLODE_UP		= "image//spr_normal_bullet.png";
static const char*	SPR_BULLET_EXPLODE_DOWN		= "image//spr_normal_bullet.png";
static const char*	SPR_BULLET_EXPLODE_LEFT		= "image//spr_normal_bullet.png";
static const char*	SPR_BULLET_EXPLODE_RIGHT	= "image//spr_normal_bullet.png";


// FONT
static const char*	FNT_BLACK			= "font//font_black.png";
static const char*	FNT_RED				= "font//font_red.png";
static const char*	FNT_BLUE			= "font//font_blue.png";
static const char*	FNT_DEFINE			= "font//font.fnt";

static float		FNT_SIZE_DESIGN		= 1.0f;
static float		FNT_SIZE_SMALL		= FNT_SIZE_DESIGN / 7.5f;
static float		FNT_SIZE_NORMAL		= FNT_SIZE_DESIGN / 5;
static float		FNT_SIZE_BIG		= FNT_SIZE_DESIGN / 2;
static float		FNT_SIZE_TITLE		= FNT_SIZE_DESIGN;


// MAP
static const char*	MAP_1			= "map//map1.ranf";
static const char*	MAP_2			= "map//map2.ranf";
static const char*	MAP_3			= "map//map3.ranf";

static const char*	SPR_GRASS		= "image//spr_grass.png";
static const char*	SPR_WATER		= "image//spr_water.png";
static const char*	SPR_ROCK		= "image//spr_rock.png";
static const char*	SPR_BRICK_1		= "image//spr_brick_1.png";
static const char*	SPR_BRICK_2		= "image//spr_brick_2.png";
static const char*	SPR_BRICK_3		= "image//spr_brick_3.png";
static const char*	SPR_BRICK_4		= "image//spr_brick_4.png";


// ITEM
static const char*	SPR_ITEM_HP			= "image//spr_item_hp.png";
static const char*	SPR_ITEM_SPEED		= "image//spr_item_speed.png";
static const char*	SPR_ITEM_DAMAGE		= "image//spr_item_damage.png";
static const char*	SPR_ITEM_TANK		= "image//spr_item_tank.png";
static const char*	SPR_ITEM_INVI		= "image//spr_item_invisible.png";
static const char*	SPR_ITEM_BULLET		= "image//spr_item_bullet.png";


// TAG
static const char*	TAG_TANK			= "Tank";
static const char*	TAG_BULLET			= "Bullet";
static const char*	TAG_TEAM			= "Team";
static const char*	TAG_HP				= "HP";
static const char*	TAG_BRICK			= "Brick";
static const char*	TAG_ROCK			= "Rock";
static const char*	TAG_OCEAN			= "Ocean";
static const char*	TAG_SCREENCOLLIDER	= "ScreenCollider";
static const char*	TAG_TEAMMANAGER		= "TeamManager";
static const char*	TAG_UITEXT			= "UiText";
static const char*	TAG_ITEM			= "Item";


#endif