#pragma once

#include <vector>

#include "Food.h"
#include "Snake.h"
#include "AEntity.h"
#include "GameSettings.h"


class WorldManager
{
public:
	WorldManager(GameSettings &settings);
	~WorldManager();

public:
	void initialize();

	void addEntity(AEntity *entity);
	void removeEntity(AEntity *entity);

	void update(sf::Time & elapsedTime);
	void draw(sf::RenderWindow &window);

public:
	Snake *snake;
	GameSettings &settings;
	std::vector<AEntity*> entities;
};
