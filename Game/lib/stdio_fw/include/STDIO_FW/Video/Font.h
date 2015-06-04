#pragma once

// FreeType Headers
#include "ft2build.h"
#include FT_FREETYPE_H

namespace stdio_fw
{
	class Graphics;
	class Font
	{
		friend class Graphics;
	private:
		char					m_fontPath[128];
		FT_Face					m_face;

	public:
		Font(const char* font_path);

		ErrorCode		loadFont();
		void			setFontSize(int size);
		
		// Static variable and method
	private:
		static FT_Library		m_sFTlib;

		// Texture slot for font rendering
		static uint		m_texID;
		
	public:
		static ErrorCode initFontLib();		
	};
}

