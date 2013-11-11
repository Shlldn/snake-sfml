#pragma once

#include "AEntity.h"


class Food : public AEntity
{
public:
	Food();
	~Food(void);

public:
	virtual void update(sf::Time &elapsedTime);
};

