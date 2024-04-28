#include "Piece.h"
#include "King.h"


Piece::Piece(int x, int y, const char* colour, int squareWidth, int squareHeight)
{
	isActive = false;
	posX = x, posY = y;
	name = "PIECE";
	this->colour = colour == "WHITE" ? "WHITE" : "BLACK";
	source = Rectangle{ 0 };
	texturePosition = Rectangle{ (float)x * squareWidth, (float)y * squareHeight, (float)squareWidth, (float)squareHeight };
	isInCheck = false;
}

void Piece::Draw(float x, float y, int squareWidth, int squareHeight, Texture2D& piecesTextureSheet)
{
	Rectangle destRect = { x, y, squareWidth, squareHeight };

	DrawTexturePro(piecesTextureSheet, source, destRect, Vector2{0,0}, 0.0f, RAYWHITE);
}

void Piece::ShowPossibleMoves(Square* squares[64])
{

	if (!validMoves.empty())
	{
		for (auto& move : validMoves)
		{
			if (squares[move->x + move->y * 8]->piece != nullptr)
				move->colour = RED;
			else
				move->colour = (move->x + move->y) % 2 == 0 ? DARKBLUE : BLUE;
		}

	}
}

void Piece::HidePossibleMoves(Square* squares[64])
{
	if (!validMoves.empty())
	{
		for (auto& move : validMoves)
			move->colour = (move->x + move->y) % 2 == 0 ? BEIGE : BROWN;
	}
}

void Piece::AddMove(Square* squares[64], Square* move, bool checkCheck)
{
	validMoves.push_back(move);
}

Square* Piece::GetKing(Square* squares[64], const char* colour)
{
	for (int i = 0 ; i < 64; i++)
	{
		if (squares[i]->piece != nullptr)
		{
			if (squares[i]->piece->GetType() == "KING" && squares[i]->piece->colour == colour)
				return squares[i];
		}
	}
}
