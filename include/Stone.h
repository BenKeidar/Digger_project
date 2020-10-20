#pragma once
#include "StaticObject.h"

class Stone : public StaticObject
{
public:
	Stone(sf::Vector2i location, char icon);//constructor
	void draw(sf::RenderWindow& win, float clock_sample);//draw func
};

