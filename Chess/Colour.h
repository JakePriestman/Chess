#pragma once

#include "Pawn.h"

class Colour
{
public:
	//TODO: ADD PIECES
	Colour() = default;

	Colour(int colour);

	void Draw();

	Pawn pawn[8];

private:
	Color _colour;
};
