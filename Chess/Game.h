#pragma once

#include "Board.h"
#include "Pawn.h"
#include "King.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"

class Game
{
public:
	Game() = default;

	Board board;

	Piece* activePiece;

	static Texture2D textureSheet;

	Sound moveSound, captureSound, castleSound, checkSound;
	
	void Init(int width, int height, const char* title, int fps);
	void InitPieces();
	void HandleSound(bool exchange, Piece* king, bool kingHasMoved);
	void HandleEvents();
	void Render();
	void Clean();
	void Run(int width, int height, const char* title, int fps);

private:
	const char* _turn;
};