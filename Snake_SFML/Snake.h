#pragma once

#include "AEntity.h"
#include "Food.h"


typedef	std::vector<sf::Vector2i>	SnakeTail;


enum Direction
{
	DIRECTION_UP,
	DIRECTION_LEFT,
	DIRECTION_DOWN,
	DIRECTION_RIGHT,
	DIRECTION_NONE
};


class Snake : public AEntity
{
public:
	Snake();
	virtual ~Snake();

private:
	Snake(Snake const &) {}

public:
	virtual void update(sf::Time & elapsedTime);
	void initialize();
	void spawn();
	void die();
	void eat(const Food & food);
	void addBodyPart(int x, int y);

public:
	SnakeTail tail;
	int score;
	int lives;

	int lengthToGrow;
	int speedLevel;
	Direction nextDirection;
	Direction prevDirection;
	sf::Time prevMovement; // ms
	sf::Time movementDelay; // ms
	sf::Time initialMovementDelay; // ms
};
