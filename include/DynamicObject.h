#pragma once
#include "Object.h"

enum directions_t
{
	right_t,
	down_t,
	left_t,
	up_t,
	stand_t,
};


class DynamicObject : public Object
{

public:
	DynamicObject();
   ~DynamicObject();

	//float get_speed(); //OPTIONAL

protected:
	float m_speed;
	float change_pic;
	float from_x;
	float from_y;
	bool check_before_move(sf::Vector2f center);

	directions_t m_direction;
	
};

