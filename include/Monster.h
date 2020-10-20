#pragma once
#include "DynamicObject.h"

class Monster : public DynamicObject
{

public:
	Monster(sf::Vector2i location, char icon);	

	void draw(sf::RenderWindow& window, float clock_sample);//draw func
	void move(sf::Vector2f center, float clock_sample, sf::Vector2f dig);//movement func
	void update_time_counter(float add);//func to update time counter
	void set_location(sf::Vector2f location);
	//void set_speed(float new_speed);
	void set_direction(directions_t dirc);

	directions_t get_direction();
    sf::Vector2f get_location();

private:
	void define_color();
	float m_time_counter;
};
