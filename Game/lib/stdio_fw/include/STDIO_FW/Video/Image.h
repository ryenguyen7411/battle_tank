#pragma once

namespace stdio_fw
{
	enum IMAGE_FILTER_MODE
	{		
		FILTER_NEAREST = 0x2600,
		FILTER_LINEAR = 0x2601,
		FILTER_NEAREST_MIPMAP_NEAREST = 0x2700,
		FILTER_LINEAR_MIPMAP_NEAREST = 0x2701,
		FILTER_NEAREST_MIPMAP_LINEAR = 0x2702,
		FILTER_LINEAR_MIPMAP_LINEAR = 0x2703
	};

	class Image
	{
		friend class Graphics;
		char		m_imgPath[256];
		uint		m_texID;

		uint		m_imgWidth;
		uint		m_imgHeight;
		uint		m_imgBPP;

		bool		m_isLoaded;
		bool		m_useMipmap;
		uint		m_minFilterMode;
		uint		m_magFilterMode;

	public:
		Image(const char* path, IMAGE_FILTER_MODE minFilter = FILTER_NEAREST, 
									IMAGE_FILTER_MODE magFilter = FILTER_NEAREST,
									bool useMipmap = false);
		~Image();

		ErrorCode			loadImage();
		void				unloadImage();

		uint		getWidth() { return m_imgWidth; };
		uint		getHeight() { return m_imgHeight; };

	private:
		byte*		loadImageData(uint &pow2w, uint &pow2h);
		uint		roundUpPow2(uint n);
	};
}
