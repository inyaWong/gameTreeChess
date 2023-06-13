
#ifndef GAMEBOARD_H_INCLUDED
#define GAMEBOARD_H_INCLUDED

#pragma once
#include <vector>
#include <tuple>


enum class Player {BLACK, WHITE};  // ���� Player ö������
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
    double miniMax(int depth, double alpha, double beta, bool maximizingPlayer);
    void printBoard();
    bool isGameOver() const;
    double evaluate() const;
    static constexpr int MAX_SEARCH_DEPTH = 4; // ����������
    void undoMove(int row, int col);
    char opposite(char player);
    std::vector<std::tuple<int, int, Player>> getValidMoves(Player player) const;
    bool makeMove(int row, int col);


    char board[BOARD_SIZE][BOARD_SIZE];
    int mBoard[BOARD_SIZE][BOARD_SIZE]; // ��������
    int bestMoveX;
    int bestMoveY;
    int mNextMove; // ��һ�����ӷ�����ɫ
    char mHuman, mComputer; // ������Һͼ�������
    int mDepth; // �������
    std::pair<int, int> mLastMove;
    bool mIsBlackTurn;


};

#endif // GAMEBOARD_H_INCLUDED
