#ifndef CHESS_BOARD_H

#include <stdint.h>
#include <stdlib.h>

#define BOARD_SIZE 64

typedef struct ChessBoard
{
    uint64_t whitePawns;
    uint64_t whiteKnights;
    uint64_t whiteBishops;
    uint64_t whiteRooks;
    uint64_t whiteQueens;
    uint64_t whiteKing;

    uint64_t blackPawns;
    uint64_t blackKnights;
    uint64_t blackBishops;
    uint64_t blackRooks;
    uint64_t blackQueens;
    uint64_t blackKing;
    
    uint64_t blackPieces;
    uint64_t whitePieces;
    uint64_t allPieces;
    uint64_t enPassantSq;
    uint8_t flags;
}ChessBoard;

enum boardFlags
{
    colorMask = 0b00000001,
    whiteShortCastleMask = 0b00000010,
    whiteLongCastleMask = 0b00000100,
    blackShortCastleMask = 0b00001000,
    blackLongCastleMask = 0b00010000
};

void showPosition(const ChessBoard* chessBoard);
ChessBoard* initChessBoard();
void createPosition(char fileName[], ChessBoard *chessBoard);


#endif