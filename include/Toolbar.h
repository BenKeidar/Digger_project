#pragma once
#include <SFML\Graphics.hpp>

class Toolbar
{
public:
	Toolbar(int level, int lives, int points, int clock, int stone);
	Toolbar();
    ~Toolbar();
    void draw(sf::RenderWindow& window);//draw
	void setToolBar();
	void setToolGame();
	void set_lives(int new_lives);//func to update lives
	void set_points(int new_points);//func to update score
	void set_stones(int new_stones);//func to update number of stones allowed
	void set_clock(int elapsed);//func to update clock

	//---------Assigment Functions--------
	int get_stones();
	int get_clock();
	//--Others--
	int m_clock;
private:
	sf::Font m_font;
	sf::Font t_font;
	sf::Text m_level_text;
	sf::Text m_points_text;
	sf::Text m_lives_text;
	sf::Text m_num_level;
	sf::Text m_num_points;
	sf::Text m_num_lives;
	sf::Text m_clock_text;
	sf::Text m_num_clock;
	sf::Text m_num_stones;
	sf::Text m_stone_text;

	int m_level = 1; 
	int m_lives = 3;
	int m_points;
	int m_stone;
};

