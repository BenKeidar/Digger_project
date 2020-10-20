#pragma once
#include <SFML\Graphics.hpp>
#include "MenuButton.h"
#include <memory>
#include "StartButton.h"
#include "HelpButton.h"
#include "ExitButton.h"

class Menu
{
public:
	Menu();//constructor
   ~Menu();//distructor

	void run(bool& exit_on);//the main funcion of the menu
	
private:
	bool m_menu;

	std::vector <std::unique_ptr<MenuButton>> m_vector_but;
	sf::Sprite m_back;
	sf::Music menuMusic;
};

