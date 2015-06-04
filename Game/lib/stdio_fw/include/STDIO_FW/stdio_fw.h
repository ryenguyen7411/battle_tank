#pragma once

// Use VLD to check memory leak
//#define USE_VLD
#ifdef USE_VLD
	#include "vld.h"
#endif

#include <stdio.h>
#include <Windows.h>

#include "macros.h"
#include "defined.h"
#include "types.h"

#include "Utils\stdio_math.h"
#include "Utils\AffineTransform.h"
#include "Core\Application.h"
#include "Video\Graphics.h"
#include "Video\Image.h"
#include "Video\Font.h"
