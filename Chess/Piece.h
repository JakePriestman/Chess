#pragma once

#include "raylib.h"
#include <vector>

//Location for Piece textures
#define PAWN_WHITE CLITERAL(Rectangle) {1600,0,320,320}
#define KNIGHT_WHITE CLITERAL(Rectangle) {960,0,320,320}
#define BISHOP_WHITE CLITERAL(Rectangle) {640,0,320,320}
#define ROOK_WHITE CLITERAL(Rectangle) {1280,0,320,320}
#define QUEEN_WHITE CLITERAL(Rectangle) {320,0,320,320}
#define KING_WHITE CLITERAL(Rectangle) {0,0,320,320}

#define PAWN_BLACK CLITERAL(Rectangle) {1600,320,320,320}
#define KNIGHT_BLACK CLITERAL(Rectangle) {960,320,320,320}
#define BISHOP_BLACK CLITERAL(Rectangle) {640,320,320,320}
#define ROOK_BLACK CLITERAL(Rectangle) {1280,320,320,320}
#define QUEEN_BLACK CLITERAL(Rectangle) {320,320,320,320}
#define KING_BLACK CLITERAL(Rectangle) {0,320,320,320}

class Square;

class Piece
{
public:
	bool isActive;

	const char* name;

	int posX, posY;

	const char* colour;

	bool isInCheck;

	Rectangle source, texturePosition;

	std::vector<Square*> validMoves;

	Piece() = default;

	Piece(int x, int y, const char* colour, int squareWidth, int squareHeight);

	const char* GetType()
	{
		return name;
	}

	void Draw(float x, float y, int squareWidth, int squareHeight, Texture2D& piecesTextureSheet);

	virtual void CalculatePossibleMoves(Square* squares[64], bool checkCheck) {  };

	void ShowPossibleMoves(Square* squares[64]);

	void HidePossibleMoves(Square* squares[64]);

	void AddMove(Square* squares[64], Square* move, bool checkCheck);

	std::vector<Square*> GetPossibleMoves() { return validMoves; };

	virtual bool Move(Square* square, Square* squares[64]) { return false; };

	virtual void SetCheck(Square* squares[64]) { };

	static Square* GetKing(Square* squares[64], const char* colour);

	bool IsHeld()
	{
		return (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), texturePosition));
	};

};

class Square
{
public:
	Color colour;
	Piece* piece;
	int width, height, x, y;
};

