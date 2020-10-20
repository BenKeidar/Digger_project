#pragma once
#include "MenuButton.h"
class ExitButton :public MenuButton
{
public:
	ExitButton();//constructor
   ~ExitButton();
	virtual void ClickOn(sf::Vector2f pos, sf::RenderWindow& window, bool& exit_on);
	virtual sf::Sprite getSprite() { return m_sprite; };
	virtual void moveOn(sf::Vector2f pos);
	virtual void draw(sf::RenderWindow& window);
};

