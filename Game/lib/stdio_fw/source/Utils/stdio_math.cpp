#include "stdio_fw.h"
#include <math.h>

namespace stdio_fw
{
	//Vector 2
	float Vec2::length()
	{
		return sqrt(x*x + y*y);
	}

	Vec2 & Vec2::normalize()
	{
		float lenInv = 1.0f / length();
		x *= lenInv;
		y *= lenInv;

		return *this;
	}

	Vec2 Vec2::operator + (const Vec2 & Vec)
	{
		return Vec2(x + Vec.x, y + Vec.y);
	}

	Vec2 & Vec2::operator += (const Vec2 & Vec)
	{
		x += Vec.x;
		y += Vec.y;

		return *this;
	}

	Vec2 Vec2::operator - ()
	{
		return Vec2(-x, -y);
	}

	Vec2 Vec2::operator - (const Vec2 & Vec)
	{
		return Vec2(x - Vec.x, y - Vec.y);
	}

	Vec2 & Vec2::operator -= (const Vec2 & Vec)
	{
		x -= Vec.x;
		y -= Vec.y;

		return *this;
	}

	Vec2 Vec2::operator * (float k)
	{
		return Vec2(x * k, y * k);
	}

	Vec2 & Vec2::operator *= (float k)
	{
		x *= k;
		y *= k;

		return *this;
	}

	Vec2 Vec2::operator / (float k)
	{
		float kInv = 1.0f / k;
		return Vec2(x * kInv, y * kInv);
	}

	Vec2 & Vec2::operator /= (float k)
	{
		return operator *= (1.0f / k);
	}

	Vec2 & Vec2::operator = (const Vec2 & Vec)
	{
		x = Vec.x;
		y = Vec.y;

		return *this;
	}

	float Vec2::operator [] (uint idx)
	{
		return (&x)[idx];
	}

	Vec2 Vec2::modulate(const Vec2 & Vec)
	{
		return Vec2(x * Vec.x, y * Vec.y);
	}

	float Vec2::dot(const Vec2 & Vec)
	{
		return x * Vec.x + y * Vec.y;
	}

	Vec3 Vec3::zero()
	{
		return Vec3(0.0f, 0.0f, 0.0f);
	}

	Vec3 Vec3::one()
	{
		return Vec3(1.0f, 1.0f, 1.0f);
	}

	// Vector3
	float Vec3::length()
	{
		return sqrt(x*x + y*y + z*z);
	}

	Vec3 & Vec3::normalize()
	{
		float lenInv = 1.0f / length();
		x *= lenInv;
		y *= lenInv;
		z *= lenInv;

		return *this;
	}

	Vec3 Vec3::operator + (const Vec3 & Vec)
	{
		return Vec3(x + Vec.x, y + Vec.y, z + Vec.z);
	}

	Vec3 & Vec3::operator += (const Vec3 & Vec)
	{
		x += Vec.x;
		y += Vec.y;
		z += Vec.z;

		return *this;
	}

	Vec3 Vec3::operator - ()
	{
		return Vec3(-x, -y, -z);
	}

	Vec3 Vec3::operator - (const Vec3 & Vec)
	{
		return Vec3(x - Vec.x, y - Vec.y, z - Vec.z);
	}

	Vec3 & Vec3::operator -= (const Vec3 & Vec)
	{
		x -= Vec.x;
		y -= Vec.y;
		z -= Vec.z;

		return *this;
	}

	Vec3 Vec3::operator * (float k)
	{
		return Vec3(x * k, y * k, z * k);
	}

	Vec3 & Vec3::operator *= (float k)
	{
		x *= k;
		y *= k;
		z *= k;

		return *this;
	}

	Vec3 Vec3::operator / (float k)
	{
		float kInv = 1.0f / k;
		return Vec3(x * kInv, y * kInv, z * kInv);
	}

	Vec3 & Vec3::operator /= (float k)
	{
		return operator *= (1.0f / k);
	}

	Vec3 & Vec3::operator = (const Vec3 & Vec)
	{
		x = Vec.x;
		y = Vec.y;
		z = Vec.z;

		return *this;
	}

	float Vec3::operator [] (uint idx)
	{
		return (&x)[idx];
	}

	Vec3 Vec3::modulate(const Vec3 & Vec)
	{
		return Vec3(x * Vec.x, y * Vec.y, z * Vec.z);
	}

	float Vec3::dot(const Vec3 & Vec)
	{
		return x * Vec.x + y * Vec.y + z * Vec.z;
	}

	Vec3 Vec3::cross(const Vec3 & Vec)
	{
		return Vec3(y * Vec.z - z * Vec.y, z * Vec.x - x * Vec.z, x * Vec.y - y * Vec.x);
	}

	Vec3 Vec3::operator * (const Mat3 & m)
	{
		Vec3 res;
		res.x = x * m.m[0][0] + y * m.m[1][0] + z * m.m[2][0];
		res.y = x * m.m[0][1] + y * m.m[1][1] + z * m.m[2][1];
		res.z = x * m.m[0][2] + y * m.m[1][2] + z * m.m[2][2];		

		return res;
	}

	// Rect
	Rect::Rect(float _x, float _y, float _width, float _height) :
		x(_x), y(_y), width(_width), height(_height){}

	Rect::Rect() :x(0), y(0), width(0), height(0) {}

	// Additional
	bool Rect::operator==(Rect b)
	{
		return x == b.x && y == b.y && width == b.width && height == b.height;
	}

	bool Rect::operator!=(Rect b)
	{
		return x != b.x || y != b.y || width != b.width || height != b.height;
	}

	bool Rect::checkAABB(Rect b)
	{
		return !(x + width < b.x || y + height < b.y || x > b.x + b.width || y > b.y + b.height);
	}
	//////////////////////////////////////////////

	// Mat3 3x3
	Mat3::Mat3(float val)
	{
		m[0][0] = val; m[0][1] = val; m[0][2] = val;
		m[1][0] = val; m[1][1] = val; m[1][2] = val;
		m[2][0] = val; m[2][1] = val; m[2][2] = val;		
	}

	Mat3::Mat3(const Mat3 & mat)
	{
		m[0][0] = mat.m[0][0]; m[0][1] = mat.m[0][1]; m[0][2] = mat.m[0][2];
		m[1][0] = mat.m[1][0]; m[1][1] = mat.m[1][1]; m[1][2] = mat.m[1][2];
		m[2][0] = mat.m[2][0]; m[2][1] = mat.m[2][1]; m[2][2] = mat.m[2][2];		
	}

	Mat3 & Mat3::setZero()
	{
		m[0][0] = 0.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 0.0f; m[1][2] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 0.0f;		

		return *this;
	}

	Mat3 & Mat3::setIdentity()
	{
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;		

		return *this;
	}

	Mat3 & Mat3::setRotation(float angle)
	{
		float s = sinf(angle);
		float c = cosf(angle);
		m[0][0] = c; m[0][1] = s; m[0][2] = 0.0f;
		m[1][0] = -s; m[1][1] = c; m[1][2] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;

		return *this;
	}

	Mat3 & Mat3::setScale(float scale)
	{
		m[0][0] = scale; m[0][1] = 0.0f;  m[0][2] = 0.0f;
		m[1][0] = 0.0f;  m[1][1] = scale; m[1][2] = 0.0f;
		m[2][0] = 0.0f;  m[2][1] = 0.0f;  m[2][2] = 1.0f;		

		return *this;
	}

	Mat3 & Mat3::setScale(float scaleX, float scaleY)
	{
		m[0][0] = scaleX; m[0][1] = 0.0f;   m[0][2] = 0.0f;
		m[1][0] = 0.0f;   m[1][1] = scaleY; m[1][2] = 0.0f;
		m[2][0] = 0.0f;   m[2][1] = 0.0f;   m[2][2] = 1.0f;
		
		return *this;
	}

	Mat3 & Mat3::setScale(float * pScale)
	{
		m[0][0] = pScale[0];   m[0][1] = 0.0f;        m[0][2] = 0.0f; 
		m[1][0] = 0.0f;        m[1][1] = pScale[1];   m[1][2] = 0.0f; 
		m[2][0] = 0.0f;        m[2][1] = 0.0f;        m[2][2] = 1.0f; 

		return *this;
	}

	Mat3 & Mat3::setScale(const Vec2 & scaleVec)
	{
		m[0][0] = scaleVec.x; m[0][1] = 0.0f;       m[0][2] = 0.0f;
		m[1][0] = 0.0f;       m[1][1] = scaleVec.y; m[1][2] = 0.0f;
		m[2][0] = 0.0f;       m[2][1] = 0.0f;       m[2][2] = 1.0f;		

		return *this;
	}

	Mat3 & Mat3::setTranslation(float x, float y)
	{
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;		
		m[2][0] = x;	m[2][1] = y;	m[2][2] = 1.0f;

		return *this;
	}

	Mat3 & Mat3::setTranslation(float *pTrans)
	{
		m[0][0] = 1.0f;			m[0][1] = 0.0f;			m[0][2] = 0.0f;
		m[1][0] = 0.0f;			m[1][1] = 1.0f;			m[1][2] = 0.0f;
		m[2][0] = pTrans[0];	m[2][1] = pTrans[1];	m[2][2] = 1.0f;

		return *this;
	}

	Mat3 & Mat3::setTranslation(const Vec2 &vec)
	{
		m[0][0] = 1.0f;		m[0][1] = 0.0f;		m[0][2] = 0.0f;
		m[1][0] = 0.0f;		m[1][1] = 1.0f;		m[1][2] = 0.0f;
		m[2][0] = vec.x;	m[2][1] = vec.y;	m[2][2] = 1.0f;

		return *this;
	}

	Mat3 Mat3::transpose()
	{
		Mat3 res;
		res.m[0][0] = m[0][0]; res.m[0][1] = m[1][0]; res.m[0][2] = m[2][0];
		res.m[1][0] = m[0][1]; res.m[1][1] = m[1][1]; res.m[1][2] = m[2][1];
		res.m[2][0] = m[0][2]; res.m[2][1] = m[1][2]; res.m[2][2] = m[2][2];
		
		return res;
	}

	Mat3 Mat3::operator + (const Mat3 & mat)
	{
		Mat3 res(*this);
		res += mat;
		return res;
	}

	Mat3 & Mat3::operator += (const Mat3 & mat)
	{
		m[0][0] += mat.m[0][0]; m[0][1] += mat.m[0][1]; m[0][2] += mat.m[0][2];
		m[1][0] += mat.m[1][0]; m[1][1] += mat.m[1][1]; m[1][2] += mat.m[1][2];
		m[2][0] += mat.m[2][0]; m[2][1] += mat.m[2][1]; m[2][2] += mat.m[2][2];
		
		return *this;
	}

	Mat3 Mat3::operator - (const Mat3 & mat)
	{
		Mat3 res(*this);
		res -= mat;
		return res;
	}

	Mat3 & Mat3::operator -= (const Mat3 & mat)
	{
		m[0][0] -= mat.m[0][0]; m[0][1] -= mat.m[0][1]; m[0][2] -= mat.m[0][2];
		m[1][0] -= mat.m[1][0]; m[1][1] -= mat.m[1][1]; m[1][2] -= mat.m[1][2];
		m[2][0] -= mat.m[2][0]; m[2][1] -= mat.m[2][1]; m[2][2] -= mat.m[2][2];		

		return *this;
	}

	Mat3 Mat3::operator * (const Mat3 & mat)
	{
		Mat3 res;
		res.m[0][0] = m[0][0] * mat.m[0][0] + m[0][1] * mat.m[1][0] + m[0][2] * mat.m[2][0];
		res.m[0][1] = m[0][0] * mat.m[0][1] + m[0][1] * mat.m[1][1] + m[0][2] * mat.m[2][1];
		res.m[0][2] = m[0][0] * mat.m[0][2] + m[0][1] * mat.m[1][2] + m[0][2] * mat.m[2][2];		

		res.m[1][0] = m[1][0] * mat.m[0][0] + m[1][1] * mat.m[1][0] + m[1][2] * mat.m[2][0];
		res.m[1][1] = m[1][0] * mat.m[0][1] + m[1][1] * mat.m[1][1] + m[1][2] * mat.m[2][1];
		res.m[1][2] = m[1][0] * mat.m[0][2] + m[1][1] * mat.m[1][2] + m[1][2] * mat.m[2][2];		

		res.m[2][0] = m[2][0] * mat.m[0][0] + m[2][1] * mat.m[1][0] + m[2][2] * mat.m[2][0];
		res.m[2][1] = m[2][0] * mat.m[0][1] + m[2][1] * mat.m[1][1] + m[2][2] * mat.m[2][1];
		res.m[2][2] = m[2][0] * mat.m[0][2] + m[2][1] * mat.m[1][2] + m[2][2] * mat.m[2][2];	

		return res;
	}

	Mat3 Mat3::operator * (float k)
	{
		Mat3 mat(*this);
		mat *= k;
		return mat;
	}

	Mat3 & Mat3::operator *= (float k)
	{
		m[0][0] *= k; m[0][1] *= k; m[0][2] *= k;
		m[1][0] *= k; m[1][1] *= k; m[1][2] *= k;
		m[2][0] *= k; m[2][1] *= k; m[2][2] *= k;	

		return *this;
	}


	Vec3 Mat3::operator * (const Vec3 & vec)
	{
		Vec3 res;
		res.x = vec.x * m[0][0] + vec.y * m[0][1] + vec.z * m[0][2];
		res.y = vec.x * m[1][0] + vec.y * m[1][1] + vec.z * m[1][2];
		res.z = vec.x * m[2][0] + vec.y * m[2][1] + vec.z * m[2][2];		

		return res;
	}

	Mat3 & Mat3::operator = (const Mat3 & mat)
	{
		m[0][0] = mat.m[0][0]; m[0][1] = mat.m[0][1]; m[0][2] = mat.m[0][2];
		m[1][0] = mat.m[1][0]; m[1][1] = mat.m[1][1]; m[1][2] = mat.m[1][2];
		m[2][0] = mat.m[2][0]; m[2][1] = mat.m[2][1]; m[2][2] = mat.m[2][2];

		return *this;
	}
}