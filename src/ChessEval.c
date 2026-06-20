#include <string.h>

#include "ChessBoard.h"
#include "ChessMoveGenerator.h"
#include "ChessUtils.h"
#include "ChessEval.h"
#include "ChessTests.h"
#include "ChessTranspositionTables.h"


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

Move killerMoves[KILLER_MOVE_DEPTH][2];
uint64_t stopTime = 0;
int currentDepth;
int timeCheckCounter = 1;
int timeLimitReached = 0;

void initKillerMoves()
{
    for (int i = 0; i < currentDepth; i++)
    {
        killerMoves[i][0] = (Move){0, 0, 0, 0, 0};
        killerMoves[i][1] = (Move){0, 0, 0, 0, 0};
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

int evaluateMobility(ChessBoard* chessBoard, AttackTables* attackTables, int isBlack)
{
    int mobility = 0;

    uint64_t knights = chessBoard->whiteKnights;
    uint64_t bishops = chessBoard->whiteBishops;
    uint64_t rooks = chessBoard->whiteRooks;
    uint64_t queens = chessBoard->whiteQueens;
    uint64_t friendlyPieces = chessBoard->whitePieces;

    if (isBlack)
    {
        knights = chessBoard->blackKnights;
        bishops = chessBoard->blackBishops;
        rooks = chessBoard->blackRooks;
        queens = chessBoard->blackQueens;
        friendlyPieces = chessBoard->blackPieces;
    }
    
    while (knights)
    {
        int sq = getSqInd(knights);
        uint64_t attacks = attackTables->knightAttacks[sq] & ~friendlyPieces;
        mobility += countPieces(attacks) * KNIGHT_MOBILITY_VALUE;
        knights &= knights - 1;
    }

    while (bishops)
    {
        int sq = getSqInd(bishops);
        uint64_t attacks = getBishopAttackPattern(sq, chessBoard->allPieces, attackTables) & ~friendlyPieces;
        mobility += countPieces(attacks) * BISHOP_MOBILITY_VALUE;
        bishops &= bishops - 1;
    }

    while (rooks)
    {
        int sq = getSqInd(rooks);
        uint64_t attacks = getRookAttackPattern(sq, chessBoard->allPieces, attackTables) & ~friendlyPieces;
        mobility += countPieces(attacks) * ROOK_MOBILITY_VALUE;
        rooks &= rooks - 1;
    }

    while (queens)
    {
        int sq = getSqInd(queens);
        uint64_t attacks = getQueenAttackPattern(sq, chessBoard->allPieces, attackTables) & ~friendlyPieces;
        mobility += countPieces(attacks) * QUEEN_MOBILITY_VALUE;
        queens &= queens - 1;
    }

    return mobility;
}


int evaluatePosition(ChessBoard *chessBoard, AttackTables* attackTables)
{
    int score = 0;

    score += countPieces(chessBoard->whitePawns)   * PAWN_VALUE;
    score += countPieces(chessBoard->whiteKnights) * KNIGHT_VALUE;
    score += countPieces(chessBoard->whiteBishops) * BISHOP_VALUE;
    score += countPieces(chessBoard->whiteRooks)   * ROOK_VALUE;
    score += countPieces(chessBoard->whiteQueens)  * QUEEN_VALUE;
    score += countPieces(chessBoard->whitePieces & innerCenterEval) * INNER_CENTER_VALUE;
    score += countPieces(chessBoard->whitePieces & outerCenterEval) * OUTER_CENTER_VALUE;
    score += evaluateMobility(chessBoard, attackTables, white);

    score -= countPieces(chessBoard->blackPawns)   * PAWN_VALUE;
    score -= countPieces(chessBoard->blackKnights) * KNIGHT_VALUE;
    score -= countPieces(chessBoard->blackBishops) * BISHOP_VALUE;
    score -= countPieces(chessBoard->blackRooks)   * ROOK_VALUE;
    score -= countPieces(chessBoard->blackQueens)  * QUEEN_VALUE;
    score -= countPieces(chessBoard->blackPieces & innerCenterEval) * INNER_CENTER_VALUE;
    score -= countPieces(chessBoard->blackPieces & outerCenterEval) * OUTER_CENTER_VALUE;
    score -= evaluateMobility(chessBoard, attackTables, black);

    return score;
}

void setBestMoveFirst(MoveList* moveList, ChessBoard* chessBoard, TranspositionTableEntry* transpositionTable, int moveCount)
{
    int moveInd = moveCount;
    MoveScore* transpositionMove = getTransposition(chessBoard, transpositionTable, 0, 1);

    for (int i = moveCount + 1; i < moveList->nextIndex; i++)
    {   
        if (transpositionMove != NULL && transpositionMove->move.from == moveList->moves[i].from && transpositionMove->move.to == moveList->moves[i].to)
        {
            moveInd = i;
            break;
        }
        
        if (moveList->moves[i].score > moveList->moves[moveInd].score)
        {
            moveInd = i;
        }
        
    }
    Move tmp = moveList->moves[moveCount];
    moveList->moves[moveCount] = moveList->moves[moveInd];
    moveList->moves[moveInd] = tmp;
}

int qsearchWhite(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes, TranspositionTableEntry* transpositionTable, int alpha, int beta)
{
    int score = evaluatePosition(chessBoard, attackTables);

    if (score >= beta)
    {
        return beta;
    }

    if (score > alpha)
    {
        alpha = score;
    }

    MoveList moveList;
    Move moves[256];
    moveList.moves = moves;
    moveList.nextIndex = 0;

    int moveScore;

    //ChessBoard* original = malloc(sizeof(ChessBoard));
    //memcpy(original, chessBoard, sizeof(ChessBoard));

    generateMoves(chessBoard, attackTables, &moveList);
    

    for (int i = 0; i < moveList.nextIndex; i++)
    {
        timeCheckCounter++;
        
        if ((timeCheckCounter & TIME_CHECK) == 0)
        {
            timeCheckCounter = 1;
            
            if (stopTime < getTimeMs())
            {
                timeLimitReached = 1;
            }
            
        }

        if (timeLimitReached)
        {
            //free(original);
            return 0;
        }

        setBestMoveFirst(&moveList,chessBoard, transpositionTable, i);

        if (!getCapturedPiece(moveList.moves[i].flags) && !getPromotionPiece(moveList.moves[i].flags))
        {
            break;
        }

        makeMove(chessBoard, &moveList.moves[i], hashes);

        int isChecked = isSquareAttacked(getSqInd(chessBoard->whiteKing), chessBoard, attackTables, 0);

        if (!isChecked)
        {
            moveScore = qsearchBlack(chessBoard, attackTables, hashes, transpositionTable, alpha, beta);

            if (moveScore > alpha)
            {
                alpha = moveScore;
            }

            if (alpha >= beta)
            {
                unMakeMove(chessBoard, &moveList.moves[i], hashes);
                //ASSERT_CHESS_BOARD(original, chessBoard);
                break;
            }
        }

        unMakeMove(chessBoard, &moveList.moves[i], hashes);
        //ASSERT_CHESS_BOARD(original, chessBoard);
    }
    //free(original);
    return alpha;
}

int qsearchBlack(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes, TranspositionTableEntry* transpositionTable, int alpha, int beta)
{
    int score = evaluatePosition(chessBoard, attackTables);

    if (score <= alpha)
    {
        return alpha;
    }

    if (score < beta)
    {
        beta = score;
    }

    MoveList moveList;
    Move moves[256];
    moveList.moves = moves;
    moveList.nextIndex = 0;

    int moveScore;

    //ChessBoard* original = malloc(sizeof(ChessBoard));
    //memcpy(original, chessBoard, sizeof(ChessBoard));


    generateMoves(chessBoard, attackTables, &moveList);

    for (int i = 0; i < moveList.nextIndex; i++)
    {
        timeCheckCounter++;
        
        if ((timeCheckCounter & TIME_CHECK) == 0)
        {
            timeCheckCounter = 1;
            
            if (stopTime < getTimeMs())
            {
                timeLimitReached = 1;
            }
            
        }

        if (timeLimitReached)
        {
            //free(original);
            return 0;
        }

        setBestMoveFirst(&moveList, chessBoard, transpositionTable, i);

        if (!getCapturedPiece(moveList.moves[i].flags) && !getPromotionPiece(moveList.moves[i].flags))
        {
            break;
        }

        makeMove(chessBoard, &moveList.moves[i], hashes);

        int isChecked = isSquareAttacked(getSqInd(chessBoard->blackKing), chessBoard, attackTables, 1);

        if (!isChecked)
        {
            moveScore = qsearchWhite(chessBoard, attackTables, hashes, transpositionTable, alpha, beta);
            
            if (moveScore < beta)
            {
                beta = moveScore;
            }

            if (alpha >= beta)
            {
                unMakeMove(chessBoard, &moveList.moves[i], hashes);
                //ASSERT_CHESS_BOARD(original, chessBoard);
                break;
            }
        }

        unMakeMove(chessBoard, &moveList.moves[i], hashes);
        //ASSERT_CHESS_BOARD(original, chessBoard);
    }
    //free(original);
    return beta;
}

MoveScore blackMove(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes, TranspositionTableEntry* transpositionTable, int depthSearched, int alpha, int beta)
{
    MoveScore bestMove;
    bestMove.eval = MAX_INT;

    if (depthSearched == currentDepth)
    {
        bestMove.eval = qsearchBlack(chessBoard, attackTables, hashes, transpositionTable, alpha, beta);
        return bestMove;
    }

    MoveList moveList;
    Move moves[256];
    moveList.moves = moves;
    moveList.nextIndex = 0;

    MoveScore moveScore;
    int legalMoves = 0;

    //ChessBoard* original = malloc(sizeof(ChessBoard));
    //memcpy(original, chessBoard, sizeof(ChessBoard));

    generateMoves(chessBoard, attackTables, &moveList);

    findKillerMoves(&moveList, depthSearched);

    for (int i = 0; i < moveList.nextIndex; i++)
    {
        timeCheckCounter++;

        if ((timeCheckCounter & TIME_CHECK) == 0)
        {
            timeCheckCounter = 1;
            
            if (stopTime < getTimeMs())
            {
                timeLimitReached = 1;
            }
            
        }

        if (timeLimitReached)
        {
            //free(original);
            return bestMove;
        }
        
        
        setBestMoveFirst(&moveList, chessBoard, transpositionTable, i);

        makeMove(chessBoard, &moveList.moves[i], hashes);

        int isChecked = isSquareAttacked(getSqInd(chessBoard->blackKing), chessBoard, attackTables, 1);

        if (!isChecked)
        {
            legalMoves++;

            moveScore = whiteMove(chessBoard, attackTables, hashes, transpositionTable, depthSearched + 1, alpha, beta);

            if (moveScore.eval < bestMove.eval)
            {
                bestMove = moveScore;
                bestMove.move = moveList.moves[i];
            }

            if (moveScore.eval < beta)
            {
                beta = moveScore.eval;
            }

            if (alpha >= beta)
            {
                setKillerMove(moveList.moves[i], depthSearched);
                unMakeMove(chessBoard, &moveList.moves[i], hashes);
                //ASSERT_CHESS_BOARD(original, chessBoard);
                break;
            }
            
        }

        unMakeMove(chessBoard, &moveList.moves[i], hashes);
        //ASSERT_CHESS_BOARD(original, chessBoard);
    }
    //free(original);
    if (legalMoves == 0)
    {
        if (isSquareAttacked(getSqInd(chessBoard->blackKing), chessBoard, attackTables, 1))
            bestMove.eval = BLACK_MATED;
        else
            bestMove.eval = 0;
    }

    setTransposition(chessBoard, transpositionTable, currentDepth - depthSearched, &bestMove);
    return bestMove;
}

MoveScore whiteMove(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes, TranspositionTableEntry* transpositionTable, int depthSearched, int alpha, int beta)
{
    MoveScore bestMove;
    bestMove.eval = MIN_INT - 1;

    if (depthSearched == currentDepth)
    {
        bestMove.eval = qsearchWhite(chessBoard, attackTables, hashes, transpositionTable, alpha, beta);
        return bestMove;
    }

    MoveList moveList;
    Move moves[256];
    moveList.moves = moves;
    moveList.nextIndex = 0;

    MoveScore moveScore;
    int legalMoves = 0;

    //ChessBoard* original = malloc(sizeof(ChessBoard));
    //memcpy(original, chessBoard, sizeof(ChessBoard));
    
    generateMoves(chessBoard, attackTables, &moveList);
    
    findKillerMoves(&moveList, depthSearched);

    
    
    for (int i = 0; i < moveList.nextIndex; i++)
    {
        timeCheckCounter++;
        
        if ((timeCheckCounter & TIME_CHECK) == 0)
        {
            timeCheckCounter = 1;
            
            if (stopTime < getTimeMs())
            {
                timeLimitReached = 1;
            }
            
        }

        if (timeLimitReached)
        {
            //free(original);
            return bestMove;
        }

        setBestMoveFirst(&moveList, chessBoard, transpositionTable, i);
        
        makeMove(chessBoard, &moveList.moves[i], hashes);

        int isChecked = isSquareAttacked(getSqInd(chessBoard->whiteKing), chessBoard, attackTables, 0);

        if (!isChecked)
        {
            legalMoves++;

            moveScore = blackMove(chessBoard, attackTables, hashes, transpositionTable, depthSearched + 1, alpha, beta);

            if (moveScore.eval > bestMove.eval)
            {
                bestMove = moveScore;
                bestMove.move = moveList.moves[i];  
            }

            if (moveScore.eval > alpha)
            {
                alpha = moveScore.eval;
            }

            if (alpha >= beta)
            {
                setKillerMove(moveList.moves[i], depthSearched);
                unMakeMove(chessBoard, &moveList.moves[i], hashes);
                //ASSERT_CHESS_BOARD(original, chessBoard);
                break;
            }
            
        }
        unMakeMove(chessBoard, &moveList.moves[i], hashes);
        //ASSERT_CHESS_BOARD(original, chessBoard);
    }
    //free(original);
    if (legalMoves == 0)
    {
        if (isSquareAttacked(getSqInd(chessBoard->whiteKing), chessBoard, attackTables, 0))
            bestMove.eval = WHITE_MATED;
        else
            bestMove.eval = 0;
    }

    setTransposition(chessBoard, transpositionTable, currentDepth - depthSearched, &bestMove);
    return bestMove;
}

MoveScore iterativeSearch(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableEntry* transpositionTable, TranspositionTableHashes* hashes)
{
    MoveScore bestMove;
    initKillerMoves();
    if (isBlack(chessBoard))
    {
        bestMove = blackMove(chessBoard, attackTables, hashes, transpositionTable, 0, MIN_INT, MAX_INT);
    }else
    {
        bestMove = whiteMove(chessBoard, attackTables, hashes, transpositionTable, 0, MIN_INT, MAX_INT);
    }
    return bestMove;
}

MoveScore evaluate(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes, TranspositionTableEntry* transpositionTable, uint64_t timePerMove)
{
    MoveScore currentBestMove;
    MoveScore depthBestMove;
    timeLimitReached = 0;
    timeCheckCounter = 1;
    stopTime = getTimeMs() + timePerMove - 100;

    currentDepth = 1;
    while (!timeLimitReached)
    {
        printf("Current search depth: %d\n", currentDepth);
        depthBestMove = iterativeSearch(chessBoard, attackTables, transpositionTable, hashes);
        
        if (!timeLimitReached)
        {
            currentBestMove = depthBestMove;
        }

        if (currentBestMove.eval == BLACK_MATED || currentBestMove.eval == WHITE_MATED)
        {
            break;
        }
        
        
        currentDepth++;  
    }
    return currentBestMove;
}