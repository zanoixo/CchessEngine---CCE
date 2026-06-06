#include "ChessBoard.h"
#include "ChessMoveGenerator.h"
#include "ChessUtils.h"
#include "ChessEval.h"

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

    score -= countPieces(chessBoard->blackPawns)   * PAWN_VALUE;
    score -= countPieces(chessBoard->blackKnights) * KNIGHT_VALUE;
    score -= countPieces(chessBoard->blackBishops) * BISHOP_VALUE;
    score -= countPieces(chessBoard->blackRooks)   * ROOK_VALUE;
    score -= countPieces(chessBoard->blackQueens)  * QUEEN_VALUE;

    return score;
}

MoveScore blackMove(ChessBoard *chessBoard, AttackTables *attackTables, int depth, int alpha, int beta)
{
    MoveScore bestMove;
    bestMove.score = MAX_INT;

    MoveList moveList;
    moveList.moves = malloc(sizeof(Move) * 256);
    moveList.nextIndex = 0;

    MoveScore moveScore;
    int legalMoves = 0;

    generateMoves(chessBoard, attackTables, &moveList);

    for (int i = 0; i < moveList.nextIndex; i++)
    {
        makeMove(chessBoard, &moveList.moves[i]);

        if (!isSquareAttacked(getSqInd(chessBoard->blackKing), chessBoard, attackTables, black))
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
                    unMakeMove(chessBoard, &moveList.moves[i]);
                    break;
                }
            }
        }

        unMakeMove(chessBoard, &moveList.moves[i]);
    }

    free(moveList.moves);

    if (legalMoves == 0)
    {
        if (isSquareAttacked(getSqInd(chessBoard->blackKing), chessBoard, attackTables, black))
            bestMove.score = MAX_INT;
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
    bestMove.score = MIN_INT;

    MoveList moveList;
    moveList.moves = malloc(sizeof(Move) * 256);
    moveList.nextIndex = 0;

    MoveScore moveScore;
    int legalMoves = 0;

    generateMoves(chessBoard, attackTables, &moveList);

    for (int i = 0; i < moveList.nextIndex; i++)
    {
        makeMove(chessBoard, &moveList.moves[i]);

        if (!isSquareAttacked(getSqInd(chessBoard->whiteKing), chessBoard, attackTables, white))
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
                    unMakeMove(chessBoard, &moveList.moves[i]);
                    break;
                }
            }
        }

        unMakeMove(chessBoard, &moveList.moves[i]);
    }

    free(moveList.moves);

    if (legalMoves == 0)
    {
        if (isSquareAttacked(getSqInd(chessBoard->whiteKing), chessBoard, attackTables, white))
            bestMove.score = MIN_INT;
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

MoveScore evaluate(ChessBoard *chessBoard, AttackTables *attackTables)
{
    MoveScore bestMove;
    if (isBlack(chessBoard))
    {
        bestMove = blackMove(chessBoard, attackTables, 7, MIN_INT, MAX_INT);
    }else
    {
        bestMove = whiteMove(chessBoard, attackTables, 7, MIN_INT, MAX_INT);
    }
    return bestMove;
}