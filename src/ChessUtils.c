#include "ChessUtils.h"

void showBitBoard(uint64_t bitBoard)
{
    for (int rank = 7; rank >= 0; rank--)
    {
        for (int file = 0; file < 8; file++)
        {
            int square = rank * 8 + file;
            uint64_t mask = 1ULL << square;

            printf("%d ", (bitBoard & mask) ? 1 : 0);
        }

        printf("\n");
    }
    printf("\n");
}

void sendError(char errorMsg[]){

    printf("[ERROR]: %s\n", errorMsg);
    exit(1);
}
