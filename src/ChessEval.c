#include "ChessBoard.h"
#include "ChessMoveGenerator.h"
#include "ChessUtils.h"
#include "ChessEval.h"

uint64_t innerCenterEval = 0b00000000ULL << 56 |
                           0b00000000ULL << 48 |
                           0b00000000ULL << 40 |
                           0b00011000ULL << 32 |
                           0b00011000ULL << 24 |
                           0b00000000ULL << 16 |
                           0b00000000ULL << 8  |
                           0b00000000ULL;

uint64_t outerCenterEval = 0b00000000ULL << 56 |
                           0b00000000ULL << 48 |
                           0b00111100ULL << 40 |
                           0b00100100ULL << 32 |
                           0b00100100ULL << 24 |
                           0b00111100ULL << 16 |
                           0b00000000ULL << 8  |
                           0b00000000ULL;

Move killerMoves[MAX_DEPTH + 1][2];
uint64_t LEGAL_MOVES = 84998978956;
uint64_t MOVE_COUNTER = 0;

void initKillerMoves()
{
    for (int i = 0; i < MAX_DEPTH + 1; i++)
    {
        killerMoves[i][0] = (Move){0, 0, 0, 0};
        killerMoves[i][1] = (Move){0, 0, 0, 0};
    }
}

void findKillerMoves(MoveList *moveList, int depth)
{
    for (int i = 0; i < moveList->nextIndex; i++)
    {
        if (moveList->moves[i].from == killerMoves[depth][0].from &&
             moveList->moves[i].to == killerMoves[depth][0].to)
        {
            moveList->moves[i].score = 200;
        }

        if (moveList->moves[i].from == killerMoves[depth][1].from &&
             moveList->moves[i].to == killerMoves[depth][1].to)
        {
            moveList->moves[i].score = 100;
        }
        
    }
    
}

void setKillerMove(Move killerMove, int depth)
{
    if (!getPromotionPiece(killerMove.flags) && !getCapturedPiece(killerMove.flags))
    {
        if (!(killerMoves[depth][0].from == killerMove.from && killerMoves[depth][0].to == killerMove.to) &&
            !(killerMoves[depth][1].from == killerMove.from && killerMoves[depth][1].to == killerMove.to))
        {
            killerMoves[depth][1] = killerMoves[depth][0];
            killerMoves[depth][0] = killerMove;
        } 
    }
}

int countPieces(uint64_t bitboard)
{
    int count = 0;

    while (bitboard)
    {
        count++;
        bitboard &= bitboard - 1;
    }

    return count;
}


int evaluatePosition(ChessBoard *chessBoard)
{
    int score = 0;

    score += countPieces(chessBoard->whitePawns)   * PAWN_VALUE;
    score += countPieces(chessBoard->whiteKnights) * KNIGHT_VALUE;
    score += countPieces(chessBoard->whiteBishops) * BISHOP_VALUE;
    score += countPieces(chessBoard->whiteRooks)   * ROOK_VALUE;
    score += countPieces(chessBoard->whiteQueens)  * QUEEN_VALUE;
    score += countPieces(chessBoard->whitePieces & innerCenterEval) * INNER_CENTER_VALUE;
    score += countPieces(chessBoard->whitePieces & outerCenterEval) * OUTER_CENTER_VALUE;

    score -= countPieces(chessBoard->blackPawns)   * PAWN_VALUE;
    score -= countPieces(chessBoard->blackKnights) * KNIGHT_VALUE;
    score -= countPieces(chessBoard->blackBishops) * BISHOP_VALUE;
    score -= countPieces(chessBoard->blackRooks)   * ROOK_VALUE;
    score -= countPieces(chessBoard->blackQueens)  * QUEEN_VALUE;
    score -= countPieces(chessBoard->blackPieces & innerCenterEval) * INNER_CENTER_VALUE;
    score -= countPieces(chessBoard->blackPieces & outerCenterEval) * OUTER_CENTER_VALUE;

    return score;
}

void setBestMoveFirst(MoveList* moveList, int moveCount)
{
    int moveInd = moveCount;
    for (int i = moveCount + 1; i < moveList->nextIndex; i++)
    {
        if (moveList->moves[i].score > moveList->moves[moveInd].score)
        {
            moveInd = i;
        }
        
    }
    Move tmp = moveList->moves[moveCount];
    moveList->moves[moveCount] = moveList->moves[moveInd];
    moveList->moves[moveInd] = tmp;
}

MoveScore blackMove(ChessBoard *chessBoard, AttackTables *attackTables, int depth, int alpha, int beta)
{
    MoveScore bestMove;
    bestMove.score = MAX_INT;

    MoveList moveList;
    Move moves[256];
    moveList.moves = moves;
    moveList.nextIndex = 0;

    MoveScore moveScore;
    int legalMoves = 0;

    generateMoves(chessBoard, attackTables, &moveList);

    findKillerMoves(&moveList, depth);

    for (int i = 0; i < moveList.nextIndex; i++)
    {
        //MOVE_COUNTER++;
        setBestMoveFirst(&moveList, i);

        makeMove(chessBoard, &moveList.moves[i]);

        if (!isSquareAttacked(getSqInd(chessBoard->blackKing), chessBoard, attackTables, 1))
        {
            legalMoves++;
            if (depth > 0)
            {
                moveScore = whiteMove(chessBoard, attackTables, depth - 1, alpha, beta);

                if (moveScore.score < bestMove.score)
                {
                    bestMove = moveScore;
                    bestMove.move = moveList.moves[i];
                }

                if (moveScore.score < beta)
                {
                    beta = moveScore.score;
                }

                if (alpha >= beta)
                {
                    setKillerMove(moveList.moves[i], depth);
                    unMakeMove(chessBoard, &moveList.moves[i]);
                    break;
                }
            }
        }

        unMakeMove(chessBoard, &moveList.moves[i]);
    }

    if (legalMoves == 0)
    {
        if (isSquareAttacked(getSqInd(chessBoard->blackKing), chessBoard, attackTables, 1))
            bestMove.score = BLACK_MATED + depth;
        else
            bestMove.score = 0;

        return bestMove;
    }

    if (depth == 0)
    {
        bestMove.score = evaluatePosition(chessBoard);
        return bestMove;
    }

    return bestMove;
}

MoveScore whiteMove(ChessBoard *chessBoard, AttackTables *attackTables, int depth, int alpha, int beta)
{
    MoveScore bestMove;
    bestMove.score = MIN_INT - 1;

    MoveList moveList;
    Move moves[256];
    moveList.moves = moves;
    moveList.nextIndex = 0;

    MoveScore moveScore;
    int legalMoves = 0;

    generateMoves(chessBoard, attackTables, &moveList);

    findKillerMoves(&moveList, depth);

    for (int i = 0; i < moveList.nextIndex; i++)
    {
        //MOVE_COUNTER++;
        setBestMoveFirst(&moveList, i);

        makeMove(chessBoard, &moveList.moves[i]);

        if (!isSquareAttacked(getSqInd(chessBoard->whiteKing), chessBoard, attackTables, 0))
        {
            legalMoves++;
            if (depth > 0)
            {
                moveScore = blackMove(chessBoard, attackTables, depth - 1, alpha, beta);

                if (moveScore.score > bestMove.score)
                {
                    bestMove = moveScore;
                    bestMove.move = moveList.moves[i];  
                }

                if (moveScore.score > alpha)
                {
                    alpha = moveScore.score;
                }

                if (alpha >= beta)
                {
                    setKillerMove(moveList.moves[i], depth);
                    unMakeMove(chessBoard, &moveList.moves[i]);
                    break;
                }
            }
        }

        unMakeMove(chessBoard, &moveList.moves[i]);
    }

    if (legalMoves == 0)
    {
        if (isSquareAttacked(getSqInd(chessBoard->whiteKing), chessBoard, attackTables, 0))
            bestMove.score = WHITE_MATED - depth;
        else
            bestMove.score = 0;

        return bestMove;
    }

    if (depth == 0)
    {
        bestMove.score = evaluatePosition(chessBoard);
    }

    return bestMove;
}

MoveScore evaluate(ChessBoard *chessBoard, AttackTables *attackTables)
{
    MoveScore bestMove;
    initKillerMoves();

    if (isBlack(chessBoard))
    {
        bestMove = blackMove(chessBoard, attackTables, MAX_DEPTH, MIN_INT, MAX_INT);
    }else
    {
        bestMove = whiteMove(chessBoard, attackTables, MAX_DEPTH, MIN_INT, MAX_INT);
    }
    //printf("Moves cut: %llu\n", LEGAL_MOVES - MOVE_COUNTER);
    return bestMove;
}