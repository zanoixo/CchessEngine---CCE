#ifndef CHESS_EVAL_H


#define MAX_INT 1000000000
#define MIN_INT -1000000000
#define BLACK_MATED 1000000
#define WHITE_MATED -1000000 

#define PAWN_VALUE   100
#define KNIGHT_VALUE 330
#define BISHOP_VALUE 320
#define ROOK_VALUE   500
#define QUEEN_VALUE  900
#define INNER_CENTER_VALUE 20
#define OUTER_CENTER_VALUE 10

typedef struct MoveScore
{
    int score;
    Move move;
}MoveScore;


MoveScore evaluate(ChessBoard *chessBoard, AttackTables *attackTables);
MoveScore whiteMove(ChessBoard *chessBoard, AttackTables *attackTables, int depth, int alpha, int beta);
MoveScore blackMove(ChessBoard *chessBoard, AttackTables *attackTables, int depth, int alpha, int beta);

#endif