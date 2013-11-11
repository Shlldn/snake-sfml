#pragma once

#include <SFML/Graphics.hpp>


enum EntityType
{
	ENTITY_NONE,
	ENTITY_SNAKE,
	ENTITY_FOOD,
};


class AEntity
{
public:
	AEntity(EntityType entityType = ENTITY_NONE);
	virtual ~AEntity();
	
public:
	virtual void update(sf::Time &elapsedTime) = 0;
	virtual bool collidesWith(const AEntity &other);

public:
	EntityType type;
	sf::Vector2i position;
	bool isAlive;
};
