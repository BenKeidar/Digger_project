#include "Wall.h"


//will get the location and icon and will create a wall.
Wall::Wall(sf::Vector2i location, char icon)
{
	sf::Texture* texture = Singleton::show().get_pic(3);
	m_pic.setTexture(*texture);
	m_pic.setOrigin(TO_CENTER, TO_CENTER);

	m_pic.setScale(1.5,1.5);

	m_icon = icon;
	m_location.x = (float)location.x * 45 + TO_CENTER+7.5;
	m_location.y = (float)location.y * 45 + TO_CENTER+7.5;

}

//the draw funtion for wall.
void Wall::draw(sf::RenderWindow& win, float clock_sample)
{
	m_pic.setTextureRect(sf::IntRect(0, 0, 30, 30));
	m_pic.setPosition(m_location.x + TO_CENTER+7.5, m_location.y + TO_CENTER+7.5);
	win.draw(m_pic);
}
