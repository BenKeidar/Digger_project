#pragma once
#include <SFML\Graphics.hpp>
#include "Singleton.h"

const float HEIGHT = 30;
const float WIDTH = 30;
const float TO_CENTER = 15;
const int SHAPE = 30;

class Object
{
public:
	Object();//constructor
	virtual ~Object();//distructor

	virtual void draw(sf::RenderWindow& win, float clock_sample) = 0;//virtual draw func

	//assignment fuctions:
	char get_icon();

protected:
	char m_icon;
	sf::Sprite m_pic;
	sf::Color m_color;
	sf::Vector2f m_location;
};

