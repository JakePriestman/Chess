#include "Rook.h"

Rook::Rook(int x, int y, const char* colour, int squareWidth, int squareHeight) : Piece(x, y, colour, squareWidth, squareHeight)
{
	source = colour == "WHITE" ? ROOK_WHITE : ROOK_BLACK;
	name = "ROOK";
	_hasMoved = false;
}

void Rook::CalculatePossibleMoves(Square* squares[64], bool checkCheck)
{
	for (int i = posX - 1; i >= 0; i--)
	{
		if (squares[i + posY * 8]->piece == nullptr)
			AddMove(squares, squares[i + posY * 8], checkCheck);

		if (squares[i + posY * 8]->piece != nullptr && squares[i + posY * 8]->piece->colour == colour)
			break;

		if (squares[i + posY * 8]->piece != nullptr && squares[i + posY * 8]->piece->colour != colour)
		{
			AddMove(squares, squares[i + posY * 8], checkCheck);
			break;
		}
	}

	for (int i = posX + 1; i <= 7; i++)
	{
		if (squares[i + posY * 8]->piece == nullptr)
			AddMove(squares, squares[i + posY * 8], checkCheck);

		if (squares[i + posY * 8]->piece != nullptr && squares[i + posY * 8]->piece->colour == colour)
			break;

		if (squares[i + posY * 8]->piece != nullptr && squares[i + posY * 8]->piece->colour != colour)
		{
			AddMove(squares, squares[i + posY * 8], checkCheck);
			break;
		}
	}

	for (int j = posY - 1; j >= 0; j--)
	{
		if (squares[posX + j * 8]->piece == nullptr)
			AddMove(squares, squares[posX + j * 8], checkCheck);

		if (squares[posX + j * 8]->piece != nullptr && squares[posX + j * 8]->piece->colour == colour)
			break;

		if (squares[posX + j * 8]->piece != nullptr && squares[posX + j * 8]->piece->colour != colour)
		{
			AddMove(squares, squares[posX + j * 8], checkCheck);
			break;
		}
	}

	for (int j = posY + 1; j <= 7; j++)
	{
		if (squares[posX + j * 8]->piece == nullptr)
			AddMove(squares, squares[posX + j * 8], checkCheck);

		if (squares[posX + j * 8]->piece != nullptr && squares[posX + j * 8]->piece->colour == colour)
			break;

		if (squares[posX + j * 8]->piece != nullptr && squares[posX + j * 8]->piece->colour != colour)
		{
			AddMove(squares, squares[posX + j * 8], checkCheck);
			break;
		}
	}
}

bool Rook::Move(Square* square, Square* squares[64])
{
	for (auto& move : validMoves)
	{
		//TODO: Implement castling.
		if (square == move)
		{
			_hasMoved = true;
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