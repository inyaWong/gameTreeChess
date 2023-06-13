#include "GameBoard.h"
#ifndef GAMECONTROLLER_H_INCLUDED
#define GAMECONTROLLER_H_INCLUDED

#pragma once


class GameController
{
public:
    GameController();
    void startGame();

private:
    static const int PLAYER_TURN = 0;
    static const int AI_TURN = 1;
    GameBoard board;
    void playerTurn();
    void aiTurn();
    int turn;
};

#endif // GAMECONTROLLER_H_INCLUDED
