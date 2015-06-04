#include "stdio_fw.h"

#include "GL\glew.h"
#include "Video\Font.h"

namespace stdio_fw
{
	FT_Library Font::m_sFTlib = nullptr;
	uint Font::m_texID = 0;

	ErrorCode Font::initFontLib()
	{
		if (FT_Init_FreeType(&m_sFTlib))
			return ErrorCode::ERR_INIT_FREETYPE_FAILED;

		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &m_texID);
		glBindTexture(GL_TEXTURE_2D, m_texID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);

		return ErrorCode::ERR_NO_ERROR;
	}

	Font::Font(const char* font_path)
	{
		strcpy(m_fontPath, font_path);
	}

	ErrorCode Font::loadFont()
	{
		if (FT_New_Face(m_sFTlib, m_fontPath, 0, &m_face))
			return ErrorCode::ERR_CANT_LOAD_FONT;
		
		// set font default size
		FT_Set_Pixel_Sizes(m_face, 0, 48);

		return ErrorCode::ERR_NO_ERROR;
	}

	void Font::setFontSize(int size)
	{
		FT_Set_Pixel_Sizes(m_face, 0, size);
	}
}
