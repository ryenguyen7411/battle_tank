#pragma once

namespace stdio_fw
{
	struct Vec2
	{
		//Constructors
		Vec2() : x(0.0f), y(0.0f){}
		Vec2(float _x, float _y) : x(_x), y(_y) {}
		Vec2(float * pArg) : x(pArg[0]), y(pArg[1]) {}
		Vec2(const Vec2 & Vec) : x(Vec.x), y(Vec.y) {}

		//Vector's operations
		float length();
		Vec2 & normalize();
		Vec2 operator + (const Vec2 & Vec);
		Vec2 & operator += (const Vec2 & Vec);
		Vec2 operator - ();
		Vec2 operator - (const Vec2 & Vec);
		Vec2 & operator -= (const Vec2 & Vec);
		Vec2 operator * (float k);
		Vec2 & operator *= (float k);
		Vec2 operator / (float k);
		Vec2 & operator /= (float k);
		Vec2 & operator = (const Vec2 & Vec);
		Vec2 modulate(const Vec2 & Vec);
		float dot(const Vec2 & Vec);

		//access to elements
		float operator [] (uint idx);

		//data members
		float x;
		float y;
	};

	struct Mat3;
	struct Vec3
	{
		//Constructors
		Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
		Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
		Vec3(float * pArg) : x(pArg[0]), y(pArg[1]), z(pArg[2]) {}
		Vec3(const Vec3 & Vec) : x(Vec.x), y(Vec.y), z(Vec.z) {}

		Vec3 zero();
		Vec3 one();
		//Vector's operations
		float length();
		Vec3 & normalize();
		Vec3 operator + (const Vec3 & Vec);
		Vec3 & operator += (const Vec3 & Vec);
		Vec3 operator - ();
		Vec3 operator - (const Vec3 & Vec);
		Vec3 & operator -= (const Vec3 & Vec);
		Vec3 operator * (float k);
		Vec3 & operator *= (float k);
		Vec3 operator / (float k);
		Vec3 & operator /= (float k);
		Vec3 & operator = (const Vec3 & Vec);
		Vec3 modulate(const Vec3 & Vec);
		float dot(const Vec3 & Vec);
		Vec3 cross(const Vec3 & Vec);

		// access to elements
		float operator [] (uint idx);

		//matrix multiplication
		Vec3 operator * (const Mat3 & m);

		// data members
		float x;
		float y;
		float z;
	};

	struct Mat3
	{
		//constructors
		Mat3() {}
		Mat3(float val);
		Mat3(const Mat3 & mat);

		// Mat3 operations
		Mat3 & setZero();
		Mat3 & setIdentity();

		Mat3 & setRotation(float angle);		

		Mat3 & setScale(float scale);
		Mat3 & setScale(float scaleX, float scaleY);
		Mat3 & setScale(float * pScale);
		Mat3 & setScale(const Vec2 &scaleVec);

		Mat3 & setTranslation(float x, float y);
		Mat3 & setTranslation(float *pTrans);
		Mat3 & setTranslation(const Vec2 &vec);

		Mat3 transpose();

		Mat3 operator + (const Mat3 & mat);
		Mat3 & operator += (const Mat3 & mat);
		Mat3 operator - (const Mat3 & mat);
		Mat3 &operator -= (const Mat3 & mat);

		Mat3 operator * (const Mat3 & mat);
		Mat3 operator * (float k);
		Mat3 & operator *= (float k);

		Vec3 operator * (const Vec3 & vec);

		Mat3 & operator = (const Mat3 & mat);

		//data members
		float m[3][3];
	};

	struct Rect
	{
		float x, y, width, height;
		Rect();
		Rect(float x, float y, float width, float height);		
	};
}

