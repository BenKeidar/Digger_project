#pragma once
#include "StaticObject.h"

class Wall : public StaticObject
{

public:
	Wall(sf::Vector2i location, char icon);//constructor
	void draw(sf::RenderWindow& win, float clock_sample);//draw func
};

