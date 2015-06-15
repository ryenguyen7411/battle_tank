#include "stdafx.h"

#include <string>

#include "support.h"

Direction g_isCollide(Rect st, Rect nd, Vec2 stVeloc, Vec2 ndVeloc)
{
	if((st.x + st.width < nd.x && st.x + st.width - stVeloc.x < nd.x - ndVeloc.x) ||
		(st.x > nd.x + nd.width && st.x - stVeloc.x > nd.x + nd.width - ndVeloc.x) ||
		(st.y + st.height < nd.y && st.y + st.height - stVeloc.y < nd.y - ndVeloc.y) ||
		(st.y > nd.y + nd.height && st.y - stVeloc.y > nd.y + nd.height - ndVeloc.y))
		return Direction::DIR_NONE;
	else
	{
		Direction collideDirection = Direction::DIR_UNKNOWN;

		if(st.y + st.height - stVeloc.y <= nd.y - ndVeloc.y)
			collideDirection = Direction::DIR_UP;
		else if(st.y - stVeloc.y > nd.y + nd.height - ndVeloc.y)
			collideDirection = Direction::DIR_DOWN;
		else if(st.x + st.width - stVeloc.x < nd.x - ndVeloc.x)
				collideDirection = Direction::DIR_LEFT;
		else if(st.x - stVeloc.x > nd.x + nd.width - ndVeloc.x)
				collideDirection = Direction::DIR_RIGHT;

		return collideDirection;
	}
}

///////////////////////////////////////////////////////
//Coder: Rye
//Purpose: Reimplement getNumber function
int GetNumber(char* s)
{
	int result = 0;
	while(*s < '0' || *s > '9') s++;

	while(*s >= '0' && *s <= '9')
	{
		result *= 10;
		result += *s - '0';
		s++;
	}

	return result;
}


////////

bool		g_CheckAABB(Rect box1, Rect box2)
{
	if (box1.x + box1.width < box2.x || box1.x > box2.x + box2.width || box1.y + box1.height < box2.y || box1.y > box2.y + box2.height)
		return false;

	return true;
}

bool isInRect(Rect _rect, Vec2 _position)
{
	return !(_position.x < _rect.x || _position.x > _rect.x + _rect.width
		|| _position.y < _rect.y || _position.y > _rect.y + _rect.height);
}

bool isInRect(Rect _rect, Vec3 _position)
{
	return !(_position.x < _rect.x || _position.x > _rect.x + _rect.width
		|| _position.y < _rect.y || _position.y > _rect.y + _rect.height);
}

int convertToInt(char* __sNumber)
{
	int _returnValue = 0;

	while(*__sNumber <= '9' && *__sNumber >= '0')
	{
		_returnValue *= 10;
		_returnValue += *__sNumber - '0';

		__sNumber++;
	}

	return _returnValue;
}

char* convertToString(int __number)
{
	if(__number == 0)
		return "0";

	char _sNumber[1024];

	int i;
	for(i = 0; __number != 0; i++)
	{
		_sNumber[i] = __number % 10 + '0';
		__number /= 10;
	}
	_sNumber[i] = '\0';

	for(i = 0; i < strlen(_sNumber) / 2; i++)
	{
		char _temp = _sNumber[i];
		_sNumber[i] = _sNumber[strlen(_sNumber) - 1 - i];
		_sNumber[strlen(_sNumber) - 1 - i] = _temp;
	}

	return _sNumber;
}
