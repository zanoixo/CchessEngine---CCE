#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define BOARD_SIZE 64

enum Piece
{
    pawn = 1,
    knight = 2,
    bishop = 3,
    rook = 4,
    queen = 5,
    king = 6
};

enum color
{
    white = 0,
    black = 1
};

void showBitBoard(uint64_t bitBoard);
void sendError(char errorMsg[]);
uint64_t getTimeMs();
