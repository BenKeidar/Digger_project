#include "Singleton.h"
#include <iostream>

Singleton::Singleton()
{
	pic_arr[0].loadFromFile("digger.png"); //digger picture
	pic_arr[1].loadFromFile("monster.png"); // monster picture.
	pic_arr[2].loadFromFile("diamond.png"); //diamond picture.
	pic_arr[3].loadFromFile("wall.png");	//wall picture.
	pic_arr[4].loadFromFile("game_won.png");
	pic_arr[5].loadFromFile("menu_buttons.png"); //the buttons.
	pic_arr[6].loadFromFile("menu_back.jpg"); //menu background.
	pic_arr[7].loadFromFile("points.png"); //points gift.
	pic_arr[8].loadFromFile("stone_gift.png"); //stone gift .
	pic_arr[9].loadFromFile("clock_gift.png"); //clock gift.
	pic_arr[10].loadFromFile("gameover.jpg"); //game over picture.
	pic_arr[11].loadFromFile("level_up.png"); //level_up picture.
	pic_arr[12].loadFromFile("lost.png"); //lost picture.
	pic_arr[13].loadFromFile("digger_help.png"); //help picture.
	pic_arr[14].loadFromFile("game_back.png"); //help picture.
	pic_arr[15].loadFromFile("stone.png"); //stone picture. 
	pic_arr[16].loadFromFile("+stone.png"); //stone picture.
	pic_arr[17].loadFromFile("+xp.png"); //xp picture.
	pic_arr[18].loadFromFile("+time.png"); //time picture.

	pic_arr[2].setSmooth(true);
	//pic_arr[6].setSmooth(true);
	//pic_arr[7].setSmooth(true);
	//pic_arr[8].setSmooth(true);
}

// will make a static object to get a picture.
Singleton& Singleton::show()
{
	static Singleton noun;
	return noun;
}

// return the picture from the array.
sf::Texture* Singleton::get_pic(int pic_num)
{

	return &pic_arr[pic_num];
}


Singleton::~Singleton()
{
}