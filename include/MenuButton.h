#pragma once
#include <SFML\Graphics.hpp>
#include "Singleton.h"

class MenuButton
{
public:
	MenuButton();//constructor
    virtual ~MenuButton();//distructor
	virtual void ClickOn(sf::Vector2f pos, sf::RenderWindow& window, bool& exit_on) = 0;// define what happened when you click on the button
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual sf::Sprite getSprite() = 0;//func to return sprite.
	virtual void moveOn(sf::Vector2f pos) = 0;// define what happened when you move on the button.
	

protected:
	sf::Texture* m_text;
	sf::Sprite m_sprite;
	sf::Sprite m_button_on;
	sf::Sprite m_button_before;
};

