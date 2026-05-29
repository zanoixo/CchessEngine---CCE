#ifndef CHESS_BOARD_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

enum Piece
{
    pawn = 1,
    knight = 2,
    bishop = 3,
    rook = 4,
    queen = 5,
    king = 6
};

void showBitBoard(uint64_t bitBoard);
void sendError(char errorMsg[]);

#endif