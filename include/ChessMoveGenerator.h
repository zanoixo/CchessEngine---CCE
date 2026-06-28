#pragma once

#include "ChessUtils.h"

typedef struct TranspositionTableHashes TranspositionTableHashes;
typedef struct ChessBoard ChessBoard; 

typedef struct MagicTableHash
{
    uint64_t mask;
    uint64_t magicNumber;
    int shift;

}MagicTableHash;

typedef struct BlockerAttackPattern
{
    uint64_t attackPattern;
    uint64_t blockerPattern;
}BlockerAttackPattern;

typedef struct AttackTables
{
    uint64_t whitePanwsAttacks[BOARD_SIZE];
    uint64_t blackPanwsAttacks[BOARD_SIZE];
    uint64_t knightAttacks[BOARD_SIZE];
    uint64_t kingAttacks[BOARD_SIZE];
    uint64_t* rookAttacks[BOARD_SIZE];
    MagicTableHash rookMagicHashTable[BOARD_SIZE];
    uint64_t* bishopAttacks[BOARD_SIZE];
    MagicTableHash bishopMagicHashTable[BOARD_SIZE];
    
}AttackTables;

enum PromotionPieces
{
    queenPromotion = 1,
    rookPromotion = 2,
    bishopPromotion = 3,
    knightPromotion = 4,
    numOfPromotionPieces = 5
};

enum MoveFlags
{
    promotionPieceMask         = 0b00000000000111,
    capturePieceMask           = 0b00000000111000,
    enPassantMask              = 0b00000001000000,
    removeWhiteShortCastleFlag = 0b00000010000000,
    removeWhiteLongCastleFlag  = 0b00000100000000,
    removeBlackShortCastleFlag = 0b00001000000000,
    removeBlackLongCastleFlag  = 0b00010000000000,
    pieceMask                  = 0b11100000000000
};

enum MoveFlagsPosition
{
    promotionFlagPosition = 0,
    captureFlagPostion = 3,
    enPassantFlagPosition = 6,
    removeWhiteShortCastleFlagPosition = 7,
    removeWhiteLongCastleFlagPosition = 8,
    removeBlackShortCastleFlagPosition = 9,
    removeBlackLongCastleFlagPosition = 10,
    pieceFlagPosition = 11
};

typedef struct Move
{
    uint64_t from;
    uint64_t to;
    uint64_t prevEnPassantSq;
    uint16_t flags;
    int score;
}Move;

typedef struct MoveList
{
    Move* moves;
    int nextIndex;
}MoveList;


AttackTables* initAttackTables();
uint64_t getRookAttackPattern(int sqInd, uint64_t position, AttackTables *attackTables);
uint64_t getBishopAttackPattern(int sqInd, uint64_t position, AttackTables *attackTables);
uint64_t getQueenAttackPattern(int sqInd, uint64_t position, AttackTables *attackTables);
void generateMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList);
void generateKnightMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList);
void generateKingMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList);
void generateQueenMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList);
void generateBishopMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList);
void generateRookMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList);
void generatePawnMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList);
void generateCastleMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList);
void makeMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes);
void unMakeMove(ChessBoard *chessBoard, Move *move, TranspositionTableHashes* hashes);
int isSquareAttacked(uint8_t sqInd, ChessBoard *chessBoard, AttackTables *attackTables, int isAttackedByWhite);
uint8_t isBlack(ChessBoard *chessBoard);
uint8_t getSqInd(uint64_t sq);
uint8_t getCapturedPiece(uint16_t flags);
uint8_t getPromotionPiece(uint16_t flags);
uint8_t getPiece(uint16_t flags);
uint8_t getPieceFromSquare(uint64_t sq, uint8_t isBlack, ChessBoard *chessBoard);
