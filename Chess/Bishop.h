#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop() = default;

	Bishop(int x, int y, const char* colour, int squareWidth, int squareHeight);

	virtual void CalculatePossibleMoves(Square* squares[64], bool checkCheck);

	virtual bool Move(Square* square, Square* squares[64]);
};