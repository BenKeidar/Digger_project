#include "Monster.h"


//will get the location and icon and will create a monster.
Monster::Monster(sf::Vector2i location, char icon)
{
	m_location.x = (float)location.x * 45 + TO_CENTER+7.5;
	m_location.y = (float)location.y * 45 + TO_CENTER+7.5;

	sf::Texture* texture = Singleton::show().get_pic(1); // set monsters picture.
	m_pic.setTexture(*texture);
	m_pic.setOrigin(TO_CENTER, TO_CENTER);

	m_pic.setScale(1.5, 1.5);

	m_icon = icon; //set icon.
	define_color(); //define the color.+
	m_speed = 150; //default speed.
	from_y = 0;
	from_x = 0;
	change_pic = 0;
	m_direction = stand_t; //default direction.
	m_time_counter = 0;
}

// draw function.
void Monster::draw(sf::RenderWindow& win, float clock_sample)
{
	float color{};
	change_pic += clock_sample * m_speed;
	if (m_direction != stand_t)
		from_y = (float)m_direction * SHAPE;

	if (from_x == 0 && change_pic >= 15.f)
	{
		from_x = 1;
		change_pic = 0;
	}

	else if (from_x == 1 && change_pic >= 15.f)
	{
		from_x = 0;
		change_pic = 0;
	}

	if (m_color == sf::Color::Black)
		color = 0;
	else if ((m_color == sf::Color::Red))
		color = 60;
	else if ((m_color == sf::Color::Blue))
		color = 120;

	m_pic.setTextureRect(sf::IntRect((int)color + (int)from_x * SHAPE, from_y, 30, 30));

	m_pic.setPosition(m_location.x + TO_CENTER + 7.5, m_location.y + TO_CENTER + 7.5);
	win.draw(m_pic);

}


//movement function.
//two different ways to move (smart , regular) .
//the smart use manhatten formula.
//the regular will randomize a direction.
void Monster::move(sf::Vector2f center, float clock_sample, sf::Vector2f dig)
{
	float distance = clock_sample * m_speed;

	int current = (int)m_direction;
	int num = current;
	directions_t dirc = stand_t;

	if (m_icon != '%') //regular monster.
	{
		while (current == num)
		{
			num = rand() % 4;
			switch (num)
			{
			case 0:
				dirc = up_t;
				break;
			case 1:
				dirc = down_t;
				break;
			case 2:
				dirc = left_t;
				break;
			case 3:
				dirc = right_t;
			}
		}
		if (check_before_move(center) && m_time_counter >= 1.f)
		{
			m_direction = dirc;
			m_time_counter = 0;
		}
	}

	else // smart monster. (% = smart)
	{
		
		num = rand() % 30;
		if (num % 2 == 0)
		{
			if (dig.x > m_location.x)
				dirc = right_t;
			if (dig.x < m_location.x)
				dirc = left_t;
			if (dig.x == m_location.x)
			{
				if (dig.y > m_location.y)
					dirc = down_t;
				if (dig.y < m_location.y)
					dirc = up_t;
			}
		}
		else
		{
			if (dig.y > m_location.y)
				dirc = down_t;
			if (dig.y < m_location.y)
				dirc = up_t;
			if (dig.y == m_location.y)
			{
				if (dig.x > m_location.x)
					dirc = right_t;
				if (dig.x < m_location.x)
					dirc = left_t;
			}
		}

		if (check_before_move(center))
		{
			m_direction = dirc;
			m_time_counter = 0;
		}

	}

	if (m_direction == up_t)
		m_location.y = m_location.y - distance;
	if (m_direction == down_t)
		m_location.y = m_location.y + distance;
	if (m_direction == right_t)
		m_location.x = m_location.x + distance;
	if (m_direction == left_t)
		m_location.x = m_location.x - distance;
}

// update the move time counter.
void Monster::update_time_counter(float add)
{
	m_time_counter += add;
}

// return the location.
sf::Vector2f Monster::get_location()
{
	return m_location;
}

// get vector2f for location and update the location.
void Monster::set_location(sf::Vector2f location)
{
	m_location = location;
}


// set the monster speed for new speed.
/*void Monster::set_speed(float new_speed)
{
	m_speed += new_speed;
}*/

// set the monster direction.
void Monster::set_direction(directions_t dirc)
{
	m_direction = dirc;
}

// return the monster direction.
directions_t Monster::get_direction()
{
	return m_direction;
}

// define the color for the monster by her icon.
void Monster::define_color()
{
	int num = rand()%10;
	if (m_icon == '%')
		m_color = sf::Color::Black;
	else
		{
            if (num >= 3)
	     	{
			     m_color = sf::Color::Blue;
			}
			else
				 m_color = sf::Color::Red;
		}
		
}


