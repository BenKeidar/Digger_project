#include "Menu.h"
#include <iostream>


// will build the menu of the game.
Menu::Menu() : m_menu()
{
	sf::Font font;

	m_vector_but.push_back(std::make_unique<StartButton>()); //create start button
	m_vector_but.push_back(std::make_unique<HelpButton>());	//create help button
	m_vector_but.push_back(std::make_unique<ExitButton>()); //create exit button

	m_back.setTexture(*(Singleton::show().get_pic(6)));
	m_back.setTextureRect(sf::IntRect(0, 0, 1200, 1000));

	menuMusic.openFromFile("MenuMusic.ogg");
}


// the main funcion of the menu.
// this will run until one of the buttons is pressed.
void Menu::run(bool& exit_on)
{
	sf::RenderWindow window(sf::VideoMode(1200, 1000, 92), "DIGGER", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(sf::Vector2i(220, 0));

	menuMusic.setLoop(true);
	menuMusic.play();

	while (window.isOpen())
	{

		sf::Event event;
		sf::Vector2f mouseCoords;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed: //check if the X is pressed.
				exit_on = false;
				window.close();
				break;

			case sf::Event::MouseButtonPressed: //check if button is pressed
			{
				mouseCoords.x = (float)event.mouseButton.x;
				mouseCoords.y = (float)event.mouseButton.y;
				for (size_t i = 0; i < m_vector_but.size(); ++i)
				{
					menuMusic.stop();
					m_vector_but[i]->ClickOn(mouseCoords, window, exit_on);
				}
				menuMusic.play();
			}
			case sf::Event::MouseMoved: //check if the mouse moved on the buttons.
			{
				mouseCoords = window.mapPixelToCoords({ event.mouseMove.x,event.mouseMove.y });
				for (size_t i = 0; i < m_vector_but.size(); ++i)
					m_vector_but[i]->moveOn(mouseCoords);
				break;
			}
			default:
				break;
			}
		}
		window.clear();
		window.draw(m_back);
		for (size_t i = 0; i < m_vector_but.size(); ++i)
			m_vector_but[i]->draw(window);
		window.display();
	}
}

Menu::~Menu()
{}

