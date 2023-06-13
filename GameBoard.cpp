#include "GameBoard.h"
#include "GameController.h"
#include <iostream>
#include <cfloat>

using namespace std;
const int INF = 1e9;

char GameBoard::getPieceAt(int row, int col) const {
    return mBoard[row][col];
}

GameBoard::GameBoard()
{
    initBoard();
}

void GameBoard::initBoard()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = EMPTY;
        }
    }
}

bool GameBoard::isLegalMove(int x, int y)
{
    return (x >= 0 && x <= BOARD_SIZE - 1 && y >= 0 && y <= BOARD_SIZE - 1 && board[x][y] == EMPTY);
}

void GameBoard::playerMove(int x, int y)
{
    board[x][y] = PLAYER;
}

bool GameBoard::checkWin(int x, int y, char player)
{
    int count = 0;

    // check row
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[x][i] == player)
        {
            count++;
            if (count == 5)
            {
                return true;
            }
        }
        else
        {
            count = 0;
        }
    }

    // check column
    count = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][y] == player)
        {
            count++;
            if (count == 5)
            {
                return true;
            }
        }
        else
        {
            count = 0;
        }
    }

    // check diagonal
    count = 0;
    for (int i = -4; i <= 4; i++)
    {
        if (x + i >= 0 && x + i <= BOARD_SIZE - 1 && y + i >= 0 && y + i <= BOARD_SIZE - 1 && board[x + i][y + i] == player)
        {
            count++;
            if (count == 5)
            {
                return true;
            }
        }
        else
        {
            count = 0;
        }
    }

    // check anti-diagonal
    count = 0;
    for (int i = -4; i <= 4; i++)
    {
        if (x + i >= 0 && x + i <= BOARD_SIZE - 1 && y - i >= 0 && y - i <= BOARD_SIZE - 1 && board[x + i][y - i] == player)
        {
            count++;
            if (count == 5)
            {
                return true;
            }
        }
        else
        {
            count = 0;
        }
    }

    return false;
}

void GameBoard::aiMove(int &x, int &y)
{
    alphaBetaSearch(4, SCORE_MIN, SCORE_MAX);
    x = bestMoveX;
    y = bestMoveY;
    board[x][y] = AI;
}

int GameBoard::evaluate(char player)
{
    int score = 0;

    char opponent = (player == PLAYER) ? AI : PLAYER;

    // check row
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        int countPlayer = 0;
        int countOpponent = 0;
        for (int j = 0; j < 5; j++)
        {
            if (i + j <= BOARD_SIZE - 1)
            {
                if (board[i + j][bestMoveY] == player)
                {
                    countPlayer++;
                }
                else if (board[i + j][bestMoveY] == opponent)
                {
                    countOpponent++;
                }
            }
        }

        if (countPlayer == 5)
        {
            return SCORE_MAX;
        }
        else if (countOpponent == 5)
        {
            return SCORE_MIN;
        }
        else if (countPlayer == 4 && countOpponent == 0)
        {
            score += 10000;
        }
        else if (countPlayer == 3 && countOpponent == 0)
        {
            score += 1000;
        }
        else if (countPlayer == 2 && countOpponent == 0)
        {
            score += 100;
        }
        else if (countPlayer == 1 && countOpponent == 0)
        {
            score += 10;
        }
        else if (countPlayer == 0 && countOpponent == 0)
        {
            score += 1;
        }
        else if (countOpponent == 4 && countPlayer == 0)
        {
            score -= 10000;
        }
        else if (countOpponent == 3 && countPlayer == 0)
        {
            score -= 1000;
        }
        else if (countOpponent == 2 && countPlayer == 0)
        {
            score -= 100;
        }
        else if (countOpponent == 1 && countPlayer == 0)
        {
            score -= 10;
        }
        else if (countOpponent == 0 && countPlayer == 0)
        {
            score -= 1;
        }
    }

    // check column
    for (int j = 0; j < BOARD_SIZE; j++)
    {
        int countPlayer = 0;
        int countOpponent = 0;
        for (int i = 0; i < 5; i++)
        {
            if (j + i <= BOARD_SIZE - 1)
            {
                if (board[bestMoveX][j + i] == player)
                {
                    countPlayer++;
                }
                else if (board[bestMoveX][j + i] == opponent)
                {
                    countOpponent++;
                }
            }
        }

        if (countPlayer == 5)
        {
            return SCORE_MAX;
        }
        else if (countOpponent == 5)
        {
            return SCORE_MIN;
        }
        else if (countPlayer == 4 && countOpponent == 0)
        {
            score += 10000;
        }
        else if (countPlayer == 3 && countOpponent == 0)
        {
            score += 1000;
        }
        else if (countPlayer == 2 && countOpponent == 0)
        {
            score += 100;
        }
        else if (countPlayer == 1 && countOpponent == 0)
        {
            score += 10;
        }
        else if (countPlayer == 0 && countOpponent == 0)
        {
            score += 1;
        }
        else if (countOpponent == 4 && countPlayer == 0)
        {
            score -= 10000;
        }
        else if (countOpponent == 3 && countPlayer == 0)
        {
            score -= 1000;
        }
        else if (countOpponent == 2 && countPlayer == 0)
        {
            score -= 100;
        }
        else if (countOpponent == 1 && countPlayer == 0)
        {
            score -= 10;
        }
        else if (countOpponent == 0 && countPlayer == 0)
        {
            score -= 1;
        }
    }

    // check diagonal
    for (int k = -BOARD_SIZE + 1; k < BOARD_SIZE; k++)
    {
        int countPlayer = 0;
        int countOpponent = 0;
        for (int i = 0; i < 5; i++)
        {
            if (bestMoveX + i >= 0 && bestMoveX + i <= BOARD_SIZE - 1 && bestMoveY - i + k >= 0 && bestMoveY - i + k <= BOARD_SIZE - 1)
            {
                if (board[bestMoveX + i][bestMoveY - i + k] == player)
                {
                    countPlayer++;
                }
                else if (board[bestMoveX + i][bestMoveY - i + k] == opponent)
                {
                    countOpponent++;
                }
            }
        }

        if (countPlayer == 5)
        {
            return SCORE_MAX;
        }
        else if (countOpponent == 5)
        {
            return SCORE_MIN;
        }
        else if (countPlayer == 4 && countOpponent == 0)
        {
            score += 10000;
        }
        else if (countPlayer == 3 && countOpponent == 0)
        {
            score += 1000;
        }
        else if (countPlayer == 2 && countOpponent == 0)
        {
            score += 100;
        }
        else if (countPlayer == 1 && countOpponent == 0)
        {
            score += 10;
        }
        else if (countPlayer == 0 && countOpponent == 0)
        {
            score += 1;
        }
        else if (countOpponent == 4 && countPlayer == 0)
        {
            score -= 10000;
        }
        else if (countOpponent == 3 && countPlayer == 0)
        {
            score -= 1000;
        }
        else if (countOpponent == 2 && countPlayer == 0)
        {
            score -= 100;
        }
        else if (countOpponent == 1 && countPlayer == 0)
        {
            score -= 10;
        }
        else if (countOpponent == 0 && countPlayer == 0)
        {
            score -= 1;
        }
    }

    // check anti-diagonal
    for (int k = 0; k < 2 * BOARD_SIZE - 1; k++)
    {
        int countPlayer = 0;
        int countOpponent = 0;
        for (int i = 0; i < 5; i++)
        {
            if (bestMoveX - i >= 0 && bestMoveX - i <= BOARD_SIZE - 1 && bestMoveY - i + k - 4 >= 0 && bestMoveY - i + k - 4 <= BOARD_SIZE - 1)
            {
                if (board[bestMoveX - i][bestMoveY - i + k - 4] == player)
                {
                    countPlayer++;
                }
                else if (board[bestMoveX - i][bestMoveY - i + k - 4] == opponent)
                {
                    countOpponent++;
                }
            }
        }

        if (countPlayer == 5)
        {
            return SCORE_MAX;
        }
        else if (countOpponent == 5)
        {
            return SCORE_MIN;
        }
        else if (countPlayer == 4 && countOpponent == 0)
        {
            score += 10000;
        }
        else if (countPlayer == 3 && countOpponent == 0)
        {
            score += 1000;
        }
        else if (countPlayer == 2 && countOpponent == 0)
        {
            score += 100;
        }
        else if (countPlayer == 1 && countOpponent == 0)
        {
            score += 10;
        }
        else if (countPlayer == 0 && countOpponent == 0)
        {
            score += 1;
        }
        else if (countOpponent == 4 && countPlayer == 0)
        {
            score -= 10000;
        }
        else if (countOpponent == 3 && countPlayer == 0)
        {
            score -= 1000;
        }
        else if (countOpponent == 2 && countPlayer == 0)
        {
            score -= 100;
        }
        else if (countOpponent == 1 && countPlayer == 0)
        {
            score -= 10;
        }
        else if (countOpponent == 0 && countPlayer == 0)
        {
            score -= 1;
        }
    }

    return score;
}

void GameBoard::findBestMove(int& x, int& y)
{
    int score = -INF;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (GameBoard::mBoard[i][j] == EMPTY) {
                GameBoard::mBoard[i][j] = mNextMove;
                int moveScore = miniMax(0, false, -INF, INF);
                GameBoard::mBoard[i][j] = EMPTY;
                if (moveScore > score) {
                    score = moveScore;
                    x = i;
                    y = j;
                }
            }
        }
    }
}

double GameBoard::miniMax(int depth, double alpha, double beta, bool maximizingPlayer)
{
    if(depth == 0 || isGameOver()) {
        return evaluate() * (maximizingPlayer ? 1 : -1);
    }

    double bestValue;
    if(maximizingPlayer) {
        bestValue = -DBL_MAX;
        for(auto move : getValidMoves(mNextMove)) {
            makeMove(move, mNextMove);
            double value = miniMax(depth - 1, alpha, beta, false);
            undoMove(move);
            bestValue = max(bestValue, value);
            alpha = max(alpha, bestValue);
            if(beta <= alpha) {
                break;
            }
        }
    } else {
        bestValue = DBL_MAX;
        for(auto move : getValidMoves(opposite(mNextMove))) {
            makeMove(move, opposite(mNextMove));
            double value = miniMax(depth - 1, alpha, beta, true);
            undoMove(move);
            bestValue = min(bestValue, value);
            beta = min(beta, bestValue);
            if(beta <= alpha) {
                break;
            }
        }
    }
    return bestValue;
}

int GameBoard::alphaBetaSearch(int depth, int alpha, int beta)
{
    if (depth == 0)
    {
        return evaluate(AI);
    }

    vector<pair<int, int>> moves;
    int score;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (isLegalMove(i, j))
            {
                moves.push_back(make_pair(i, j));
            }
        }
    }

    bool isMaxNode = (moves.size() % 2 == 0);

    if (isMaxNode)
    {
        score = SCORE_MIN;
        for (int i = 0; i < moves.size(); i++)
        {
            int x = moves[i].first;
            int y = moves[i].second;
            board[x][y] = AI;
            int childScore = alphaBetaSearch(depth - 1, alpha, beta);
            if (childScore > score)
            {
                score = childScore;
                if (depth == 4)
                {
                    bestMoveX = x;
                    bestMoveY = y;
                }
            }
            board[x][y] = EMPTY;
            alpha = max(alpha, score);
            if (beta <= alpha)
            {
                break;
            }
        }
    }
    else
    {
        score = SCORE_MAX;
        for (int i = 0; i < moves.size(); i++)
        {
            int x = moves[i].first;
            int y = moves[i].second;
            board[x][y] = PLAYER;
            int childScore = alphaBetaSearch(depth - 1, alpha, beta);
            if (childScore < score)
            {
                score = childScore;
            }
            board[x][y] = EMPTY;
            beta = min(beta, score);
            if (beta <= alpha)
            {
                break;
            }
        }
    }

    return score;
}

void GameBoard::printBoard()
{
    for(int row = 0; row < NUM_ROWS; ++row) {
    for(int col = 0; col < NUM_COLUMNS; ++col) {
        cout << mBoard.getPieceAt(row, col) << " ";
    }
    cout << endl;
}
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool GameBoard::isGameOver() const
{
    // 如果下一步落子的玩家没有可以落子的位置，或者双方棋子数量不足，
    // 或者搜索深度已经达到了最大值，就认为游戏已经结束
    return getValidMoves(mNextMove).empty()
           || mComputer.getPiecesCount() <= 2
           || mHuman.getPiecesCount() <= 2
           || mDepth >= MAX_SEARCH_DEPTH;
}

double GameBoard::evaluate() const
{
    double score = 0;

    // 当前玩家的棋子数
    int playerCount = (mNextMove == BLACK) ? mComputer.getPiecesCount() : mHuman.getPiecesCount();
    int opponentCount = (mNextMove == BLACK) ? mHuman.getPiecesCount() : mComputer.getPiecesCount();

    // 棋子的数量对分数的贡献
    score += (playerCount - opponentCount) * 10;

    // 遍历棋盘上的所有位置，计算棋子的位置得分
    for(int i=0; i<NUM_ROWS; i++) {
        for(int j=0; j<NUM_COLUMNS; j++) {
            if(mBoard[i][j] == EMPTY) {
                continue;
            }
            double squareScore = (mBoard[i][j] == mNextMove) ? 1 : -1; // 根据棋子颜色设置得分
            if(mBoard[i][j] == BLACK) {
                if(i == 0 || i == NUM_ROWS - 1) {
                    squareScore += 0.5;
                }
                if(j == 0 || j == NUM_COLUMNS - 1) {
                    squareScore += 0.5;
                }
            } else {
                if(i == 0 || i == NUM_ROWS - 1) {
                    squareScore -= 0.5;
                }
                if(j == 0 || j == NUM_COLUMNS - 1) {
                    squareScore -= 0.5;
                }
            }
            score += squareScore;
        }
    }

    return score;
}

double GameBoard::evaluate() const
{
    double score = 0;

    // 当前玩家的棋子数
    int playerCount = (mNextMove == BLACK) ? mComputer.getPiecesCount() : mHuman.getPiecesCount();
    int opponentCount = (mNextMove == BLACK) ? mHuman.getPiecesCount() : mComputer.getPiecesCount();

    // 棋子的数量对分数的贡献
    score += (playerCount - opponentCount) * 10;

    // 遍历棋盘上的所有位置，计算棋子的位置得分
    for(int i=0; i<NUM_ROWS; i++) {
        for(int j=0; j<NUM_COLUMNS; j++) {
            if(mBoard[i][j] == EMPTY) {
                continue;
            }
            double squareScore = (mBoard[i][j] == mNextMove) ? 1 : -1; // 根据棋子颜色设置得分
            if(mBoard[i][j] == BLACK) {
                if(i == 0 || i == NUM_ROWS - 1) {
                    squareScore += 0.5;
                }
                if(j == 0 || j == NUM_COLUMNS - 1) {
                    squareScore += 0.5;
                }
            } else {
                if(i == 0 || i == NUM_ROWS - 1) {
                    squareScore -= 0.5;
                }
                if(j == 0 || j == NUM_COLUMNS - 1) {
                    squareScore -= 0.5;
                }
            }
            score += squareScore;
        }
    }

    return score;
}
