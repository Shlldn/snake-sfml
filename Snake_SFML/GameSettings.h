#pragma once

struct	GameSettings
{
public:
	// Display
	int windowWidth;
	int windowHeight;
	//int		aspectRatio;
	bool limitFPS;
	int maxFPS;
	bool verticalSync;

	int unit;
	int viewSize;
	int viewOffset;
	
	// World
	int rowsNb;
	int colsNb;
};

