#pragma once
#include "Piece.h"


class King : public Piece
{
public:
	King() = default;

	King(int x, int y, const char* colour, int squareWidth, int squareHeight);

	virtual void CalculatePossibleMoves(Square* squares[64], bool checkCheck);

	virtual bool Move(Square* square, Square* squares[64]);

	virtual void SetCheck(Square* squares[64]);

	bool hasMoved;
};