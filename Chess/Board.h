#pragma once

#include "raylib.h"
#include "Piece.h"

//#define SQUARE_HEIGHT CLITERAL (int)80
//#define SQUARE_WIDTH CLITERAL (int)80


class Board
{
public:
	Board() = default;

	Board(int squareWidth, int squareHeight);

	void DrawBoard();

	void DrawSquare(int x, int y, Color colour);

	Piece* GetPiece(int x, int y);

	Square* GetSquare(int x, int y);

	Square* squares[64];

	Texture2D piecesTextureSheet;

	int squareWidth, squareHeight;

};