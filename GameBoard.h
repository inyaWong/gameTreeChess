
#ifndef GAMEBOARD_H_INCLUDED
#define GAMEBOARD_H_INCLUDED

#pragma once
#include <vector>

class GameBoard
{
public:
    static const int BOARD_SIZE = 15;
    static const char PLAYER = 'X';
    static const char AI = 'O';
    static const char EMPTY = '.';
    static const int SCORE_MAX = 99999999;
    static const int SCORE_MIN = -99999999;

    GameBoard();

    void initBoard();
    bool isLegalMove(int x, int y);
    void playerMove(int x, int y);
    bool checkWin(int x, int y, char player);
    void aiMove(int &x, int &y);
    int evaluate(char player);
    void findBestMove(int &x, int &y);
    int alphaBetaSearch(int depth, int alpha, int beta);
    void printBoard();

private:
    char board[BOARD_SIZE][BOARD_SIZE];
    int mBoard[BOARD_SIZE][BOARD_SIZE]; // 棋盘数组
    int bestMoveX;
    int bestMoveY;
    int mNextMove; // 下一个落子方的颜色
};

#endif // GAMEBOARD_H_INCLUDED
