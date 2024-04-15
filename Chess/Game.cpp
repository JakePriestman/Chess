#include "Game.h"

void Game::InitPieces()
{
	//Initialize Pawns
	for (int i = 0; i < 8; i++)
	{
		board.squares[i + (6 * 8)]->piece = new Pawn{ i, 6, "WHITE", board.squareWidth, board.squareHeight };
		board.squares[i + 8]->piece = new Pawn{ i, 1, "BLACK", board.squareWidth, board.squareHeight };
	}

	//Initialize Kings
	board.squares[4]->piece = new King{ 4, 0, "BLACK", board.squareWidth, board.squareHeight };
	board.squares[4 + 7 * 8]->piece = new King{ 4, 7, "WHITE", board.squareWidth, board.squareHeight };

	//Initialize rooks
	board.squares[0]->piece = new Rook{ 0, 0, "BLACK", board.squareWidth, board.squareHeight };
	board.squares[7]->piece = new Rook{ 7, 0, "BLACK", board.squareWidth, board.squareHeight };
	board.squares[7*8]->piece = new Rook{ 0, 7, "WHITE", board.squareWidth, board.squareHeight };
	board.squares[63]->piece = new Rook{ 7, 7, "WHITE", board.squareWidth, board.squareHeight };

	//Initialize Bishops
//	board.squares[2]->piece = new Bishop{ 2, 0, "BLACK", board.squareWidth, board.squareHeight };
//	board.squares[5]->piece = new Bishop{ 5, 0, "BLACK", board.squareWidth, board.squareHeight };
//	board.squares[2 + 7*8]->piece = new Bishop{2, 7, "WHITE", board.squareWidth, board.squareHeight};
//	board.squares[5 + 7*8]->piece = new Bishop{5, 7, "WHITE", board.squareWidth, board.squareHeight};
//
//	//Initialize Queens
//	board.squares[3]->piece = new Queen{ 3, 0, "BLACK", board.squareWidth, board.squareHeight };
//	board.squares[3 + 7 * 8]->piece = new Queen{ 3, 7, "WHITE", board.squareWidth, board.squareHeight };
//
//	//Initialize Knights
//	board.squares[1]->piece = new Knight{ 1, 0, "BLACK", board.squareWidth, board.squareHeight };
//	board.squares[6]->piece = new Knight{ 6, 0, "BLACK", board.squareWidth, board.squareHeight };
//	board.squares[1 + 7 * 8]->piece = new Knight{ 1, 7, "WHITE", board.squareWidth, board.squareHeight };
//	board.squares[6 + 7 * 8]->piece = new Knight{ 6, 7, "WHITE", board.squareWidth, board.squareHeight };
}

void Game::HandleSound(bool exchange, Piece* king, bool kingHasMoved)
{
	if (exchange)
	{
		if (king->isInCheck)
			PlaySound(checkSound);
		else
			PlaySound(captureSound);
	}
	else
	{
		if (activePiece->GetType() == "KING" && (activePiece->posX == 2 || activePiece->posX == 6) && !kingHasMoved)
			PlaySound(castleSound);

		else if (king->isInCheck)
			PlaySound(checkSound);

		else
			PlaySound(moveSound);
	}
}

void Game::Init(int width, int height, const char* title, int fps)
{
	InitWindow(width, height, title);

	SetTargetFPS(fps);

	_turn = "WHITE";

	board = Board{ GetRenderWidth() /8, GetRenderHeight() /8};

	InitAudioDevice();

	captureSound = LoadSound("Assets/capture.mp3");
	moveSound = LoadSound("Assets/move-self.mp3");
	castleSound = LoadSound("Assets/castle.mp3");
	checkSound = LoadSound("Assets/move-check.mp3");

	InitPieces();

	for (auto& square : board.squares)
	{
		if (square->piece)
			square->piece->CalculatePossibleMoves(board.squares, true);
	}

	activePiece == nullptr;
}

void Game::HandleEvents()
{
	for (auto& square : board.squares)
	{
		if (square->piece != nullptr)
		{
			if(square->piece->validMoves.empty())
				square->piece->CalculatePossibleMoves(board.squares, true); //Calculate all moves if the valid moves have been emptied

			if (!activePiece) //We clicked on a piece
			{
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), square->piece->texturePosition) && square->piece->colour == _turn)
				{
					activePiece = square->piece;
					//activePiece->CalculatePossibleMoves(board.squares, true);
					activePiece->ShowPossibleMoves(board.squares);
					break;
				}
			}

			else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), square->piece->texturePosition)) // we clicked on another piece while a piece is active
			{
				activePiece->HidePossibleMoves(board.squares); 
				activePiece = nullptr;
			}

			else if (square->piece->IsHeld() && square->piece->colour == _turn && GetMouseX() < GetRenderWidth() && GetMouseY() < GetRenderHeight() && GetMouseX() > 0 && GetMouseY() > 0) //We're holding the active piece
			{
				activePiece->texturePosition.x = (GetMouseX() - board.squareWidth / 2);
				activePiece->texturePosition.y = (GetMouseY() - board.squareWidth / 2);
			}

			else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), activePiece->texturePosition)) // we clicked on the active piece
			{
				activePiece->HidePossibleMoves(board.squares);
				activePiece = nullptr;
				break;
			}
		}


		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && activePiece) //We have either dropped the piece at the move or clicked on the move
		{
			Square* move = board.GetSquare(GetMouseX(), GetMouseY());
			Piece* king = activePiece->GetKing(board.squares, nullptr)->piece;
			Piece* otherKing = activePiece->GetKing(board.squares, activePiece->colour == "WHITE" ? "BLACK" : "WHITE")->piece;

			if (std::find(activePiece->validMoves.begin(), activePiece->validMoves.end(), move) != activePiece->validMoves.end())
			{
				bool exchange = move->piece;
				bool kingHasMoved = false;

				if (activePiece->name == "KING")
					kingHasMoved = static_cast<King*>(activePiece)->hasMoved;
					

				activePiece->Move(move, board.squares);

				for (auto& square : board.squares)
				{
					if (square->piece != nullptr)
					{
						square->piece->validMoves.clear();
						square->piece->CalculatePossibleMoves(board.squares, true);
					}
				}

				otherKing->SetCheck(move, board.squares);
				king->SetCheck(move, board.squares);

				HandleSound(exchange, otherKing, kingHasMoved);

				activePiece = nullptr;
				_turn = _turn == "WHITE" ? "BLACK" : "WHITE";
			}

			else
			{
				activePiece->texturePosition.x = activePiece->posX * board.squareWidth;
				activePiece->texturePosition.y = activePiece->posY * board.squareHeight;
			}
		}
	}
}

void Game::Render()
{
	BeginDrawing();

	ClearBackground(BLACK);

	board.DrawBoard();

	for (auto& square : board.squares)
	{
		if (square->piece != nullptr)
		{
			square->piece->Draw(square->piece->texturePosition.x, square->piece->texturePosition.y, board.squareWidth, board.squareHeight, board.piecesTextureSheet);
			//Draw hitbox
			//DrawRectangle(square->piece->texturePosition.x, square->piece->texturePosition.y, 80, 80, BLUE);
		}
	}

	//Draw active piece last.
	if(activePiece)
		activePiece->Draw(activePiece->texturePosition.x, activePiece->texturePosition.y, board.squareWidth, board.squareHeight, board.piecesTextureSheet);

	EndDrawing();
}

void Game::Clean()
{
	CloseWindow();
}


void Game::Run(int width, int height, const char* title, int fps)
{
	Init(width, height, title, fps);

	while (!WindowShouldClose())
	{
		HandleEvents();
		Render();
	}

	this->Clean();
}