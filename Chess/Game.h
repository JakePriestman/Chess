#pragma once

#include "Board.h"


class Game
{
public:
	Game() = default;

	Board *board;
	
	void update();
	void init(int width, int height, const char* title, int fps);
	void handleEvents();
	void render();
	void clean();
	void run(int width, int height, const char* title, int fps);

private:

};