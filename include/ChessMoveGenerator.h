#ifndef CHESS_MOVE_GENERATOR_H

#include "ChessBoard.h"

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
    queenPromotion = 0,
    rookPromotion = 1,
    bishopPromotion = 2,
    knightPromotion = 3,
    numOfPromotionPieces = 4
};

enum CapturedPiece
{
    pawnCaptured = 0,
    knightCaptured = 1,
    bishopCaptured = 2,
    rookCaptured = 3,
    queenCaptured = 4
};

enum MoveFlags
{
    promotionPieceMask = 0b00000011,
    capturePieceMask =   0b00011100
};

enum MoveFlagsPosition
{
    promotionFlagPosition = 0,
    captureFlagPostion = 2
};

typedef struct Move
{
    uint8_t from;
    uint8_t to;
    uint8_t flags;
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

#endif