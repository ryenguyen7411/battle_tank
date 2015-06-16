// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

// Include depend libs
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glfw3dll.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "FreeImage.lib")
#pragma comment(lib, "freetype.lib")

#pragma comment(lib, "stdio_fw.lib")

#include "STDIO_FW\stdio_fw.h"
#include "STDIO_FW\Utils\stdio_math.h"
#include "STDIO_FW\Video\Image.h"

#include "config.h"
#include "support.h"
#include "Singleton.h"
#include "ResourcesManager.h"
#include "Factory.h"

//#define USE_VLD

#ifdef USE_VLD
	#pragma comment(lib, "vld.lib")
	#include "vld.h"
#endif