#include "Board.h"
#include "Wall.h"
#include "Diamond.h"
#include <Stone.h>
#include <Controller.h>


// build the level by the level number.
Board::Board(int level) 
{
	m_level = level;
	m_monster_sum = 0;

	ifstream file; //to read from file.
	char num = (char)(m_level)+'0';
	string end = ".txt";
	string file_name = "";
	file_name += num;
	file_name += end;
	file.open(file_name); //the name of the file.
	copy_to_file_vector(file); //copy to the file vector.
	make_m_board(); //do assign to the m_board.
	define_m_board(m_file_vector); //copy to the static vector.
}


//draw the static objects on the board.
void Board::draw(sf::RenderWindow& win, float clock_sample)
{
	for (int y = 0; y < m_length; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			if (m_board[y][x])	//if not null
				m_board[y][x]->draw(win, clock_sample);
		}
	}
}


//return the digger location.
sf::Vector2i Board::get_dig_location()
{
	return digger.location;
}

//return the digger icon.
char Board::get_dig_icon()
{
	return digger.icon;
}

//return a struct of monster location and his icon by the number.
struct keep_info Board::get_monster(int mons)
{
	return monster[mons];
}


//return the total number of monster.
int Board::get_monster_sum()
{
	return m_monster_sum;
}


//return the width
int Board::get_width()
{
	return m_width;
}


//return the lenth
int Board::get_length()
{
	return m_length;
}



// copy the level string from file to the string vector.
void Board::copy_to_file_vector(ifstream& file)
{
	Toolbar item_update;
	Controller time_update;

	string line;

	file >> m_length >> m_width; //read width and length.
	file >> m_stone >> m_time;  //read stone allowed to eat and time limit for level

	item_update.set_stones(m_stone);
	item_update.set_clock(m_time);

	getline(file, line); //eat enter;

	for (int index = 0; index < m_length; index++) // build the map
	{
		getline(file, line);
		m_file_vector.push_back(line);
	}
}

// translate the static objects from location and icon (from the file vector) to 
//static objects . and keep ditails about digger and the monsters.
void Board::define_m_board(vector<string>m_file_vector)
{
	char icon;
	m_diamond = 0;
	sf::Vector2i location;

	for (int y = 0; y < m_length; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			location.x = x;
			location.y = y;

			icon = m_file_vector[y][x];

			switch (icon)
			{
				case '#':m_board[y][x] = make_unique <Wall>(location, '#'); //wall
					break;
				case 'D':m_board[y][x] = make_unique <Diamond>(location, 'D'); //diamond
					m_diamond++;
					break;
				case '@':m_board[y][x] = make_unique <Stone>(location, '@'); //Stone
					break;
				case '/':
				{
					digger.icon = icon;
					digger.location = location;
					break;
				}
				case '%'://monsters
				case '!':
				{
					struct keep_info mons;
					mons.icon = icon;
					mons.location = location;
					monster.push_back(mons);
					m_monster_sum++;
				}
			} 
		}
	}
}

// build the m_board vector and define him to be nullptr in every cell.
void Board::make_m_board()
{
	m_board.resize(m_length);

	for (int i = 0; i < m_length; i++)
	{
		m_board[i].resize(m_width);
	}

	for (int i = 0; i < m_length; i++)
	{
		for (int j = 0; j < m_width; j++)
			m_board[i][j] = nullptr;
	}
}


// return pointer to static object from the static board by float location.
StaticObject* Board::get_object(sf::Vector2f place)
{
	sf::Vector2i object;
	object.x = (int)place.x / 45;
	object.y = (int)place.y / 45;
	if (object.y >= m_length || object.x >= m_width)
		return nullptr;

	return m_board[object.y][object.x].get();

}


// when diamond has been eaten this funcion will update the sum of diamonds on the board. 
void Board::diamond_eaten()
{
	m_diamond--;
}


// release a uniqe ptr object on the board.
//we use this for eating diamonds.
void Board::set_object_null(sf::Vector2f place)
{
	sf::Vector2i object;
	object.x = (int)place.x / (SHAPE + 15);
	object.y = (int)place.y / (SHAPE + 15);

	m_board[object.y][object.x] = nullptr;
}


// return the number of diamonds.
int Board::get_diamond()
{
	return m_diamond;
}

int Board::get_stones()
{
	return m_stone;
}

void Board::stone_eaten()
{
	m_stone--;
}

// set the gift on the static board. by location and icon.
void Board::set_gift(int x, int y, char icon)
{
	sf::Vector2i location;
	location.x = x;
	location.y = y;
	switch (icon)
	{
	case 'P': m_board[y][x] = make_unique <Diamond>(location, 'P');
		break;
	case 'S': m_board[y][x] = make_unique <Diamond>(location, 'S');
		break;
	case 'C': m_board[y][x] = make_unique <Diamond>(location, 'C');
		break;
	}
}

int Board::get_time()
{
	return m_time;
}

void Board::set_time(int elapsed)
{
	m_time = elapsed;
	std::cout << m_time << std::endl;
}


