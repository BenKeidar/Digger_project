#pragma once
#include "MenuButton.h"
class HelpButton :public MenuButton
{
public:
	HelpButton();//constructor
   ~HelpButton();

	virtual void ClickOn(sf::Vector2f pos, sf::RenderWindow& window, bool& exit_on);// define what happened when you click on the button
	virtual sf::Sprite getSprite() { return m_sprite; };//func to return sprite.
	virtual void moveOn(sf::Vector2f pos);// define what happened when you move on the button.
	virtual void draw(sf::RenderWindow& window);
	
private:
	bool m_button_help;
};

