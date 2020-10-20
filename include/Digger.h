#pragma once
#include "DynamicObject.h"


class Digger : public DynamicObject
{

public:
	Digger(sf::Vector2i location, char icon);//constructor

	//void set_speed(float new_speed);
	void set_location(sf::Vector2f newp);
	void draw(sf::RenderWindow& win, float clock_sample);
	void move(float distance, directions_t dirc, sf::Vector2f center);//movement function

	sf::Vector2f get_location();
	directions_t get_direction();
	
private:
	
};

