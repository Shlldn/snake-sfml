#include <iostream>
#include "GameEngine.h"


int main()
{
	try
	{
		GameEngine game;

		game.run();
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (...)
	{
		std::cerr << "Unhandled exception" << std::endl;
		return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}

