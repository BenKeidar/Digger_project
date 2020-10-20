#include "Diamond.h"


//will get the location and icon and will create a diamond.
Diamond::Diamond(sf::Vector2i location, char icon)
{
	sf::Texture* texture;
	//sf::Texture* points, stone, gift;

	if (icon == 'P' || icon == 'S' || icon == 'C') //check if special diamond and put the right pic.
	{
		switch (icon)
		{
		case 'P':
			texture = Singleton::show().get_pic(7);
			break;
		case 'S':
			texture = Singleton::show().get_pic(8);
			break;
		case 'C':
			texture = Singleton::show().get_pic(9);
			break;
		}
	}
	else //if regular diamond.
		texture = Singleton::show().get_pic(2);

	m_pic.setTexture(*texture);
	m_pic.setOrigin(TO_CENTER, TO_CENTER);

	m_pic.setScale(1.5, 1.5);

	m_icon = icon; //set icon.
	m_location.x = (float)location.x * 45 + TO_CENTER+7.5; //update location.
	m_location.y = (float)location.y * 45 + TO_CENTER+7.5;
}

//the draw function for diamond.
void Diamond::draw(sf::RenderWindow& win, float clock_sample)
{
	m_pic.setTextureRect(sf::IntRect(0, 0, 30, 30));
	m_pic.setPosition(m_location.x + TO_CENTER + 7.5, m_location.y + TO_CENTER + 7.5);

	//if (m_icon != 'P' && m_icon != 'S' && m_icon != 'C') //cancel gifts.
		
	    win.draw(m_pic);
}
