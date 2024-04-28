#include "Pawn.h"
#include "Queen.h"

Pawn::Pawn(int x, int y, const char* colour, int squareWidth, int squareHeight) : Piece(x, y, colour, squareWidth, squareHeight)
{
	isFirstMove = true;
	source = colour == "WHITE" ? PAWN_WHITE : PAWN_BLACK;
	name = "PAWN";
	dy = colour == "WHITE" ? -1 : 1;
}

void Pawn::CalculatePossibleMoves(Square* squares[64], bool checkCheck)
{
	if (isFirstMove && squares[(posY + dy * 2) * 8 + posX]->piece == nullptr && squares[(posY + dy) * 8 + posX]->piece == nullptr)
		AddMove(squares, squares[(posY + dy * 2) * 8 + posX], checkCheck);

	if (posY != 0 || posY != 7)
	{
		if (squares[(posY + dy) * 8 + posX]->piece == nullptr)
			AddMove(squares, squares[(posY + dy) * 8 + posX], checkCheck);
		if (squares[(posY + dy) * 8 + posX + 1]->piece != nullptr && squares[(posY + dy) * 8 + posX + 1]->piece->colour != colour && posX != 7)
			AddMove(squares, squares[(posY + dy) * 8 + posX + 1], checkCheck);
		if (squares[(posY + dy) * 8 + posX - 1]->piece != nullptr && squares[(posY + dy) * 8 + posX - 1]->piece->colour != colour && posX != 0)
			AddMove(squares, squares[(posY + dy) * 8 + posX - 1], checkCheck);
	}
}

bool Pawn::Move(Square* square, Square* squares[64])
{
	for (auto& move : validMoves)
	{
		if (square == move)
		{
			isFirstMove = false;
			squares[posX + posY * 8]->piece = nullptr;

			posX = move->x;
			posY = move->y;

			if (move->y == 0 || move->y == 7)
			{
				move->piece = nullptr;
				move->piece = new Queen{ posX, posY, colour, move->width, move->height };
			}
			else
				move->piece = this;

			isActive = false;
			texturePosition = Rectangle{ (float)posX*move->width, (float)posY*move->height, (float)move->width, (float)move->height };
			HidePossibleMoves(squares);
			return true;
		}
	}
	return false;
}