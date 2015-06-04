#pragma once

#include <list>

namespace stdio_fw
{
	enum CACHED_LOC
	{		
		// Solid object
		ATT_POSITION0 = 0,		
		UNI_COLOR0,
		// Image
		ATT_POSITION1,
		ATT_TEXCOORD1,
		UNI_TEXTURE1,
		// Font render
		ATT_POSITION2,
		ATT_TEXCOORD2,
		UNI_COLOR2,
		UNI_TEXTURE2,

		// Max cached loc
		TOTAL_LOC
	};

	enum CACHED_PROGRAM
	{
		PRG_SOL = 0,
		PRG_IMG,
		PRG_FON,
		TOTAL_PRG
	};

	class Image;
	class Font;
	class Graphics
	{
		// We use 2 program: 0 for SOLID OBJECT and 1 for IMAGE
		uint		m_aPrograms[TOTAL_PRG];

		// Cache attribute and uniforms location here
		int					m_cachedLocs[TOTAL_LOC];

		float				m_drawColor[4];
		float				m_clearColor[4];

		int					m_iScreenW;
		int					m_iScreenH;		

		Font*				m_curFont;		
		AffineTransform		m_affineTransform;

	public:
		Graphics();
		~Graphics();

		ErrorCode			initGraphics(int screenW, int screenH);

		void				fillRect(int x, int y, int width, int height);
		void				fillRect(Rect rect);


		void				drawRect(int x, int y, int width, int height, int weight = 1);
		void				drawRect(Rect rect, int weight = 1);

		void				drawLine(int x1, int y1, int x2, int y2);
		void				drawLine(Vec2 p1, Vec2 p2);

		void				drawImage(Image* img, int x, int y, uint flipping = 0);
		void				drawImage(Image* img, Rect rect, uint flipping = 0);

		void				drawRegion(Image* img, int x, int y, int width, int height, int src_x, int src_y, int src_w, int src_h, uint flipping = 0);
		void				drawRegion(Image* img, Rect src, Rect dest, uint flipping = 0);

		void				drawText(const char* text, int x, int y, int scale_x = 1, int scale_y = 1);

		// Set color function: 0xRRGGBBAA
		void				setColor(uint color);
		void				setColor(int red, int green, int blue, int alpha);
		
		void				setClearColor(uint color);
		void				setClearColor(int red, int green, int blue, int alpha);

		void				cleanScreen();

		// Set font
		void				setFont(Font* font);

		// Get client width and height
		int					getClientWidth();
		int					getClientHeight();

		// Set transform info
		void				rotate(float alpha);
		void				rotate(float alpha, int x, int y);
		void				translate(int x, int y);
		void				scale(float sx, float sy);

		void				setTransform(const AffineTransform& transform);
		AffineTransform&	getTransform();

	private:
		void				draw(int x, int y, int width, int height, float *uv = nullptr, uint texture_id = 0, uint flipping = 0);
	};
}