#include "ExitButton.h"




ExitButton::ExitButton()
{
	m_sprite.setTexture(*m_text); //set the first pic
	m_sprite.setTextureRect(sf::IntRect(190, 470, 500, 105));
	m_sprite.setPosition(360, 630);
	//m_sprite.setScale(1.2, 1.2);
	m_button_on.setTexture(*m_text); //set the second pic.
	//m_button_on.setColor(sf::Color::Green);
	m_button_on.setTextureRect(sf::IntRect(190, 570, 500, 105));
	m_button_on.setPosition(360, 630);
	//m_button_on.setScale(1.2, 1.2);
	m_button_before = m_sprite;
}



//define whats happened when the user click on exit in the menu.
void ExitButton::ClickOn(sf::Vector2f pos, sf::RenderWindow& window, bool& exit_on)
{
	if (!m_sprite.getGlobalBounds().contains(pos))
		return;
	exit_on = false; //update the exit on boolian (do not open the menu again).
	window.close();
}

//define whats happened when the user move on the exit in the menu.
void ExitButton::moveOn(sf::Vector2f pos)
{
	if (m_sprite.getGlobalBounds().contains(pos))
		m_sprite = m_button_on; //switch between the pictures.
	else
		m_sprite = m_button_before;
}

//draw the button.
void ExitButton::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

ExitButton::~ExitButton()
{}