#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
class Singleton
{
public:
	static Singleton& show();
	sf::Texture* get_pic(int pic_num);

	~Singleton();
private:
	Singleton();
	Singleton(const Singleton&) = delete;

	Singleton& operator=(const Singleton&) = delete;
	sf::Texture pic_arr[100];
};