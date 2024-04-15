#include "Knight.h"

Knight::Knight(int x, int y, const char* colour, int squareWidth, int squareHeight) : Piece(x, y, colour, squareWidth, squareHeight)
{
	source = colour == "WHITE" ? KNIGHT_WHITE: KNIGHT_BLACK;
	name = "KNIGHT";
}

void Knight::CalculatePossibleMoves(Square* squares[64], bool checkCheck)
{
	for (int j = posY - 2; j <= posY+2; j += 4)
	{
		if (posX - 1 >= 0 && j >=0 && j <8)
		{
			if (squares[posX - 1 + 8 * j]->piece != nullptr && squares[posX - 1 + 8 * j]->piece->colour != colour)
				AddMove(squares, squares[posX - 1 + 8 * j], checkCheck);
			//CASTLE CHECK HERE
			else if (squares[posX - 1 + 8 * j]->piece == nullptr)
				AddMove(squares, squares[posX - 1 + 8 * j], checkCheck);
		}

		if (posX + 1 < 8 && j >= 0 && j < 8)
		{
			if (squares[posX + 1 + 8 * j]->piece != nullptr && squares[posX + 1 + 8 * j]->piece->colour != colour)
				AddMove(squares, squares[posX + 1 + 8 * j], checkCheck);
			//CASTLE CHECK HERE
			else if (squares[posX + 1 + 8 * j]->piece == nullptr)
				AddMove(squares, squares[posX + 1 + 8 * j], checkCheck);
		}
	}

	for (int i = posX - 2; i <= posX + 2; i += 4)
	{
		if (posY - 1 >= 0 && i >= 0 && i < 8)
		{
			if (squares[i + 8 * (posY-1)]->piece != nullptr && squares[i + 8 * (posY - 1)]->piece->colour != colour)
				AddMove(squares, squares[i + 8 * (posY - 1)], checkCheck);
			//CASTLE CHECK HERE
			else if (squares[i + 8 * (posY - 1)]->piece == nullptr)
				AddMove(squares, squares[i + 8 * (posY - 1)], checkCheck);
		}

		if (posY + 1 < 8 && i >= 0 && i < 8)
		{
			if (squares[i + 8 * (posY + 1)]->piece != nullptr && squares[i + 8 * (posY + 1)]->piece->colour != colour)
				AddMove(squares, squares[i + 8 * (posY + 1)], checkCheck);
			//CASTLE CHECK HERE
			else if (squares[i + 8 * (posY + 1)]->piece == nullptr)
				AddMove(squares, squares[i + 8 * (posY + 1)], checkCheck);
		}
	}
}

bool Knight::Move(Square* square, Square* squares[64])
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