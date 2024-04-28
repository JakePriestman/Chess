#include "King.h"
#include <iostream>;


King::King(int x, int y, const char* colour, int squareWidth, int squareHeight) : Piece(x, y, colour, squareHeight, squareHeight)
{
	source = colour == "WHITE" ? KING_WHITE : KING_BLACK;
	name = "KING";
	hasMoved = false;
	isInCheck = false;
}

void King::CalculatePossibleMoves(Square* squares[64], bool checkCheck)
{
	for (int i = posX - 1; i <= posX + 1; i++)
	{
		for (int j = posY - 1; j <= posY + 1; j++)
		{
			if (i == posX && j == posY)
				continue;
			if (i >= 0 && j >= 0 && i <= 7 && j <= 7)
			{
				if (squares[i + 8 * j]->piece != nullptr && squares[i + 8 * j]->piece->colour != colour)
					AddMove(squares, squares[i + 8 * j], checkCheck);

				else if (squares[i + 8 * j]->piece == nullptr)
					AddMove(squares, squares[i + 8 * j], checkCheck);
			}
		}
	}

	if (!hasMoved && squares[posX+1 + 8*posY]->piece == nullptr && squares[posX + 2 + 8 * posY]->piece == nullptr)
	{
		AddMove(squares, squares[posX + 2 + 8 * posY], checkCheck);
	}

	if (!hasMoved && squares[posX - 1 + 8 * posY]->piece == nullptr && squares[posX - 2 + 8 * posY]->piece == nullptr && squares[posX - 3 + 8 * posY]->piece == nullptr)
	{
		AddMove(squares, squares[posX - 2 + 8 * posY], checkCheck);
	}
}

bool King::Move(Square* square, Square* squares[64])
{
	for (auto& move : validMoves)
	{

		if (square == move)
		{
			if (!hasMoved && square == squares[posX+2+8*posY])
			{
				squares[posX + 3 + 8 * posY]->piece->posX -= 2;
				squares[posX + 1 + 8 * posY]->piece = squares[posX + 3 + 8 * posY]->piece;
				squares[posX + 1 + 8 * posY]->piece->texturePosition = Rectangle{ (float)squares[posX + 1 + 8 * posY]->piece->posX * move->width, (float)squares[posX + 1 + 8 * posY]->piece->posY * move->height, (float)move->width, (float)move->height };
				squares[posX + 3 + 8 * posY]->piece = nullptr;
				hasMoved = true;
				squares[posX + posY * 8]->piece = nullptr;

				posX = move->x;
				posY = move->y;
				move->piece = this;

				isActive = false;
				texturePosition = Rectangle{ (float)posX * move->width, (float)posY * move->height, (float)move->width, (float)move->height };
				HidePossibleMoves(squares);
				return true;
			}

			if (!hasMoved && square == squares[posX - 2 + 8 * posY])
			{
				squares[posX - 4 + 8 * posY]->piece->posX += 3;
				squares[posX - 1 + 8 * posY]->piece = squares[posX - 4 + 8 * posY]->piece;
				squares[posX - 1 + 8 * posY]->piece->texturePosition = Rectangle{ (float)squares[posX - 1 + 8 * posY]->piece->posX * move->width, (float)squares[posX - 1 + 8 * posY]->piece->posY * move->height, (float)move->width, (float)move->height };
				squares[posX - 4 + 8 * posY]->piece = nullptr;
				hasMoved = true;
				squares[posX + posY * 8]->piece = nullptr;

				posX = move->x;
				posY = move->y;
				move->piece = this;

				isActive = false;
				texturePosition = Rectangle{ (float)posX * move->width, (float)posY * move->height, (float)move->width, (float)move->height };
				HidePossibleMoves(squares);
				return true;
			}

			hasMoved = true;
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

void King::SetCheck(Square* squares[64])
{
	for (int i = 0; i < 64; i++)
	{
		if (squares[i]->piece != nullptr)
		{
			if (squares[i]->piece->colour != colour)
			{
				if (squares[i]->piece->GetType() == "KING")
				{
					if (abs(squares[i]->x - posX) <= 1 && abs(squares[i]->y - posY) <= 1)
					{
						isInCheck = true;
						std::cout << this->colour << "King:" << isInCheck << "\n";
						return;
					}
				}

				else if (squares[i]->piece->GetType() == "PAWN")
				{
					int dyPawn = squares[i]->piece->colour == "WHITE" ? 1 : -1;

					if ((posX == squares[i]->x + 1 || posX == squares[i]->x - 1) && posY == squares[i]->y - dyPawn)
					{
						isInCheck = true;
						std::cout << this->colour << "King:" << isInCheck << "\n";
						return;
					}
				}

				else
				{
					squares[i]->piece->GetPossibleMoves();
					for (auto& move : squares[i]->piece->validMoves)
					{
						if (move->x == posX && move->y == posY)
						{
							isInCheck = true;
							std::cout << this->colour << "King:" << isInCheck << "\n";
							return;
						}
					}
				}
			}
		}	
	}
	isInCheck = false;
	std::cout << this->colour << "King:" << isInCheck << "\n";
}