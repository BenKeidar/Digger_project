#pragma once
#include "StaticObject.h"

class Diamond : public StaticObject
{
public:
	Diamond(sf::Vector2i location, char icon); //constructor
	void draw(sf::RenderWindow& win, float clock_sample);
};

