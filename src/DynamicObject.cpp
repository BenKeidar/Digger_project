#include "DynamicObject.h"



DynamicObject::DynamicObject():change_pic(), from_x(0), from_y(0), m_direction(),m_speed(0)
{
}


DynamicObject::~DynamicObject()
{
}
//speed balance asist
/*float DynamicObject::get_speed()
{
	return m_speed;
}*/

bool DynamicObject::check_before_move(sf::Vector2f center)
{

	if ((abs(m_location.x - center.x) <= 3.f) && (abs(m_location.y - center.y) <= 3.f))
		return true;

	return false;
}
