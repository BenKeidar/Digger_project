#include "HelpButton.h"

//build the help button.
HelpButton::HelpButton()
{
	m_sprite.setTexture(*m_text); //set the first pic
	m_sprite.setTextureRect(sf::IntRect(190, 280, 620, 94));
	m_sprite.setPosition(360, 480);
	//m_sprite.setScale(1.2,1.2);
	m_button_on.setTexture(*m_text); //set the second pic
	//m_button_on.setColor(sf::Color::Green);
	m_button_on.setTextureRect(sf::IntRect(190, 380, 620, 94));
	m_button_on.setPosition(360, 480);
	m_button_before = m_sprite;
	//m_button_on.setScale(1.2,1.2);
	m_button_help = false;
}

//define whats happened when the user click on exit in the menu.
void HelpButton::ClickOn(sf::Vector2f pos, sf::RenderWindow& window, bool& exit_on)
{
	sf::Sprite helpS;
	sf::Texture* helpT;
	if (!m_sprite.getGlobalBounds().contains(pos))
		return;
	helpT = Singleton::show().get_pic(13); //load the help pic from the singleton.
	helpS.setTexture(*helpT);

	window.clear();
	window.draw(helpS); //show the help screen.
	window.display();

	sf::Vector2f mouseCoords;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			case sf::Event::KeyPressed:
			case sf::Event::MouseButtonPressed:
				return;
			}
		}
	}
}

//define whats happened when the user move on exit in the menu.
void HelpButton::moveOn(sf::Vector2f pos)
{
	if (m_sprite.getGlobalBounds().contains(pos))
		m_sprite = m_button_on;
	else
		m_sprite = m_button_before;
}

//print the button.
void HelpButton::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

HelpButton::~HelpButton()
{}
