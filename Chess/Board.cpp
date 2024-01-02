#include "Board.h"

void Board::DrawBoard(int width, int height)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Color colour = (j + i) % 2 == 0 ? WHITE : BLACK;

			DrawRectangle(j * width, i * height, width, height, colour);
		}
	}
}