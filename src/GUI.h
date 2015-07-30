#pragma once

#include <SFML/Graphics.hpp>

#include "WorldManager.h"


class GUI
{
public:
	GUI();
	~GUI();

public:
	void update(sf::Time &elapsedTime, WorldManager &world);
	void draw(sf::RenderWindow &window);

public:
	sf::Font font;
	std::vector<sf::Text> text;
};

