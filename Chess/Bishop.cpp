#include "Bishop.h"

Bishop::Bishop(int x, int y, const char* colour, int squareWidth, int squareHeight) : Piece(x, y, colour, squareWidth, squareHeight)
{
	source = colour == "WHITE" ? BISHOP_WHITE : BISHOP_BLACK;
	name = "BISHOP";
}

void Bishop::CalculatePossibleMoves(Square* squares[64], bool checkCheck)
{
	for (int i = posX - 1; i >= 0; i--)
	{
		int j = posY - (posX-i);
		if (j >= 0 && j <= 7)
		{
			if (squares[i + j * 8]->piece == nullptr)
				AddMove(squares, squares[i + j * 8], checkCheck);

			if (squares[i + j * 8]->piece != nullptr && squares[i + j * 8]->piece->colour == colour)
				break;

			if (squares[i + j * 8]->piece != nullptr && squares[i + j * 8]->piece->colour != colour)
			{
				AddMove(squares, squares[i + j * 8], checkCheck);
				break;
			}
		}
	}

	for (int i = posX - 1; i >= 0; i--)
	{
		int j = posY + (posX - i);
		if (j >= 0 && j <= 7)
		{
			if (squares[i + j * 8]->piece == nullptr)
				AddMove(squares, squares[i + j * 8], checkCheck);

			if (squares[i + j * 8]->piece != nullptr && squares[i + j * 8]->piece->colour == colour)
				break;

			if (squares[i + j * 8]->piece != nullptr && squares[i + j * 8]->piece->colour != colour)
			{
				AddMove(squares, squares[i + j * 8], checkCheck);
				break;
			}
		}
	}

	for (int i = posX + 1; i < 8; i++)
	{
		int j = posY - (i - posX);
		if (j >= 0 && j <= 7)
		{
			if (squares[i + j * 8]->piece == nullptr)
				AddMove(squares, squares[i + j * 8], checkCheck);

			if (squares[i + j * 8]->piece != nullptr && squares[i + j * 8]->piece->colour == colour)
				break;

			if (squares[i + j * 8]->piece != nullptr && squares[i + j * 8]->piece->colour != colour)
			{
				AddMove(squares, squares[i + j * 8], checkCheck);
				break;
			}
		}
	}

	for (int i = posX + 1; i < 8; i++)
	{
		int j = posY + (i - posX);
		if (j >= 0 && j <= 7)
		{
			if (squares[i + j * 8]->piece == nullptr)
				AddMove(squares, squares[i + j * 8], checkCheck);

			if (squares[i + j * 8]->piece != nullptr && squares[i + j * 8]->piece->colour == colour)
				break;

			if (squares[i + j * 8]->piece != nullptr && squares[i + j * 8]->piece->colour != colour)
			{
				AddMove(squares, squares[i + j * 8], checkCheck);
				break;
			}
		}
	}
}

bool Bishop::Move(Square* square, Square* squares[64])
{
	for (auto& move : validMoves)
	{
		if (square == move)
		{
			squares[posX + posY * 8]->piece = nullptr;

			posX = move->x;
			posY = move->y;
			move->piece = this;

			isActive = false;
			texturePosition = Rectangle{ (float)posX * move->width, (float)posY * move->height, (float)move->width, (float)move->height };
			HidePossibleMoves(squares);
			return true;
		}
	}
	return false;
}