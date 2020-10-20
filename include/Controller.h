 #pragma once
#include "Monster.h"
#include "Digger.h"
#include "Diamond.h"
#include "Board.h"
#include "Wall.h"
#include "Object.h"
#include "Singleton.h"
#include <Vector>
#include <time.h>
#include "windows.h"
#include "Toolbar.h"
#include "Menu.h"


class Controller
{
public:
	Controller(); 
	void run(); //the game function.

private:
	vector <struct keep_info> m_mons_info;
	vector <Monster> m_monster; //the monster vector.
	std::unique_ptr <Digger> digger; //the digger object.

	sf::Music m_background; //music file
	sf::Music m_game_over;
	sf::Music m_eating;
	sf::Music m_lost;
	sf::Music m_level_end;
	sf::Music m_special_diamond;
	sf::Music m_gift;
	sf::Music m_s_stone;
	sf::Music m_game_end;
	sf::Music InGameMusic;

	sf::Vector2f gifts_loc;
	sf::Sprite background;
	sf::Clock game_clock;

	int m_monster_sum;
	int m_lives;
	int m_clock ;
	int m_elapsed;
	int m_prev_lives;
	int m_diamond_sum;
	int m_points;
	int m_prev_points;
	int m_clock_bonuses;
	bool m_sound_switch;
	bool m_time_bonus;	
    bool m_if_stones = false;
	float m_gift_clock;
	float m_gifts_counter;

	//---------General Functions---------
	sf::Vector2f digger_get_center(int width, int length);
	sf::Vector2f digger_get_center(Monster monster, int width, int length);
    float distance(float clock_sample);
	void monster_vec_build(Board& level);
	void monster_draw(sf::RenderWindow& win, float clock_sample);
	void draw(sf::RenderWindow& win, Board& level, float clock_sample, Toolbar& menu);
	void move(int width, int length, directions_t side, float monster_t_counter, Board& level, float distance,
		 bool& good, bool& bad, Toolbar& menu, sf::RenderWindow& window);
	void create_monster();
	void check_monster_bounds(Monster& monster, int width, int length);
	void check_digger_bounds(int width, int length);
	void digger_colide_check(sf::Vector2f prev, Board& level, int width, int length, bool& if_points, 
		 bool& if_stone, Toolbar& menu, sf::RenderWindow& window);
	void monster_colide_check(Monster& monster, sf::Vector2f prev, Board& level, int width, int length);
	void recreate_monster();
	void start_over(Board& level);
	//void balance_speed_by_level(int level_size); //OPTIONAL
	void gift_status(bool& if_points, bool& if_stone, bool& if_clock, float clock_sample, Board& level, Toolbar& menu);
	void game_over(sf::RenderWindow& window);
	void set_next_level(sf::RenderWindow& window);
	void sound_switch();
	void gifts(bool& if_points, bool& if_stone, bool& if_clock, float clock_sample, Board& level);
	void set_game_end(sf::RenderWindow& window);
	void show_bonus_points(sf::RenderWindow& window);
	void show_bonus_clock(sf::RenderWindow& window);
	void show_bonus_stone(sf::RenderWindow& window);
};

