#include "GameController.h"
#include "GameBoard.h"
#include <iostream>

using namespace std;



GameController::GameController()
{
    turn = PLAYER_TURN;
}

void GameController::startGame()
{
    board.printBoard();

    while (true)
    {
        if (turn == PLAYER_TURN)
        {
            playerTurn();
        }
        else if (turn == AI_TURN)
        {
            aiTurn();
        }

        board.printBoard();

        if (board.checkWin(board.board[board.bestMoveX][board.bestMoveY] == GameBoard::PLAYER ? board.bestMoveX : -1,
                            board.board[board.bestMoveX][board.bestMoveY] == GameBoard::PLAYER ? board.bestMoveY : -1,
                            board.board[board.bestMoveX][board.bestMoveY]))
        {
            if (turn == PLAYER_TURN)
            {
                cout << "Player wins!" << endl;
            }
            else
            {
                cout << "AI wins!" << endl;
            }
            break;
        }

        if (turn == PLAYER_TURN)
        {
            turn = AI_TURN;
        }
        else
        {
            turn = PLAYER_TURN;
        }

        if (board.bestMoveX == -1 && board.bestMoveY == -1 && board.isLegalMove(7, 7))
        {
            board.playerMove(7, 7);
            board.bestMoveX = 7;
            board.bestMoveY = 7;
            board.printBoard();
        }
    }
}

void GameController::playerTurn()
{
    int x, y;
    cout << "Player's turn (X):" << endl;
    do
    {
        cout << "Input the position (x y): ";
        cin >> x >> y;
    } while (!board.isLegalMove(x, y));
    board.playerMove(x, y);
}

void GameController::aiTurn()
{
    cout << "AI's turn (O):" << endl;
    board.aiMove(board.bestMoveX, board.bestMoveY);
}
