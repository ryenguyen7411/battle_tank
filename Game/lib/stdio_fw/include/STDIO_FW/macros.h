#pragma once

#define LOG(...) printf(__VA_ARGS__)

#define XSCREEN2GL(x, width)			((1.0f*x - (width >> 1))/(width >> 1))
#define YSCREEN2GL(y, height)			(-1.0f*(1.0f*y - (height >> 1))/(height >> 1))

#define X2UVGL(x, width)				((x)/(width*1.0f))
#define Y2UVGL(y, height)				(1.0f - (y)/(height*1.0f))

// Safe delete
#define SAFE_DEL(x)					\
{									\
if (x)							\
	{								\
	delete x;					\
	x = nullptr;						\
	}								\
}

#define SAFE_DEL_ARR(x) \
{									\
if (x)							\
	{								\
	delete[] x;					\
	x = nullptr;						\
	}								\
}

// Show error window and exit program if condition wrong
#define ASSERT_MSG(condition, message) \
{ \
if (!condition) \
	{ \
	char buff[512]; \
	sprintf_s(buff, "%s\n%s: %i", message, __FILE__, __LINE__); \
	MessageBox(NULL, buff, NULL, MB_OK | MB_ICONEXCLAMATION); \
	exit(1); \
	} \
}

// Show error window and exit program 
// [in] message
#define SHOW_ERROR_MSG(message) \
{ \
	MessageBox(NULL, message, NULL, MB_OK | MB_ICONEXCLAMATION);	\
} \

