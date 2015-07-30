#pragma once

#include <vector>

#include "AEntity.h"
#include "Food.h"
#include "GameSettings.h"
#include "Snake.h"


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
