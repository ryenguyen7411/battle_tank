#include "stdio_fw.h"

#include "GL\glew.h"
#include "Video\Image.h"

#include "FreeImage.h"

namespace stdio_fw
{
	Image::Image(const char* path, 
				IMAGE_FILTER_MODE minFilter,
				IMAGE_FILTER_MODE magFilter,
				bool useMipmap) :
		m_imgWidth(0),
		m_imgHeight(0),
		m_texID(0),
		m_isLoaded(false),
		m_minFilterMode(minFilter),
		m_magFilterMode(magFilter),
		m_useMipmap(useMipmap)
	{
		strcpy_s(m_imgPath, path);
	}

	Image::~Image()
	{
		unloadImage();
	}

	ErrorCode Image::loadImage()
	{
		if (m_isLoaded)
			return ErrorCode::ERR_NO_ERROR;

		// Load image data
		uint width, height;
		byte* data = loadImageData(width, height);

		if (data == NULL)
			return ErrorCode::ERR_CANT_OPEN_FILE;

		// Create and bind texture
		glGenTextures(1, &m_texID);
		glBindTexture(GL_TEXTURE_2D, m_texID);

		GLuint internalFormat = m_imgBPP == 3 ? GL_RGB : GL_RGBA;
		GLuint format = m_imgBPP == 3 ? GL_BGR : GL_BGRA;
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		
		if (m_useMipmap)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minFilterMode);
		}
		else
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minFilterMode);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_magFilterMode);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		glBindTexture(GL_TEXTURE_2D, 0);
		m_isLoaded = true;

		SAFE_DEL_ARR(data);

		return ErrorCode::ERR_NO_ERROR;
	}

	byte* Image::loadImageData(uint &pow2w, uint &pow2h)
	{		
		FREE_IMAGE_FORMAT img_format = FreeImage_GetFileType(m_imgPath, 0);
		FIBITMAP* img_bm = FreeImage_Load(img_format, m_imgPath);

		if (img_bm == NULL)
			return NULL;

		m_imgWidth = FreeImage_GetWidth(img_bm);
		m_imgHeight = FreeImage_GetHeight(img_bm);
		m_imgBPP = FreeImage_GetBPP(img_bm) / 8;
		
		pow2w = roundUpPow2(m_imgWidth);
		pow2h = roundUpPow2(m_imgHeight);

		byte *data, *pixels;
		FIBITMAP* img_rescaled = NULL;
		if (m_imgWidth == pow2w && m_imgHeight == pow2h)
		{
			pixels = FreeImage_GetBits(img_bm);			
		}
		else
		{
			img_rescaled = FreeImage_Rescale(img_bm, pow2w, pow2h, FILTER_BOX);
			pixels = FreeImage_GetBits(img_rescaled);			
		}

		uint img_sz = pow2w * pow2h * m_imgBPP;
		data = new byte[img_sz];
		memcpy(data, pixels, img_sz);

		// Clean up
		FreeImage_Unload(img_bm);
		if (img_rescaled)
			FreeImage_Unload(img_rescaled);
		

		return data;
	}

	void Image::unloadImage()
	{
		glDeleteTextures(1, &m_texID);
		m_isLoaded = false;
	}

	uint Image::roundUpPow2(uint n)
	{
		uint x = 1;
		while (x < n) x <<= 1;

		return x;
	}
}