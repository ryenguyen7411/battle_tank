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

static const char*	SPR_BULLET_NORMAL	= "image//spr_normal_bullet.png";

static const char*	SPR_BULLET_EXPLODE_UP		= "image//spr_normal_bullet.png";
static const char*	SPR_BULLET_EXPLODE_DOWN		= "image//spr_normal_bullet.png";
static const char*	SPR_BULLET_EXPLODE_LEFT		= "image//spr_normal_bullet.png";
static const char*	SPR_BULLET_EXPLODE_RIGHT	= "image//spr_normal_bullet.png";

static const char*	FNT_BLACK			= "font//font_black.png";
static const char*	FNT_RED				= "font//font_red.png";
static const char*	FNT_BLUE			= "font//font_blue.png";
static const char*	FNT_DEFINE			= "font//font.fnt";

static float		FNT_SIZE_DESIGN		= 1.0f;
static float		FNT_SIZE_SMALL		= FNT_SIZE_DESIGN / 7.5f;
static float		FNT_SIZE_NORMAL		= FNT_SIZE_DESIGN / 5;
static float		FNT_SIZE_BIG		= FNT_SIZE_DESIGN / 2;
static float		FNT_SIZE_TITLE		= FNT_SIZE_DESIGN;


#define WHITE		0xFFFFFFFF;
#define BLACK		0x00000000;


////////////////////////////////////////////////////////////

#endif