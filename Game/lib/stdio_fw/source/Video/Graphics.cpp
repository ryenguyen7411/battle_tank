#include "stdio_fw.h"

#include "GL\glew.h"
#include "Video\Graphics.h"
#include "Video\Image.h"

namespace stdio_fw
{
	GLuint createProgram(const char* vertex_src, const char* fragment_src);
	GLuint loadShader(GLenum type, const char* src);

	Graphics::Graphics() :m_curFont(nullptr)
	{	
	}

	Graphics::~Graphics()
	{
	}

	ErrorCode Graphics::initGraphics(int screenW, int screenH)
	{
		m_iScreenW = screenW;
		m_iScreenH = screenH;

		const char* solid_obj_vertex_shader_src =
			"#version 120\n"
			"attribute vec2 a_pos;\n"			
			"void main()\n"
			"{\n"			
			"gl_Position = vec4(a_pos, 1.0, 1.0);\n"
			"}\n";

		const char* solid_obj_fragment_shader_src = 
			"#version 120\n"
			"uniform vec4 u_color;\n"
			"void main()\n"
			"{\n"
			"gl_FragColor = u_color;\n"
			"}\n";

		m_aPrograms[PRG_SOL] = createProgram(solid_obj_vertex_shader_src, solid_obj_fragment_shader_src);

		m_cachedLocs[CACHED_LOC::ATT_POSITION0] = glGetAttribLocation(m_aPrograms[PRG_SOL], "a_pos");		
		m_cachedLocs[CACHED_LOC::UNI_COLOR0] = glGetUniformLocation(m_aPrograms[PRG_SOL], "u_color");

		// For image
		const char* img_vertex_shader_src =
			"#version 120\n"
			"attribute vec2 a_pos;\n"
			"attribute vec2 a_uv;\n"			
			"varying vec2 v_uv;\n"
			"void main()\n"
			"{\n"
			"gl_Position = vec4(a_pos, 1.0, 1.0);\n"
			"v_uv = a_uv;\n"
			"}\n";

		const char* img_fragment_shader_src =
			"#version 120\n"
			"uniform sampler2D u_tex;\n"
			"varying vec2 v_uv;\n"
			"void main()\n"
			"{\n"
			"gl_FragColor = texture2D(u_tex, v_uv);\n"
			"}\n";

		m_aPrograms[PRG_IMG] = createProgram(img_vertex_shader_src, img_fragment_shader_src);
		
		m_cachedLocs[CACHED_LOC::ATT_POSITION1] = glGetAttribLocation(m_aPrograms[PRG_IMG], "a_pos");		
		m_cachedLocs[CACHED_LOC::ATT_TEXCOORD1] = glGetAttribLocation(m_aPrograms[PRG_IMG], "a_uv");
		m_cachedLocs[CACHED_LOC::UNI_TEXTURE1] = glGetUniformLocation(m_aPrograms[PRG_IMG], "u_tex");

		// For text rendering
		const char* font_vertex_shader_src =
			"#version 120\n"
			"attribute vec2 a_pos;\n"
			"attribute vec2 a_uv;\n"			
			"varying vec2 v_uv;\n"
			"void main()\n"
			"{\n"
			"gl_Position = vec4(a_pos, 1.0, 1.0);\n"
			"v_uv = a_uv;\n"
			"}\n";

		const char* font_fragment_shader_src =
			"#version 120\n"
			"uniform sampler2D u_tex;\n"
			"uniform vec4 u_color;\n"
			"varying vec2 v_uv;\n"
			"void main()\n"
			"{\n"
			"gl_FragColor = u_color * vec4(1.0, 1.0, 1.0, texture2D(u_tex, v_uv).a);\n"
			"}\n";

		m_aPrograms[PRG_FON] = createProgram(font_vertex_shader_src, font_fragment_shader_src);

		m_cachedLocs[CACHED_LOC::ATT_POSITION2] = glGetAttribLocation(m_aPrograms[PRG_FON], "a_pos");
		m_cachedLocs[CACHED_LOC::ATT_TEXCOORD2] = glGetAttribLocation(m_aPrograms[PRG_FON], "a_uv");
		m_cachedLocs[CACHED_LOC::UNI_TEXTURE2] = glGetUniformLocation(m_aPrograms[PRG_FON], "u_tex");
		m_cachedLocs[CACHED_LOC::UNI_COLOR2] = glGetUniformLocation(m_aPrograms[PRG_FON], "u_color");

		return ErrorCode::ERR_NO_ERROR;
	}

	void Graphics::fillRect(int x, int y, int width, int height)
	{
		draw(x, y, width, height);
	}

	void Graphics::fillRect(Rect rect)
	{
		draw(rect.x, rect.y, rect.width, rect.height);
	}

	void Graphics::drawRect(int x, int y, int width, int height, int weight)
	{
		//Top
		fillRect(x, y, width, weight);
		//Bottom
		fillRect(x, y + height - weight, width, weight);
		//Left
		fillRect(x, y + weight, weight, height - (weight << 1));
		//Right
		fillRect(x + width - weight, y + weight, weight, height - (weight << 1));
	}

	void Graphics::drawRect(Rect rect, int weight)
	{
		drawRect(rect.x, rect.y, rect.width, rect.height, weight);
	}

	void Graphics::drawImage(Image* img, int x, int y, uint flipping)
	{
		draw(x, y, img->getWidth(), img->getHeight(), nullptr, img->m_texID, flipping);
	}

	void Graphics::drawImage(Image* img, Rect rect, uint flipping)
	{
		draw(rect.x, rect.y, rect.width, rect.height, nullptr, img->m_texID, flipping);
	}

	void Graphics::drawRegion(Image* img, int x, int y, int width, int height, int src_x, int src_y, int src_w, int src_h, uint flipping)
	{
		float uv[]
		{
			X2UVGL(src_x, img->getWidth()), Y2UVGL(src_y, img->getHeight()),
			X2UVGL(src_x + src_w, img->getWidth()), Y2UVGL(src_y, img->getHeight()),
			X2UVGL(src_x, img->getWidth()), Y2UVGL(src_y + src_h, img->getHeight()),
			X2UVGL(src_x + src_w, img->getWidth()), Y2UVGL(src_y + src_h, img->getHeight())
		};
		draw(x, y, width, height, uv, img->m_texID, flipping);
	}

	void Graphics::drawRegion(Image* img, Rect src, Rect dest, uint flipping)
	{
		drawRegion(img, src.x, src.y, src.width, src.height, dest.x, dest.y, dest.width, dest.height, flipping);
	}

	void Graphics::drawLine(int x1, int y1, int x2, int y2)
	{
		// Compute vertices array
		float vertices[] = {
			XSCREEN2GL(x1, m_iScreenW), YSCREEN2GL(y1, m_iScreenH),
			XSCREEN2GL(x2, m_iScreenW), YSCREEN2GL(y2, m_iScreenH)
		};
		
		glUseProgram(m_aPrograms[PRG_SOL]);

		// Transfer data to verties
		GLint posLoc = m_cachedLocs[CACHED_LOC::ATT_POSITION0];
		if (posLoc != -1)
		{
			glVertexAttribPointer(posLoc, 2, GL_FLOAT, GL_FALSE, 0, vertices);
			glEnableVertexAttribArray(posLoc);
		}

		GLint colorUniLoc = m_cachedLocs[CACHED_LOC::UNI_COLOR0];
		if (colorUniLoc != -1)
		{
			glUniform4fv(colorUniLoc, 1, &m_drawColor[0]);
		}

		glDrawArrays(GL_LINES, 0, 2);
	}

	void Graphics::drawLine(Vec2 p1, Vec2 p2)
	{
		drawLine(p1.x, p1.y, p2.x, p2.y);
	}

	void Graphics::drawText(const char* text, int x, int y, int scale_x, int scale_y)
	{
		if (!m_curFont)
			return;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glUseProgram(m_aPrograms[CACHED_PROGRAM::PRG_FON]);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Active texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Font::m_texID);
		glUniform1i(m_cachedLocs[CACHED_LOC::UNI_TEXTURE2], 0);

		// Transfer color					
		glUniform4fv(m_cachedLocs[CACHED_LOC::UNI_COLOR2], 1, &m_drawColor[0]);

		// Transfer uv
		GLint uvLoc = m_cachedLocs[CACHED_LOC::ATT_TEXCOORD2];
		float default_uv[] = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,			
		};

		glVertexAttribPointer(uvLoc, 2, GL_FLOAT, GL_FALSE, 0, default_uv);
		glEnableVertexAttribArray(uvLoc);
		
		// Draw individual character
		for (const char* p = text; *p; p++)
		{
			if (FT_Load_Char(m_curFont->m_face, *p, FT_LOAD_RENDER))
				continue;

			FT_GlyphSlot gs = m_curFont->m_face->glyph;

			// Tranfer texture
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_ALPHA,
				gs->bitmap.width,
				gs->bitmap.rows,
				0,
				GL_ALPHA,
				GL_UNSIGNED_BYTE,
				gs->bitmap.buffer
				);

			float px = x + gs->bitmap_left * scale_x;
			float py = y - gs->bitmap_top * scale_x;
			float w = gs->bitmap.width * scale_x;
			float h = gs->bitmap.rows * scale_y;

			// Compute vertices array
			float vertices[] = {
				XSCREEN2GL(px, m_iScreenW), YSCREEN2GL(py, m_iScreenH),
				XSCREEN2GL(px + w, m_iScreenW), YSCREEN2GL(py, m_iScreenH),
				XSCREEN2GL(px, m_iScreenW), YSCREEN2GL(py + h, m_iScreenH),
				XSCREEN2GL(px + w, m_iScreenW), YSCREEN2GL(py + h, m_iScreenH)
			};

			// Transfer data to verties
			GLint posLoc = m_cachedLocs[CACHED_LOC::ATT_POSITION2];
			glVertexAttribPointer(posLoc, 2, GL_FLOAT, GL_FALSE, 0, vertices);
			glEnableVertexAttribArray(posLoc);

			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			x += (gs->advance.x >> 6) * scale_x;
			y += (gs->advance.y >> 6) * scale_y;
		}
		
		glUseProgram(0);
		glDisable(GL_BLEND);
	}

	void Graphics::draw(int x, int y, int width, int height, float *uv, uint texture_id, uint flipping)
	{
		//enable blend
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Active the corresponding programe
		GLint activeProgram = texture_id == 0 ? m_aPrograms[PRG_SOL] : m_aPrograms[PRG_IMG];
		glUseProgram(activeProgram);

		// Compute vertices value
		Vec3 v1(x, y, 1.0f);
		Vec3 v2(x + width, y, 1.0f);
		Vec3 v3(x, y + height, 1.0f);
		Vec3 v4(x + width, y + height, 1.0f);
		
		const Mat3& tranform_mat = m_affineTransform.getMatrix();
		v1 = v1 * tranform_mat;
		v2 = v2 * tranform_mat;
		v3 = v3 * tranform_mat;
		v4 = v4 * tranform_mat;		

		// Compute vertices array
		float vertices[] = {
			XSCREEN2GL(v1.x, m_iScreenW), YSCREEN2GL(v1.y, m_iScreenH),
			XSCREEN2GL(v2.x, m_iScreenW), YSCREEN2GL(v2.y, m_iScreenH),
			XSCREEN2GL(v3.x, m_iScreenW), YSCREEN2GL(v3.y, m_iScreenH),
			XSCREEN2GL(v4.x, m_iScreenW), YSCREEN2GL(v4.y, m_iScreenH),			
		};

		// Transfer data to verties
		GLint posLoc = texture_id == 0 ? m_cachedLocs[CACHED_LOC::ATT_POSITION0] :
			m_cachedLocs[CACHED_LOC::ATT_POSITION1];
		if (posLoc != -1)
		{
			glVertexAttribPointer(posLoc, 2, GL_FLOAT, GL_FALSE, 0, vertices);
			glEnableVertexAttribArray(posLoc);
		}
		
		if (texture_id == 0)	// We draw solid object
		{
			activeProgram = m_aPrograms[PRG_SOL];
			// Transfer color			
			glUniform4fv(m_cachedLocs[CACHED_LOC::UNI_COLOR0], 1, &m_drawColor[0]);
		}			
		else
		{
			// Bind texture and send uv coordinates
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture_id);
			glUniform1i(m_cachedLocs[CACHED_LOC::UNI_TEXTURE1], 0);			

			GLint uvLoc = m_cachedLocs[CACHED_LOC::ATT_TEXCOORD1];			
			float default_uv[] = {
				0.0f, 1.0f,
				1.0f, 1.0f,
				0.0f, 0.0f,
				1.0f, 0.0f
			};

			if (uv == nullptr)
				uv = default_uv;

			if (flipping & FLIP_Y)
			{
				float t1 = uv[0], t2 = uv[2];
				uv[0] = uv[4] = -t2;
				uv[2] = uv[6] = -t1;
			}

			if (flipping & FLIP_X)
			{
				float t1 = uv[1], t2 = uv[5];
				uv[1] = uv[3] = -t2;				
				uv[5] = uv[7] = -t1;				 
			}

			glVertexAttribPointer(uvLoc, 2, GL_FLOAT, GL_FALSE, 0, uv);
			glEnableVertexAttribArray(uvLoc);			
		}	
		
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		// Disable blend
		glDisable(GL_BLEND);
		glUseProgram(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Graphics::setColor(uint color)
	{
		// [0000 0000] [0000 0000] [0000 0000] [0000 0000]
		m_drawColor[0] = ((color >> 24) & 0xFF) / 255.0f;
		m_drawColor[1] = ((color >> 16) & 0xFF) / 255.0f;
		m_drawColor[2] = ((color >> 8) & 0xFF) / 255.0f;
		m_drawColor[3] = (color & 0xFF) / 255.0f;		
	}

	void Graphics::setColor(int red, int green, int blue, int alpha)
	{
		m_drawColor[0] = red / 255.0f;
		m_drawColor[1] = green / 255.0f;
		m_drawColor[2] = blue / 255.0f;
		m_drawColor[3] = alpha / 255.0f;
	}

	void Graphics::setClearColor(uint color)
	{
		// [0000 0000] [0000 0000] [0000 0000] [0000 0000]
		m_clearColor[0] = ((color >> 24) & 0xFF) / 255.0f;
		m_clearColor[1] = ((color >> 16) & 0xFF) / 255.0f;
		m_clearColor[2] = ((color >> 8) & 0xFF) / 255.0f;
		m_clearColor[3] = 1.0f;
	}

	void Graphics::setClearColor(int red, int green, int blue, int alpha)
	{
		m_clearColor[0] = red / 255.0f;
		m_clearColor[1] = green / 255.0f;
		m_clearColor[2] = blue / 255.0f;
		m_clearColor[3] = alpha / 255.0f;
	}

	void Graphics::cleanScreen()
	{
		glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	}

	void Graphics::setFont(Font* font)
	{
		if (font)
			m_curFont = font;
	}

	int Graphics::getClientWidth()
	{
		return m_iScreenW;
	}

	int Graphics::getClientHeight()
	{
		return m_iScreenH;
	}

	void Graphics::rotate(float alpha)
	{
		m_affineTransform.rotate(alpha);
	}

	void Graphics::rotate(float alpha, int x, int y)
	{
		m_affineTransform.rotate(alpha, x, y);
	}

	void Graphics::translate(int x, int y)
	{
		m_affineTransform.translate(x, y);
	}

	void Graphics::scale(float sx, float sy)
	{
		m_affineTransform.scale(sx, sy);
	}

	void Graphics::setTransform(const AffineTransform& transform)
	{
		m_affineTransform = transform;
	}

	AffineTransform& Graphics::getTransform()
	{
		return m_affineTransform;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////
	GLuint loadShader(GLenum type, const char* src)
	{
		GLuint shader = glCreateShader(type);
		if (shader)
		{
			glShaderSource(shader, 1, &src, NULL);
			glCompileShader(shader);
			GLint compiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
			if (!compiled)
			{
				GLint infoLen = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
				if (infoLen)
				{
					char* buf = (char*)malloc(infoLen);
					if (buf)
					{
						glGetShaderInfoLog(shader, infoLen, NULL, buf);
						char msg[512];
						sprintf_s(msg, 512, "Could not compile shader %d:\n%s\n", type, buf);
						ASSERT_MSG(false, msg);
						free(buf);
					}
					glDeleteShader(shader);
					shader = 0;
				}
			}
		}
		return shader;
	}

	GLuint createProgram(const char* vertex_src, const char* fragment_src)
	{
		GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertex_src);
		if (!vertexShader)
		{
			return 0;
		}

		GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, fragment_src);
		if (!pixelShader)
		{
			return 0;
		}

		GLuint program = glCreateProgram();
		if (program)
		{
			glAttachShader(program, vertexShader);
			glAttachShader(program, pixelShader);

			glLinkProgram(program);
			GLint linkStatus = GL_FALSE;
			glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
			if (linkStatus != GL_TRUE)
			{
				GLint bufLength = 0;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
				if (bufLength)
				{
					char* buf = (char*)malloc(bufLength);
					if (buf)
					{
						glGetProgramInfoLog(program, bufLength, NULL, buf);
						char msg[512];
						sprintf_s(msg, 512, "Could not link program:\n%s\n", buf);
						ASSERT_MSG(false, msg);
						free(buf);
					}
				}
				glDeleteProgram(program);
				program = 0;
			}
		}
		if (!program)
		{
			ASSERT_MSG(false, "Could not create program.");			
		}
		return program;
	}
}
