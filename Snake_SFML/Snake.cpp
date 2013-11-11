#include "Snake.h"


Snake::Snake()
	: tail(SnakeTail()),
	  AEntity(ENTITY_SNAKE)
{
	initialize();
}


Snake::~Snake(void)
{
}


void Snake::update(sf::Time & elapsedTime)
{
	prevMovement += elapsedTime;
	
	if (prevMovement >= movementDelay)
	{
		// If there is at least 1 body part to grow, grow it
		if (lengthToGrow > 0)
		{
			tail.push_back(sf::Vector2i());
			lengthToGrow--;
		}
		
		// Move each part of the tail to the next part's position
		for (SnakeTail::reverse_iterator it = tail.rbegin(); it != tail.rend(); it++)
		{
			SnakeTail::reverse_iterator itNext = it + 1;
			if (itNext != tail.rend())
				*it = *itNext;
			else
				*it = position;
		}

		// Move the head in the next direction
		switch (nextDirection)
		{
		case DIRECTION_UP:
			position.y--;
			break;
		case DIRECTION_LEFT:
			position.x--;
			break;
		case DIRECTION_DOWN:
			position.y++;
			break;
		case DIRECTION_RIGHT:
			position.x++;
			break;
		default:
			break;
		}

		// Update previous direction
		prevDirection = nextDirection;


		prevMovement -= movementDelay;
	}
}


/*
** Set the snake to its default state
*/
void Snake::initialize()
{
	position = sf::Vector2i(-1, -1);
	score = 0;
	lives = 3;
	lengthToGrow = 0;
	initialMovementDelay = sf::milliseconds(280);
}


void Snake::eat(const Food & food)
{
	static const int speeds[] = { 280, 230, 180, 130 };
	
	score += 1;
	lengthToGrow += 1;
	
	// Increase the speed level every 3 food items eaten up until level 3
	// [tail size minus two (the initial size of the tail) plus one (since the new tail part will be added later on)]
	if (speedLevel < 3 && (tail.size() - 1) % 3 == 0)
		speedLevel++;

	movementDelay = sf::milliseconds(speeds[speedLevel]);
}


void Snake::addBodyPart(int x, int y)
{
	tail.push_back(sf::Vector2i(x, y));
}


void Snake::spawn()
{
	nextDirection = DIRECTION_RIGHT;
	prevDirection = DIRECTION_RIGHT;
	
	position = sf::Vector2i(3, 1);
	addBodyPart(2, 1);
	addBodyPart(1, 1);

	lengthToGrow = 0;
	speedLevel = 0;

	prevMovement = sf::milliseconds(0);
	movementDelay = sf::milliseconds(initialMovementDelay.asMilliseconds());
}


void Snake::die()
{
	lives -= 1;
	if (lives < 0)
	{
		score = 0;
		lives = 3;
	}

	position = sf::Vector2i(0, 0);
	tail.clear();
	
	lengthToGrow = 0;
}

