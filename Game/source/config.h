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

static const char*	SPR_BULLET_NORMAL	= "image//spr_bullet.png";

static const char*	FNT_IMAGE			= "font//font.png";
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