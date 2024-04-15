#pragma once

#include "Piece.h"

class Pawn : public Piece
{
public:
	bool isFirstMove;

	int dy;

	Pawn() = default;

	Pawn(int x, int y, const char* colour, int squareWidth, int squareHeight);

	virtual void CalculatePossibleMoves(Square* squares[64], bool checkCheck);

	virtual bool Move(Square* square, Square* squares[64]);
};
