#include "Controller.h"
#include <Stone.h>

//constructor initialized private members
Controller::Controller() : m_monster_sum(0), m_lives(3), m_gift_clock(0)
                            , m_diamond_sum(0), m_prev_lives(), m_gifts_counter(), m_prev_points()
							,m_elapsed(), m_clock(0), m_time_bonus(false), m_clock_bonuses(0)
{

	m_background.openFromFile("music.ogg");
	m_eating.openFromFile("eating.ogg");
	m_eating.setVolume(100);
	m_game_over.openFromFile("end.ogg");
	m_lost.openFromFile("lost.ogg");
	m_level_end.openFromFile("level_end.ogg");
	m_special_diamond.openFromFile("diamond.ogg");
	m_gift.openFromFile("gift.ogg");
	m_s_stone.openFromFile("stone.ogg");
	m_s_stone.setVolume(100);
	InGameMusic.openFromFile("InGame.ogg");
	m_game_end.openFromFile("game_won1.ogg");


	m_points = 0;
	m_sound_switch = true;
	gifts_loc = { -1,-1 };
}

//the main funcion , it will manage all the game play 
//will makes the moves (function move) , check for
//colides (by colide functions) , stones, clock , gifts , music and more.
void Controller::run()
{
	srand(unsigned(time(NULL))); //random for monsters move.

	directions_t side = stand_t;
	sf::Texture* back;
	sf::Clock game_clock;
	sf::Clock clock;
	sf::Event event;

	Toolbar setTime;
	bool skip = true; //if 'L' key is pressed it will skip a level.
	int last_level = 5;
	for (int level_num = 1; level_num <= last_level; level_num++)
	{
		if (m_if_stones && level_num != last_level)
			level_num--;

		sf::RenderWindow window(sf::VideoMode(1200, 1000, 32), "DIGGER", sf::Style::Titlebar | sf::Style::Close);
		back = Singleton::show().get_pic(14);
		background.setTexture(*back);
		window.setPosition(sf::Vector2i(220, 0));

		Board level(level_num); //create level.
		m_diamond_sum = level.get_diamond();
		side = stand_t;
		m_monster_sum = level.get_monster_sum(); //number of monsters.
		monster_vec_build(level); //create monsters
		create_monster();	//create monsters

		float clock_sample = 0;
		bool if_stone = false; //if stone gift exist on the board
		bool if_points = false;//if points gift exist on the board
		bool if_clock = false;//if clock gift  exist on the board

		m_gifts_counter = 0; //count the time until we will create existing gifts.
		m_gift_clock = 0;	//count the time until the gifts will disappear.
		gifts_loc = { -1,-1 }; //update the gift to "null".

		digger = make_unique <Digger>(level.get_dig_location(), level.get_dig_icon()); //create digger.

		if (m_if_stones)
		{
			m_lives = m_prev_lives;
			m_if_stones = false;
		}

		Toolbar menu(level_num, m_lives, m_points, level.get_time(), level.get_stones()); //create the menu bar.
		//balance_speed_by_level((level.get_length()+level.get_width())/2); //set the characters speed by level size

		InGameMusic.setLoop(true); //music
		InGameMusic.play();
		m_time_bonus = false;
		m_prev_points = m_points;//save prev level points
		while (window.isOpen()) //everything in the game is going to run in this loop.
		{
			
			m_elapsed = game_clock.getElapsedTime().asSeconds(); //elapsed will hold the elapsed time in seconds
			m_elapsed = (level.get_time() - m_elapsed); //set the time from end 

			if(m_time_bonus)
				m_elapsed += 10 * m_clock_bonuses; 

			menu.set_clock(m_elapsed);
			
			while (window.pollEvent(event))
			{

				if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					game_over(window);
					return;
				}
				if (event.type == sf::Event::KeyPressed) //check for key press.
				{
					if (event.key.code == sf::Keyboard::Up)
						side = up_t;
					if (event.key.code == sf::Keyboard::Down)
						side = down_t;
					if (event.key.code == sf::Keyboard::Left)
						side = left_t;
					if (event.key.code == sf::Keyboard::Right)
						side = right_t;
					if (event.key.code == sf::Keyboard::Space)
						side = stand_t;
					if (event.key.code == sf::Keyboard::S) //will turn on/off the sound.
						sound_switch();
					if (event.key.code == sf::Keyboard::L) //will skip a level.
						skip = false; //update the skip "button" to null.
				}
			}
			if (skip)
			{
				clock_sample = clock.getElapsedTime().asSeconds();	//update the counter.
				move(level.get_width(), level.get_length(), side, clock_sample, level,
					 distance(clock_sample) , if_points, if_stone, menu, window);	//move action for the characters.
				draw(window, level, clock_sample, menu);	//draw the window.
				gifts(if_points, if_stone, if_clock, clock_sample, level); //check for gifts.
				clock.restart(); //restart the clock.
				window.display(); //display the window.
				gift_status(if_points, if_stone, if_clock, clock_sample, level, menu); //check the gifts status.
			}
			if (m_lives == 0) //if live is zero.
			{
				game_over(window); //will start a game over function.
				return;
			}
			if (level.get_diamond() == 0 || skip == false)// end the level.
			{
				if (level_num < last_level)
				{
					skip = true; //if 'L' key is pressed it will skip a level.
					set_next_level(window); //get ready for the next level.
					clock.restart();
					game_clock.restart();
				}
				else
					set_game_end(window);

				break;
			}
			if (menu.get_stones() == 0)// end the level.
			{
				if (level_num == last_level)
				{
					level_num--;
				}
				m_points = m_prev_points;
				game_clock.restart();
				m_if_stones = true;
				m_prev_lives = m_lives;
				break;
			}
			if (menu.get_clock() == 0)// end the level.
			{
				if (level_num == last_level)
				{
					level_num--;
				}
				m_points = m_prev_points;
				m_lives--;
				menu.set_lives(m_lives);
				m_if_stones = true;
				m_prev_lives = m_lives;
				game_clock.restart();
				break;
			}

		}	

	}
}


//will set the characters in the original places.
void Controller::start_over(Board& level)
{
	sf::Vector2f dig_loc; //to update the digger locaion
	dig_loc.x = (float)level.get_dig_location().x * (SHAPE+15) +22.5;
	dig_loc.y = (float)level.get_dig_location().y * (SHAPE+15) +22.5;

	digger.get()->set_location(dig_loc); //update in digger.
	recreate_monster(); //will recreate the monsters.
}


//will set the level speed by the average of height and width of level 
/*void Controller::balance_speed_by_level(int level_size)
{
	int balance = 7;
	digger.get()->set_speed(level_size*balance); //speed correction
	for (int i = 0; i < m_monster_sum; i++)
	{
		m_monster[i].set_speed(level_size*balance);
	}
}*/


//check if its time to erase the items (if exist - by the boolian)
//then the funcion erase the item 
void Controller::gift_status(bool& if_points, bool& if_stone, bool& if_clock, float clock_sample, Board& level, Toolbar& menu)
{
	m_gift_clock += clock_sample; //increase the m_diamond_clock by the clock sample.

	if (if_points && m_gift_clock >= 4.f) //if points on the board;
	{
		if_points = false; //turn it to false.
		m_gift_clock = 0;

		level.set_object_null(gifts_loc); //erase the gift.
		gifts_loc = { -1,-1 }; //restart the location of the gift
	}

	if (if_stone && m_gift_clock >= 4.f) //if stone on the board(same like above)
	{
		if_stone = false;
		m_gift_clock = 0;

		level.set_object_null(gifts_loc);
		gifts_loc = { -1,-1 };
	}

	if (if_clock && m_gift_clock >= 4.f) //if clock on the board(same like above)
	{
		if_clock = false;
		m_gift_clock = 0;
		level.set_object_null(gifts_loc);
		gifts_loc = { -1,-1 };
	}
}


// is going to end the game, and will show a sprite of game over picture
// and sound.
void Controller::game_over(sf::RenderWindow& window)
{
	sf::Texture* end;
	sf::Sprite f_end;
	sf::Vector2f position;

	position.x = 0;
	position.y = 0;
	end = (Singleton::show().get_pic(10)); //get the pic from singelton.
	f_end.setTexture(*end); //update the sprite.
	f_end.setTextureRect(sf::IntRect(0, 0, 1200, 1000)); //update the size.

	InGameMusic.stop();
	window.clear(); //clear the window.
	window.draw(f_end); //draw the game over picture.
	window.display(); //display it for the user
	m_game_over.play(); //play the game over sound.
	Sleep(4000);
	window.close(); //close the game window.
}


// prepare the members of controller for the next level and will play winner music
// and will display a trophy picture on the screen.
void Controller::set_next_level(sf::RenderWindow& window)
{

	InGameMusic.stop();
	m_level_end.play();

	sf::Texture* trophy = Singleton::show().get_pic(11);
	sf::Sprite tropy;

	tropy.setTexture(*trophy);
	tropy.setTextureRect(sf::IntRect(0, 0, 1200, 1000));
	window.draw(tropy); //show the trophy.
	window.display();
	Sleep(3000);
	m_level_end.stop();
	window.close();
	for (int i = 0; i < m_monster_sum; i++) //erase the monsters.
	{
		m_monster.pop_back();
		m_mons_info.pop_back();
	}
	m_points += 20;
}


// will turn off / on the sound in the game.
void Controller::sound_switch()
{
	if (m_sound_switch) //turn off.
	{
		InGameMusic.setVolume(0);
		m_game_over.setVolume(0);
		m_eating.setVolume(0);
		m_lost.setVolume(0);
		m_level_end.setVolume(0);
		m_special_diamond.setVolume(0);
		m_gift.setVolume(0);
		m_s_stone.setVolume(0);
		m_game_end.setVolume(0);
		m_sound_switch = false;
	}
	else //turn on.
	{
		InGameMusic.setVolume(100);
		m_game_over.setVolume(100);
		m_eating.setVolume(100);
		m_lost.setVolume(100);
		m_level_end.setVolume(100);
		m_special_diamond.setVolume(100);
		m_gift.setVolume(100);
		m_s_stone.setVolume(100);
		m_game_end.setVolume(100);
		m_sound_switch = true;
	}
}


// will lottery a special gift (only one on the board per time).
void Controller::gifts(bool& if_points, bool& if_stone, bool& if_clock, float clock_sample, Board& level)
{
	int x;
	int y;
	char icon{};
	sf::Vector2f location = { 45,45 }; // set the location.
	m_gifts_counter += clock_sample; //update the special gift counter.

	//check if its time for new gift and if there is no other gift on the board.
	if (m_gifts_counter >= 5 && gifts_loc.x == -1 && gifts_loc.y == -1)
	{
		x = rand() % level.get_width(); //randomize for x  location
		y = rand() % level.get_length(); //randomize for y  location

		location.x = (float)x * (SHAPE + 15) + 22.5;
		location.y = (float)y * (SHAPE + 15) + 22.5;

		while (level.get_object(location) != nullptr) //search for a null place.
		{
			x = rand() % level.get_width(); //randomize for x  location
			y = rand() % level.get_length(); //randomize for y  location

			location.x = (float)x * (SHAPE + 15) + 22.5;
			location.y = (float)y * (SHAPE + 15) + 22.5;
		}

		if (x % 3 == 0) //randomize the type.
		{
			icon = 'P';
			if_points = true;
			m_gift_clock = 0;
		}
		else if (x % 3 == 1)
		{
			icon = 'S';
			if_stone = true;
			m_gift_clock = 0;
		}
		else if (x % 3 == 2)
		{
			icon = 'C';
			if_clock = true;
			m_gift_clock = 0;
		}

		level.set_gift(x, y, icon); //create the gift.
		m_gifts_counter = 0;
		gifts_loc = location; //update the special gift location.
	}
}

void Controller::set_game_end(sf::RenderWindow& window)
{
	InGameMusic.stop();
	m_game_end.setPlayingOffset(sf::seconds(0));
	m_game_end.play();

	sf::Texture* end = Singleton::show().get_pic(4);
	sf::Sprite end1;

	end1.setTexture(*end);
	end1.setTextureRect(sf::IntRect(0, 0, 1200, 900));
	window.draw(end1); //show the end picture.
	window.display();
	Sleep(10000);
	window.close();
}

void Controller::show_bonus_points(sf::RenderWindow& window)
{
	sf::Texture* b_p = Singleton::show().get_pic(17); //make a xp picture.
	sf::Sprite bonus_points;

	bonus_points.setTexture(*b_p);
	bonus_points.setTextureRect(sf::IntRect(0, 0, 1200, 1000));
	window.draw(bonus_points);
	window.display(); //display xp picture.
	window.clear();
	Sleep(400);
}

void Controller::show_bonus_clock(sf::RenderWindow& window)
{
	sf::Texture* b_c = Singleton::show().get_pic(18); //make a clock picture.
	sf::Sprite bonus_clock;

	bonus_clock.setTexture(*b_c);
	bonus_clock.setTextureRect(sf::IntRect(0, 0, 1200, 1000));
	window.draw(bonus_clock);
	window.display(); //display clock picture.
	window.clear();
	Sleep(400);
}

void Controller::show_bonus_stone(sf::RenderWindow& window)
{
	sf::Texture* b_s = Singleton::show().get_pic(16); //make a stone picture.
	sf::Sprite bonus_stone;

	bonus_stone.setTexture(*b_s);
	bonus_stone.setTextureRect(sf::IntRect(0, 0, 1200, 1000));
	window.draw(bonus_stone);
	window.display(); //display stone picture.
	window.clear();
	Sleep(400);
}


//build a vector of monster , (struct keep info).
void Controller::monster_vec_build(Board& level)
{
	for (int index = 0; index < m_monster_sum; index++)
	{
		struct keep_info mon;
		mon = level.get_monster(index);
		m_mons_info.push_back(mon);
	}
}


//draw the monsters.
void Controller::monster_draw(sf::RenderWindow& win, float clock_sample)
{
	for (int index = 0; index < m_monster_sum; index++)
		m_monster[index].draw(win, clock_sample);
}


//calculate the distance that digger should go.
float Controller::distance(float clock_sample)
{
	float distance = clock_sample * 150;// *digger.get()->get_speed();
	return distance;
}


//draw the board including digger , diamonds and monsters.
void Controller::draw(sf::RenderWindow& win, Board& level, float clock_sample, Toolbar& menu)
{
	win.clear();
	win.draw(background);
	level.draw(win, clock_sample);

	for (int monster = 0; monster < m_monster_sum; monster++)
		m_monster[monster].draw(win, clock_sample);

	digger.get()->draw(win, clock_sample);

	menu.draw(win);
}


//fix the digger place and return the fixed center.
sf::Vector2f Controller::digger_get_center(int width, int length)
{
	sf::Vector2f location;
	location = digger.get()->get_location();
	int i, y;

	i = (int)location.x / (SHAPE+15);
	y = (int)location.y / (SHAPE + 15);

	i = i * (SHAPE + 15) + 22.5;
	y = y * (SHAPE + 15) + 22.5;

	location.x = (float)i;
	location.y = (float)y;

	return location;
}


//fix the monster place and return the fixed center.
sf::Vector2f Controller::digger_get_center(Monster monster, int width, int length)
{
	sf::Vector2f location;
	location = monster.get_location();
	int i, y;

	i = (int)location.x / (SHAPE + 15);
	y = (int)location.y / (SHAPE + 15);

	i = i * (SHAPE + 15);
	y = y * (SHAPE + 15);

	location.x = (float)i + 22.5;
	location.y = (float)y + 22.5;

	return location;
}


//this function will do the move for the dynamic objects and check for colides.
void Controller::move(int width, int length, directions_t side, float clock_sample, Board& level, float distance,
	bool& if_points, bool& if_stone, Toolbar& menu, sf::RenderWindow& window) //the move action.
{
	sf::Vector2f dig_center; //for the digger center.
	sf::Vector2f dig_prev = digger.get()->get_location();	//the current location of object.
	sf::Vector2f monster_prev;
	dig_center = digger_get_center(width, length);	//gets the center of digger.
	digger->move(distance, side, dig_center);	//move the digger.
	check_digger_bounds(width, length);
	digger_colide_check(dig_prev, level, width, length, if_points, if_stone, menu, window);

	for (int monster = 0; monster < m_monster_sum; monster++) //run over the monster.
	{
		m_monster[monster].update_time_counter(clock_sample); //update the time counter of a monster.

		monster_prev = m_monster[monster].get_location(); //save the previus location of a monster.
		m_monster[monster].move(digger_get_center(m_monster[monster], width, length), clock_sample, digger.get()->get_location());	//move the monster.
		check_monster_bounds(m_monster[monster], width, length);	//check if the location is ok and update if not.
		monster_colide_check(m_monster[monster], monster_prev, level, width, length);
	}

}

//create the monster objects.
void Controller::create_monster()
{
	for (int i = 0; i < m_monster_sum; i++)
		m_monster.push_back(Monster(m_mons_info[i].location, m_mons_info[i].icon));
}

//check for every deamon if he is in the bounds. (teleport move).
void Controller::check_monster_bounds(Monster& monster, int width, int length)
{
	sf::Vector2f temp;

	float n_width = (float)width * (SHAPE + 15);
	float n_length = (float)length * (SHAPE + 15);
}

//check for digger if he is in the bounds. (teleport move).
void Controller::check_digger_bounds(int width, int length)
{
	sf::Vector2f temp;

	float n_width = (float)width * (SHAPE + 15);
	float n_length = (float)length * (SHAPE + 15);
}

//check the colides for digger , digger check the colides with the monsters.
void Controller::digger_colide_check(sf::Vector2f prev, Board& level, int width, int length, bool& if_points,
	bool& if_stone, Toolbar& menu, sf::RenderWindow& window)
{
	sf::Vector2f digg_fix = prev;
	StaticObject* obj;
	directions_t dirc_t = digger.get()->get_direction();

	if (dirc_t == up_t)
		digg_fix.y = digg_fix.y - 22.5;
	if (dirc_t == down_t)
		digg_fix.y = digg_fix.y + 22.5;
	if (dirc_t == left_t)
		digg_fix.x = digg_fix.x - 22.5;
	if (dirc_t == right_t)
		digg_fix.x = digg_fix.x + 22.5;

	sf::Vector2i temp;

	temp.x = (int)digg_fix.x / (SHAPE + 15);
	temp.y = (int)digg_fix.y / (SHAPE + 15);
	digg_fix.x = (float)temp.x * (SHAPE + 15) + 22.5;
	digg_fix.y = (float)temp.y * (SHAPE + 15) + 22.5;

	if (dirc_t != stand_t)
	{
		obj = level.get_object(digg_fix); //get static object.
		if (obj != nullptr)
		{
			if (typeid(*obj) == typeid(Wall)) //if the object is wall
			{
				digger.get()->set_location(prev);
			}

			else if (typeid(*obj) == typeid(Diamond)) //if the object is Diamond
			{
				switch (obj->get_icon()) //wich gift do we have.
				{
				case 'P':
					m_gift.setPlayingOffset(sf::seconds(0));//set music from start for next session
					m_gift.play();
					m_points += 5;
					menu.set_points(m_points);
					if_points = true;
					show_bonus_points(window);
					break;
				case 'S':
					m_gift.setPlayingOffset(sf::seconds(0));
					m_gift.play();
					int inc_stone;
					inc_stone = 1;
					menu.set_stones(inc_stone);//increase stones by 1
					if_stone = true; //change name
					show_bonus_stone(window);
					break;
				case 'C':
					m_gift.setPlayingOffset(sf::seconds(0));
					m_gift.play(); 
					m_clock_bonuses++;
					m_time_bonus = true;
					show_bonus_clock(window);
					break;
				case 'D':
					m_eating.setPlayingOffset(sf::seconds(0));
					m_eating.play();
					m_points += 15;
					menu.set_points(m_points);
					level.diamond_eaten();
					break;
				}
				level.set_object_null(digg_fix);
			}
			else if (typeid(*obj) == typeid(Stone)) //if the object is stone
			{
				m_s_stone.setPlayingOffset(sf::seconds(0));
				m_s_stone.play(); 
				int dec_stone = -1;
				menu.set_stones(dec_stone);
				level.set_object_null(digg_fix);

				if (menu.get_stones() == 0)
				{
					InGameMusic.pause();
					m_lost.play(); //play the lost sound.
					Sleep(2000);

					m_lives--;
					menu.set_lives(m_lives);
					start_over(level); //set the characters in their beginning place.
					InGameMusic.play();
				}
			}
		}
	}

	for (int monster = 0; monster < m_monster_sum; monster++) //check colide with monster.
	{
		if ((abs(digger.get()->get_location().x - m_monster[monster].get_location().x) <= 15.f)
			&& (abs(digger.get()->get_location().y - m_monster[monster].get_location().y) <= 15.f))
		{
			m_lives--; //decrease the lives.
			sf::Texture* lost = Singleton::show().get_pic(12); //make a lost picture.
			sf::Sprite tropy;
			tropy.setTexture(*lost);
			tropy.setTextureRect(sf::IntRect(0, 0, 1200, 1000));
			window.draw(tropy);
			window.display(); //display the picture.
			InGameMusic.pause();
			m_lost.play(); //play the lost sound.
			Sleep(2000);
			menu.set_lives(m_lives); //set the lives in the title bar.
			start_over(level); //set the characters in their beginning place.
			InGameMusic.play();
		}
	}
}


//check the colides for the monster.
void Controller::monster_colide_check(Monster& monster, sf::Vector2f prev, Board& level, int width, int length)
{
	sf::Vector2f monster_fix = prev;
	StaticObject* obj;
	directions_t dirc_t = monster.get_direction();
	sf::Vector2i temp;

	if (dirc_t == up_t)
		monster_fix.y = monster_fix.y - 22.5;
	if (dirc_t == down_t)
		monster_fix.y = monster_fix.y + 22.5;
	if (dirc_t == left_t)
		monster_fix.x = monster_fix.x - 22.5;
	if (dirc_t == right_t)
		monster_fix.x = monster_fix.x + 22.5;

	temp.x = (int)monster_fix.x / (SHAPE+15);
	temp.y = (int)monster_fix.y / (SHAPE + 15);
	monster_fix.x = (float)temp.x * (SHAPE + 15) + 22.5;
	monster_fix.y = (float)temp.y * (SHAPE + 15) + 22.5;

	if (dirc_t != stand_t)
	{
		obj = level.get_object(monster_fix);
		if (obj != nullptr)
		{
			if (typeid(*obj) == typeid(Wall)) //if wall change direction.
			{
				monster.set_location(prev);
				int current = (int)dirc_t;
				int num = current;
				directions_t dirc = stand_t;

				while (current == num)
				{
					num = rand() % 4;
					switch (num)
					{
					case 0:
						dirc = up_t;
						break;
					case 1:
						dirc = down_t;
						break;
					case 2:
						dirc = left_t;
						break;
					case 3:
						dirc = right_t;
					}
				}
				monster.set_direction(dirc);
			}
		}
	}
}

// recreate the monster location.
void Controller::recreate_monster()
{
	for (int i = 0; i < m_monster_sum; i++)
	{
		sf::Vector2f temp;
		temp.x = (float)m_mons_info[i].location.x * (SHAPE+15) +22.5;
		temp.y = (float)m_mons_info[i].location.y * (SHAPE+15) +22.5;
		m_monster[i].set_location(temp);
	}
}


