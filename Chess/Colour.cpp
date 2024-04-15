#include "Colour.h"

Colour::Colour(int colour)
{
	int row = colour == 0 ? 6 : 1;
	_colour = colour == 0 ? WHITE : BLACK;

	for (int i = 0; i < 8; i++)
	{
		pawn[i] = Pawn{i, row, _colour};
	}
}

void Colour::Draw()
{
	for (int i = 0; i < 8; i++)
	{
		pawn[i].Draw(PAWN, 80, 80);
	}
}