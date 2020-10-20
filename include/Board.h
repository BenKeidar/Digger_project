#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "StaticObject.h"
#include <Vector>
#include <string>
#include <fstream> 
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <time.h>
#include <cmath>
#include <memory>

using std::vector;
using std::ifstream;
using std::string;
using std::make_unique;

struct keep_info
{
	char icon;
	sf::Vector2i location;
};

class Board
{

public:
	Board(int level);

	void draw(sf::RenderWindow& win, float clock_sampleB);
	void diamond_eaten();
	void set_object_null(sf::Vector2f place);
    void set_gift(int x, int y, char icon);
    void set_time(int elapsed);
	void stone_eaten(); 
    StaticObject* get_object(sf::Vector2f place);
	sf::Vector2i get_dig_location();
	char get_dig_icon();
	struct keep_info get_monster(int monster);
	int get_monster_sum();
	int get_width();
	int get_length();
	int get_diamond();
	int get_stones();
	int get_time();
	
private:

	int m_time; 
	int m_diamond; //number of diamonds;
	int m_stone;
	int m_level; //number of level.
	int m_width;
	int m_length;
	int m_monster_sum; //the sum of the monster.

	vector <string> m_file_vector; //vector of string.
	vector <vector <std::unique_ptr<StaticObject>>> m_board; //static objects vector.
	vector <struct keep_info > monster; //monster location.

    struct keep_info digger; //digger location.
	void copy_to_file_vector(ifstream& file);
	void define_m_board(vector <string> m_file_vector);
	void make_m_board();
};

