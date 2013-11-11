#include "Snake.h"
#include "AEntity.h"


AEntity::AEntity(EntityType entityType)
	: type(entityType),
	  isAlive(true),
	  position(-1, -1)
{
}


AEntity::~AEntity()
{
}


bool AEntity::collidesWith(const AEntity &other)
{
	// For the snake, check for all its body parts
	if (other.type == ENTITY_SNAKE)
	{
		const Snake & snake = static_cast<const Snake &>(other);
		
		// Check for the head's position
		if (position == snake.position)
			return true;

		// Check for the tail as well
		for (SnakeTail::const_iterator it = snake.tail.begin(); it != snake.tail.end(); it++)
			if (position == *it)
				return true;
	}
	
	// For all other types of entities, simply compare the entities' positions
	return (position == other.position);
}
