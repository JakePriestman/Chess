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
	board.squares[2]->piece = new Bishop{ 2, 0, "BLACK", board.squareWidth, board.squareHeight };
	board.squares[5]->piece = new Bishop{ 5, 0, "BLACK", board.squareWidth, board.squareHeight };
	board.squares[2 + 7*8]->piece = new Bishop{2, 7, "WHITE", board.squareWidth, board.squareHeight};
	board.squares[5 + 7*8]->piece = new Bishop{5, 7, "WHITE", board.squareWidth, board.squareHeight};

	//Initialize Queens
	board.squares[3]->piece = new Queen{ 3, 0, "BLACK", board.squareWidth, board.squareHeight };
	board.squares[3 + 7 * 8]->piece = new Queen{ 3, 7, "WHITE", board.squareWidth, board.squareHeight };

	//Initialize Knights
	board.squares[1]->piece = new Knight{ 1, 0, "BLACK", board.squareWidth, board.squareHeight };
	board.squares[6]->piece = new Knight{ 6, 0, "BLACK", board.squareWidth, board.squareHeight };
	board.squares[1 + 7 * 8]->piece = new Knight{ 1, 7, "WHITE", board.squareWidth, board.squareHeight };
	board.squares[6 + 7 * 8]->piece = new Knight{ 6, 7, "WHITE", board.squareWidth, board.squareHeight };

}

void Game::HandleSound(bool exchange, Piece* king, bool kingHasMoved)
{
	if (_checkmate)
	{
		PlaySound(checkmateSound);
		PlaySound(checkSound);
	}

	else if (activePiece->name == "PAWN" && activePiece->posY == 0 || activePiece->posY == 7)
	{
		PlaySound(promoteSound);

		if(king->isInCheck)
			PlaySound(checkSound);
		if (exchange)
			PlaySound(captureSound);
	}

	else if (exchange)
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
	_checkmate = false;

	board = Board{ GetRenderWidth() /8, GetRenderHeight() /8};

	InitAudioDevice();

	captureSound = LoadSound("Assets/capture.mp3");
	moveSound = LoadSound("Assets/move-self.mp3");
	castleSound = LoadSound("Assets/castle.mp3");
	checkSound = LoadSound("Assets/move-check.mp3");
	checkmateSound = LoadSound("Assets/game-end.mp3");
	promoteSound = LoadSound("Assets/promote.mp3");
	gameStartSound = LoadSound("Assets/game-start.mp3");

	InitPieces();

	for (auto& square : board.squares)
	{
		if (square->piece)
			square->piece->CalculatePossibleMoves(board.squares, true);
	}

	activePiece == nullptr;

	PlaySound(gameStartSound);
}

bool Game::MoveResolvesCheck(Piece* activePiece, Board board, Square* move, Piece* king)
{
	int x = activePiece->posX;
	int y = activePiece->posY;
	Piece* piece = nullptr;

	if (move->piece)
		piece = move->piece;

	move->piece = activePiece;
	activePiece->posX = move->x;
	activePiece->posY = move->y;
	board.squares[x + y * 8]->piece = nullptr;

	for (auto& square : board.squares)
	{
		if (square->piece != nullptr)
		{
			square->piece->validMoves.clear();
			square->piece->CalculatePossibleMoves(board.squares, true);
		}
	}

	king->SetCheck(board.squares);

	move->piece = piece;
	activePiece->posX = x;
	activePiece->posY = y;
	board.squares[x + y * 8]->piece = activePiece;

	for (auto& square : board.squares)
	{
		if (square->piece != nullptr)
		{
			square->piece->validMoves.clear();
			square->piece->CalculatePossibleMoves(board.squares, true);
		}
	}

	if (king->isInCheck)
		return false;

	return true;
}

void Game::HandleEvents()
{
	for (auto& square : board.squares)
	{
		if (square->piece != nullptr)
		{
			if (square->piece->validMoves.empty())
				square->piece->CalculatePossibleMoves(board.squares, true); //Calculate all moves if the valid moves have been emptied

			if (!activePiece) //We clicked on a piece
			{
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), square->piece->texturePosition) && square->piece->colour == _turn)
				{
					activePiece = square->piece;
					activePiece->ShowPossibleMoves(board.squares);
					break;
				}
			}

			else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), square->piece->texturePosition) && square->piece->colour == activePiece->colour) // we clicked on another piece while a piece is active
			{
				activePiece->HidePossibleMoves(board.squares);
				activePiece = square->piece;
				activePiece->ShowPossibleMoves(board.squares);
				break;
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
			Piece* otherKing = Piece::GetKing(board.squares, activePiece->colour == "WHITE" ? "BLACK" : "WHITE")->piece;
			Piece* king = Piece::GetKing(board.squares, activePiece->colour)->piece;

			if (std::find(activePiece->validMoves.begin(), activePiece->validMoves.end(), move) != activePiece->validMoves.end())
			{
				bool exchange = move->piece;
				bool hasMoved = false;
				bool kingHasMoved = false;

				if (activePiece->name == "KING")
					kingHasMoved = static_cast<King*>(activePiece)->hasMoved; //just for the sound, can this be improved?


				bool resolvedCheck = MoveResolvesCheck(activePiece, board, move, king);

				if (resolvedCheck)
					hasMoved = activePiece->Move(move, board.squares);

				if (hasMoved)
				{
					for (auto& square : board.squares)
					{
						if (square->piece != nullptr)
						{
							square->piece->validMoves.clear();
							square->piece->CalculatePossibleMoves(board.squares, true);
						}
					}

					otherKing->SetCheck(board.squares);
					king->SetCheck(board.squares);

					if (otherKing->isInCheck) //HERE WE CHECK IF THERE ARE ANY MORE VALID MOVES AND IF NOT THEN WE HAVE CHECKMATE.
					{
						for (auto& square : board.squares)
						{
							if (square->piece && square->piece->colour == otherKing->colour)
							{
								for (int i = 0; i < square->piece->validMoves.size(); i++)
								{
									bool resolvedCheck = MoveResolvesCheck(square->piece, board, square->piece->validMoves[i], otherKing);

									if (resolvedCheck)
									{
										otherKing->SetCheck(board.squares);
										HandleSound(exchange, otherKing, kingHasMoved);

										activePiece = nullptr;
										_turn = _turn == "WHITE" ? "BLACK" : "WHITE";
										return;
									}
									else
										continue;
								}
							}
						}

						//CHECKMATE
						_checkmate = true;
						HandleSound(exchange, otherKing, kingHasMoved);
						activePiece = nullptr;
					}
					
					else
					{
						HandleSound(exchange, otherKing, kingHasMoved);

						activePiece = nullptr;
						_turn = _turn == "WHITE" ? "BLACK" : "WHITE";
					}
				}
				else
				{
					activePiece->texturePosition.x = activePiece->posX * board.squareWidth;
					activePiece->texturePosition.y = activePiece->posY * board.squareHeight;
				}
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

	if (_checkmate)
	{
		DrawRectangle(60, 60, GetRenderWidth() - 120, GetRenderHeight() - 120, {0, 0, 0, 200});
		DrawText(_turn == "WHITE" ? "WHITE WINS" : "BLACK WINS", GetRenderWidth() / 2 - 150, GetRenderHeight() / 2 - 48, 48, WHITE);
	}

	EndDrawing();
}

void Game::Clean()
{
	UnloadSound(captureSound);
	UnloadSound(castleSound);
	UnloadSound(checkmateSound);
	UnloadSound(moveSound);
	UnloadSound(gameStartSound);
	UnloadSound(promoteSound);
	UnloadFont(font);
	CloseWindow();
}

void Game::Run(int width, int height, const char* title, int fps)
{
	Init(width, height, title, fps);

	while (!WindowShouldClose())
	{
		if(!_checkmate)
			HandleEvents();
		Render();
	}

	this->Clean();
}