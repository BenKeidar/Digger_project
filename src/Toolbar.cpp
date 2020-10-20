#include "Toolbar.h"
#include <iostream>
#include <string>

//the constructor is getting parameters for start.
Toolbar::Toolbar(int level, int lives, int points, int clock, int stone)
{
	m_level = level; //update his parameters.
	m_lives = lives;
	m_points = points;
	m_clock = clock;
	m_stone = stone;

	m_font.loadFromFile("FONT.ttf"); //update font
	t_font.loadFromFile("FONT.ttf");
	setToolBar(); //set the toolbar.
	setToolGame();//set the toolgame.
}

Toolbar::Toolbar()
{

}

//this function will create a string of the game parameters.
//they will not going to change during the game.
void Toolbar::setToolBar()
{
	m_level_text.setFont(m_font);
	m_level_text.setCharacterSize(40);
	m_level_text.setFillColor(sf::Color::White);
	m_level_text.setStyle(sf::Text::Bold);
	m_level_text.setPosition(1040, 10);
	m_level_text.setString(" LEVEL");

	m_lives_text.setFont(m_font);
	m_lives_text.setCharacterSize(40);
	m_lives_text.setFillColor(sf::Color::White);
	m_lives_text.setStyle(sf::Text::Bold);
	m_lives_text.setPosition(1040, 130);
	m_lives_text.setString(" LIVES");

	m_points_text.setFont(m_font);
	m_points_text.setCharacterSize(40);
	m_points_text.setFillColor(sf::Color::White);
	m_points_text.setStyle(sf::Text::Bold);
	m_points_text.setPosition(1040, 250);
	m_points_text.setString("SCORE");

	m_stone_text.setFont(m_font);
	m_stone_text.setCharacterSize(27);
	m_stone_text.setFillColor(sf::Color::White);
	m_stone_text.setStyle(sf::Text::Bold);
	m_stone_text.setPosition(1040, 370);
	m_stone_text.setString("STONES\nALLOWED");

	m_clock_text.setFont(m_font);
	m_clock_text.setCharacterSize(35);
	m_clock_text.setFillColor(sf::Color::White);
	m_clock_text.setStyle(sf::Text::Bold);
	m_clock_text.setPosition(1040, 540);
	m_clock_text.setString("CLOCK");
}

//this function will create a string of the game stats.
//they will change during the game.
void Toolbar::setToolGame()
{	
	m_num_level.setString(std::to_string(m_level));
	m_num_level.setFont(t_font);
	m_num_level.setStyle(sf::Text::Bold);
	m_num_level.setCharacterSize(30);
	m_num_level.setPosition(1095, 60);
	m_num_level.setFillColor(sf::Color::White);


	int level_live_limit = 1;

	if (m_lives == level_live_limit)
		m_num_lives.setFillColor(sf::Color::Red);

	else
		m_num_clock.setFillColor(sf::Color::White);

	m_num_lives.setString(std::to_string(m_lives));
	m_num_lives.setFont(t_font);
	m_num_lives.setStyle(sf::Text::Bold);
	m_num_lives.setCharacterSize(30);
	m_num_lives.setPosition(1095, 180);


	m_num_points.setString(std::to_string(m_points));
	m_num_points.setFont(t_font);
	m_num_points.setStyle(sf::Text::Bold);
	m_num_points.setCharacterSize(30);
	m_num_points.setPosition(1095, 300);
	m_num_points.setFillColor(sf::Color::White);


	int level_Stone_limit = 2;

	if (m_stone <= level_Stone_limit)
		m_num_stones.setFillColor(sf::Color::Red);

	else
		m_num_stones.setFillColor(sf::Color::White);

	m_num_stones.setString(std::to_string(m_stone));
	m_num_stones.setFont(t_font);
	m_num_stones.setStyle(sf::Text::Bold);
	m_num_stones.setCharacterSize(30);
	m_num_stones.setPosition(1095, 470);

	int level_time_limit = 25;

	if (m_clock <= level_time_limit)
	{
		if (m_clock % 2 == 0)
			m_num_clock.setFillColor(sf::Color::White);

		else
			m_num_clock.setFillColor(sf::Color::Red);
	}
	else
		m_num_clock.setFillColor(sf::Color::White);

	m_num_clock.setString(std::to_string(m_clock));
    m_num_clock.setFont(t_font);
	m_num_clock.setStyle(sf::Text::Bold);
	m_num_clock.setCharacterSize(30);
	m_num_clock.setPosition(1095, 590);

}

// get the new lives and update it.
void Toolbar::set_lives(int new_lives)
{

	m_lives = new_lives;
	setToolBar();
	setToolGame();
}

// get the new points and update it.
void Toolbar::set_points(int new_points)
{

	m_points = new_points;
	setToolBar();
	setToolGame();
}

void Toolbar::set_stones(int new_stones)
{
	m_stone = m_stone + new_stones;
	setToolGame();
}

int Toolbar::get_stones()
{
	return m_stone;
}

// will draw the game time object.
void Toolbar::draw(sf::RenderWindow& window)
{

	window.draw(m_level_text);
	window.draw(m_points_text);
	window.draw(m_lives_text);
	window.draw(m_num_level);
	window.draw(m_num_points);
	window.draw(m_num_lives);
	window.draw(m_num_stones);
	window.draw(m_stone_text);
	window.draw(m_clock_text);
	window.draw(m_num_clock);
}


Toolbar::~Toolbar()
{
}

void Toolbar::set_clock(int elapsed)
{
	m_clock = elapsed;
	setToolGame();
}

int Toolbar::get_clock()
{
	return m_clock;
}