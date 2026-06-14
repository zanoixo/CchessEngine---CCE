#pragma once

#include "ChessMoveGenerator.h"

#define KILLER_MOVE_DEPTH 128
#define TIME_CHECK 2047

#define MAX_INT 1000000000
#define MIN_INT -1000000000
#define BLACK_MATED 1000000
#define WHITE_MATED -1000000 

#define PAWN_VALUE   100
#define KNIGHT_VALUE 330
#define BISHOP_VALUE 320
#define ROOK_VALUE   500
#define QUEEN_VALUE  900
#define KING_VALUE  2000
#define QUEEN_PROMOTION_VALUE 500000
#define ROOK_PROMOTION_VALUE 400000
#define KNIGHT_PROMOTION_VALUE 300000
#define BISHOP_PROMOTION_VALUE 200000
#define INNER_CENTER_VALUE 20
#define OUTER_CENTER_VALUE 10
#define KNIGHT_MOBILITY_VALUE 2
#define BISHOP_MOBILITY_VALUE 2
#define ROOK_MOBILITY_VALUE 2
#define QUEEN_MOBILITY_VALUE 1


typedef struct MoveScore
{
    int score;
    Move move;
}MoveScore;


MoveScore evaluate(ChessBoard *chessBoard, AttackTables *attackTables, uint64_t timePerMove);
MoveScore whiteMove(ChessBoard *chessBoard, AttackTables *attackTables, int depth, int alpha, int beta);
MoveScore blackMove(ChessBoard *chessBoard, AttackTables *attackTables, int depth, int alpha, int beta);
int qsearchWhite(ChessBoard *chessBoard, AttackTables *attackTables, int alpha, int beta);
int qsearchBlack(ChessBoard *chessBoard, AttackTables *attackTables, int alpha, int beta);
