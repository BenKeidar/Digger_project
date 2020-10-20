#include "Digger.h"


// build the digger object by location and his icon.
Digger::Digger(sf::Vector2i location, char icon)
{
	m_location.x = (float)location.x * 45 + TO_CENTER+7.5; //update location.
	m_location.y = (float)location.y * 45 + TO_CENTER+7.5;

	sf::Texture* texture = Singleton::show().get_pic(0); //update picture.
	m_pic.setTexture(*texture);
	m_pic.setOrigin(TO_CENTER, TO_CENTER);
	m_icon = icon;

	m_pic.setScale(1.5,1.5);

	m_speed = 200;
	from_x = 0;
	from_y = 0;
	m_direction = stand_t; //define his direction.
	change_pic = 0;  
}


// draw the digger on the board.
void Digger::draw(sf::RenderWindow& win, float clock_sample)
{
	change_pic += clock_sample * m_speed;
	if (m_direction != stand_t)
		from_y = (float)m_direction * SHAPE;
	if (from_x == 0 && change_pic >= 15.f) //change between pictures.
	{
		from_x = 1;
		change_pic = 0;
	}

	else if (from_x == 1 && change_pic >= 15.f)
	{
		from_x = 0;
		change_pic = 0;
	}

	m_pic.setTextureRect(sf::IntRect(120 + (int)from_x * SHAPE, from_y, 30, 30));
	m_pic.setPosition(m_location.x + TO_CENTER + 7.5, m_location.y + TO_CENTER + 7.5);
	win.draw(m_pic);
}


// move the digger.
void Digger::move(float distance, directions_t dirc, sf::Vector2f center)
{
	if (check_before_move(center))
		m_direction = dirc;
	if (m_direction == up_t)
		m_location.y = m_location.y - distance;
	if (m_direction == down_t)
		m_location.y = m_location.y + distance;
	if (m_direction == right_t)
		m_location.x = m_location.x + distance;
	if (m_direction == left_t)
		m_location.x = m_location.x - distance;

}

// return the digger location.
sf::Vector2f Digger::get_location()
{
	return m_location;
}

// update the location to new place.
void Digger::set_location(sf::Vector2f newp)
{
	m_location = newp;
}

// return the direction.
directions_t Digger::get_direction()
{
	return m_direction;
}

// update the speed to new speed.
/*void Digger::set_speed(float new_speed)
{
	m_speed += new_speed;
}*/




