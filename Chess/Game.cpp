#include "Game.h"


void Game::update()
{

}

void Game::init(int width, int height, const char* title, int fps)
{
	InitWindow(width, height, title);

	SetTargetFPS(fps);

	Game::board = new Board();
}

void Game::handleEvents()
{
	PollInputEvents();
}

void Game::render()
{
	BeginDrawing();

	ClearBackground(GRAY);

	int width = GetRenderWidth() / 8;
	int height = GetRenderHeight() / 8;

	board->DrawBoard(width, height);

	/*Image pawn = LoadImage("Assets/chess_assets.png");

	Texture2D pawntex = LoadTextureFromImage(pawn);

	DrawTexturePro(pawntex, { 1920-320,0,320,320 }, { 0, 0, (float)width, (float)height }, Vector2{ 0,0 }, 0, WHITE);*/

	EndDrawing();
}

void Game::clean()
{
	CloseWindow();
}


void Game::run(int width, int height, const char* title, int fps)
{
	this->init(width, height, title, fps);

	while (!WindowShouldClose())
	{
		this->handleEvents();
		this->update();
		this->render();
	}

	this->clean();
}