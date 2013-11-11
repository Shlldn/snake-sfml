#pragma once

#include <SFML/Graphics.hpp>

#include "GameData.h"
#include "WorldManager.h"
#include "GUIMenu.h"
#include "GUI.h"


class GameEngine
{
public:
	GameEngine();
	virtual ~GameEngine();

public:
	void run();
	void close();

protected:
	void initialize();
	void uninitialize();
	void loadContent();
	void unloadContent();

	void update(sf::Time &elapsedTime);
	void updateMainMenu(sf::Time &elapsedTime);
	void updateGame(sf::Time &elapsedTime);
	void draw();
	void display();

	void handleEvents(sf::Time &elapsedTime);
	void handleKeyboardEvent(sf::Event &event, sf::Time &elapsedTime);

protected:
	GameData data;
	WorldManager world;
	GUIMenu *menu;
	GUI gui;
	sf::RenderWindow *window;
};

