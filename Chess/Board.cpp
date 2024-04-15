#include "Board.h"

Board::Board(int _squareWidth, int _squareHeight)
{	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Color colour = (j + i) % 2 == 0 ? BEIGE : BROWN;

			squares[j + i * 8] = new Square{ colour, nullptr, _squareWidth, _squareHeight, j, i};
		}
	}

	squareHeight = _squareHeight;
	squareWidth = _squareWidth;
	piecesTextureSheet = LoadTextureFromImage(LoadImage("Assets/chess_assets.png"));
}

void Board::DrawBoard()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			DrawRectangle(j * squareWidth, i * squareHeight, squareWidth, squareHeight, squares[j+i*8]->colour);
		}
	}
}

void Board::DrawSquare(int x, int y, Color colour)
{
	DrawRectangle(x * squareWidth, y * squareHeight, squareWidth, squareHeight, colour);
}

Piece* Board::GetPiece(int x, int y)
{
	return squares[x + 8 * y]->piece;
}


Square* Board::GetSquare(int x, int y)
{
	return squares[(x / squareWidth) + (y / squareHeight) * 8];
}