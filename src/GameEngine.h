#pragma once

#include <SFML/Graphics.hpp>

#include "GUI.h"
#include "GUIMenu.h"
#include "GameData.h"
#include "WorldManager.h"


class GameEngine
{
public:
	GameEngine();
	virtual ~GameEngine();

public:
	void run();
	void close();

protected:
	//Functions
	void draw();
	void display();
	
	void initialize();
	void uninitialize();
	
	void loadContent();
	void unloadContent();

	void update(sf::Time &elapsedTime);
	void updateGame(sf::Time &elapsedTime);
	void updateMainMenu(sf::Time &elapsedTime);

	void handleEvents(sf::Time &elapsedTime);
	void handleKeyboardEvent(sf::Event &event, sf::Time &elapsedTime);

protected:
	//Variables
	GUI gui;
	GUIMenu *menu;
	GameData data;
	WorldManager world;
	sf::RenderWindow *window;
};

