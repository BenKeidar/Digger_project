#include "StartButton.h"
#include "Controller.h"

// create the button (like the other buttons).
StartButton::StartButton()
{
	m_sprite.setTexture(*m_text);
	m_sprite.setTextureRect(sf::IntRect(190, 72, 620, 88));
	m_sprite.setPosition(360, 320);
	//m_sprite.setScale(1.2, 1.2);
	m_button_on.setTexture(*m_text);
	//m_button_on.setColor(sf::Color::Green);
	m_button_on.setTextureRect(sf::IntRect(190, 172, 620, 88));
	m_button_on.setPosition(360, 320);
	//m_button_on.setScale(1.2, 1.2);
	m_button_before = m_sprite;

}

// define what happened when you click on the button.
//in that case it will create a Controller object and will run the game.
void StartButton::ClickOn(sf::Vector2f pos, sf::RenderWindow& window, bool& exit_on)
{
	if (!m_sprite.getGlobalBounds().contains(pos))
		return;

	window.close();
	Controller game;
	game.run();
}

// define what happened when you move on the button.
void StartButton::moveOn(sf::Vector2f pos)
{
	if (m_sprite.getGlobalBounds().contains(pos))
		m_sprite = m_button_on;
	else
		m_sprite = m_button_before;
}

// draw the button.
void StartButton::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

StartButton::~StartButton()
{}