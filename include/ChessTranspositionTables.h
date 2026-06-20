#pragma once

#include <stdint.h>
#include "ChessUtils.h"
#include "ChessEval.h"

#define PIECE_COUNT 12
#define CASTLE_RIGHT_COUNT 4
#define ENPASSANT_FILES_COUNT 8
#define TRANSPOSITION_TABLE_NUM_OF_BITS 25

enum pieceHashes
{
    whitePawnHash = 0,
    whiteKnightHash = 1,
    whiteBishopHash = 2,
    whiteRookHash = 3,
    whiteQueenHash = 4,
    whiteKingHash = 5,

    blackPawnHash = 6,
    blackKnightHash = 7,
    blackBishopHash = 8,
    blackRookHash = 9,
    blackQueenHash = 10,
    blackKingHash = 11,  
};

enum castellingHashes
{
    whiteShortCastleHash = 0,
    whiteLongCastleHash = 1,
    blackShortCastleHash = 2,
    blackLongCastleHash = 3
};

typedef struct TranspositionTableHashes
{
    uint64_t colorHash;
    uint64_t pieceHashes[PIECE_COUNT][BOARD_SIZE];
    uint64_t castellingHashes[CASTLE_RIGHT_COUNT];
    uint64_t enPassantHashes[ENPASSANT_FILES_COUNT];
}TranspositionTableHashes;

typedef struct TranspositionTableEntry
{
    uint64_t hash;
    uint8_t depth;
    MoveScore move;
    
}TranspositionTableEntry;

TranspositionTableHashes* initTranpositionTableHashes();