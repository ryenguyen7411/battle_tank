#ifndef __COMPONENTS_H__
#define __COMPONENTS_H__

#include <vector>

using namespace stdio_fw;

class Transform;
class Renderer;

class Component
{
public:
	CompType	m_type;
	Component(){}
	virtual ~Component(){}
};

class Transform : public Component
{
public:
	Vec3	m_position;
	Vec3	m_rotation;
	Vec3	m_scale;

	Transform(Vec3 _position = Vec3().zero(), Vec3 _rotation = Vec3().zero(), Vec3 _scale = Vec3().one())
	{
		m_position = _position;
		m_rotation = _rotation;
		m_scale = _scale;

		m_type = CompType::COMP_TRANSFORM;
	}
	~Transform()
	{

	}
};


class Renderer : public Component
{
public:
	Image*			m_sprite;
	Rect			m_bound;

	Renderer(Image* _sprite = NULL)
	{
		m_sprite = _sprite;

		m_type = CompType::COMP_RENDERER;
	}
	~Renderer()
	{
		m_sprite->unloadImage();
		SAFE_DEL(m_sprite);
	}
};


class Collider2D : public Component
{

};


//struct Animation : public Component
//{
//	ImageList*			m_image_list;
//	ImageListIterator	m_current_frame;
//
//	Animation(ImageList* _image_list)
//	{
//		m_image_list = _image_list;
//		m_current_frame = m_image_list->begin();
//	}
//	~Animation()
//	{
//		while(!m_image_list->empty())
//		{
//			m_image_list->back()->unloadImage();
//			SAFE_DEL(m_image_list->back());
//			m_image_list->pop_back();
//		}
//
//		SAFE_DEL(m_image_list);
//	}
//};



//struct Label : public Component
//{
//	Image*		m_font;
//	char*		m_text;
//
//	char*		m_char;
//	Rect**		m_char_map;
//
//	int			m_char_distance;
//	int*		m_char_offset;
//
//	Label(Image* _font, char* _text, char* _char, Rect** _char_map, int _char_distance, int* _char_offset)
//	{
//		m_font = _font;
//		m_text = _text;
//
//		m_char = _char;
//		m_char_map = _char_map;
//
//		m_char_distance = _char_distance;
//		m_char_offset = _char_offset;
//	}
//	~Label()
//	{
//		m_font->unloadImage();
//		SAFE_DEL(m_font);
//
//		for(int i = 0; i < strlen(m_char); i++)
//			delete m_char_map[i];
//		SAFE_DEL_ARR(m_char_map);
//
//		SAFE_DEL_ARR(m_char);
//		SAFE_DEL_ARR(m_char_offset);
//	}
//};
//
//
//
//struct SpriteSheet : public Component
//{
//	Image*	m_spritesheet;
//	int		m_frame_count;
//	Rect**	m_frame_map;
//
//	int		m_current_frame;
//
//	SpriteSheet(Image* spritesheet, int frame_count, Rect** frame_map)
//	{
//		m_spritesheet = spritesheet;
//		m_frame_count = frame_count;
//		m_frame_map = frame_map;
//
//		m_current_frame = 1;
//	}
//	~SpriteSheet()
//	{
//		m_spritesheet->unloadImage();
//		SAFE_DEL(m_spritesheet);
//
//		for(int i = 0; i < m_frame_count; i++)
//			delete m_frame_map[i];
//		SAFE_DEL_ARR(m_frame_map);
//	}
//};

#endif