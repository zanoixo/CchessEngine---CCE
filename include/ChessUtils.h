#ifndef CHESS_BOARD_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

enum Piece
{
    pawn = 0,
    knight = 1,
    bishop = 2,
    rook = 3,
    queen = 4,
    king = 5,

};

void showBitBoard(uint64_t bitBoard);
void sendError(char errorMsg[]);

#endif