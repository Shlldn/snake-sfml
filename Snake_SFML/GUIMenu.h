#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "GameData.h"


class GUIMenu
{
public:
	GUIMenu(GameData &data);
	virtual ~GUIMenu();

public:
	void initialize();
	void loadContent();

	void update(sf::Time &elapsedTime);
	void draw(sf::RenderWindow &window);

	void handleKeyboardEvent(sf::Event &event, sf::Time &elapsedTime);

public:
	GameData &data;

	// Font properties
	sf::Font font;
	std::string fontName;
	int fontSize;
	sf::Color fontColor;

	std::vector<sf::Text> text;
	std::vector<sf::String> items;
	int selectedItemIdx;
	bool needUpdate;
};

