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

int knightPosTable[64] =
{
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50
};

int bishopPosTable[64] =
{
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -20,-10,-10,-10,-10,-10,-10,-20
};

int rookPosTable[64] =
{
     0,  0,  5, 10, 10,  5,  0,  0,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
     5, 10, 10, 10, 10, 10, 10,  5,
     0,  0,  5, 10, 10,  5,  0,  0
};

int queenPosTable[64] =
{
    -20,-10,-10, -5, -5,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5,  5,  5,  5,  0,-10,
     -5,  0,  5,  5,  5,  5,  0, -5,
      0,  0,  5,  5,  5,  5,  0, -5,
    -10,  5,  5,  5,  5,  5,  0,-10,
    -10,  0,  5,  0,  0,  0,  0,-10,
    -20,-10,-10, -5, -5,-10,-10,-20
};

int whitePawnPosTable[64] =
{
      0,  0,  0,  0,  0,  0,  0,  0,
      5, 10, 10,-20,-20, 10, 10,  5,
      5, -5,-10,  0,  0,-10, -5,  5,
      0,  0,  0, 20, 20,  0,  0,  0,
      5,  5, 10, 25, 25, 10,  5,  5,
     10, 10, 20, 30, 30, 20, 10, 10,
     50, 50, 50, 50, 50, 50, 50, 50,
      0,  0,  0,  0,  0,  0,  0,  0
};

int blackPawnPosTable[64] =
{
     0,  0,  0,  0,  0,  0,  0,  0,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
     5,  5, 10, 25, 25, 10,  5,  5,
     0,  0,  0, 20, 20,  0,  0,  0,
     5, -5,-10,  0,  0,-10, -5,  5,
     5, 10, 10,-20,-20, 10, 10,  5,
     0,  0,  0,  0,  0,  0,  0,  0
};

Move killerMoves[KILLER_MOVE_DEPTH][2];
int historyHeuristic[BOARD_SIZE][BOARD_SIZE][DIFFERENT_PIECE_COUNT / 2];
uint64_t stopTime = 0;
int currentDepth;
int qSearchDepthReached;
int nodesSearched;
int transpositionSearches;
int transpositionHits;
int transpositionCutoffs;
int timeCheckCounter = 1;
int timeLimitReached = 0;

void penalizeHistoryHeuristic(Move move, int remeniningDepth)
{
    historyHeuristic[getSqInd(move.from)][getSqInd(move.to)][getPiece(move.flags) - 1] -= remeniningDepth;     
}

void updateHistoryHeuristic(Move move, int remeniningDepth)
{
    historyHeuristic[getSqInd(move.from)][getSqInd(move.to)][getPiece(move.flags) - 1] += remeniningDepth * remeniningDepth; 
}

int getHistoryHeuristic(Move move)
{
    return historyHeuristic[getSqInd(move.from)][getSqInd(move.to)][getPiece(move.flags) - 1];
}

void clearHistoryHeuristic()
{
    memset(historyHeuristic, 0, sizeof(historyHeuristic));
}

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
    if (!(killerMoves[depth][0].from == killerMove.from && killerMoves[depth][0].to == killerMove.to) &&
        !(killerMoves[depth][1].from == killerMove.from && killerMoves[depth][1].to == killerMove.to))
    {
        killerMoves[depth][1] = killerMoves[depth][0];
        killerMoves[depth][0] = killerMove;
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
    int piecePositioning = 0;

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
        piecePositioning += knightPosTable[sq];
        knights &= knights - 1;
    }

    while (bishops)
    {
        int sq = getSqInd(bishops);
        uint64_t attacks = getBishopAttackPattern(sq, chessBoard->allPieces, attackTables) & ~friendlyPieces;
        mobility += countPieces(attacks) * BISHOP_MOBILITY_VALUE;
        piecePositioning += bishopPosTable[sq];
        bishops &= bishops - 1;
    }

    while (rooks)
    {
        int sq = getSqInd(rooks);
        uint64_t attacks = getRookAttackPattern(sq, chessBoard->allPieces, attackTables) & ~friendlyPieces;
        mobility += countPieces(attacks) * ROOK_MOBILITY_VALUE;
        piecePositioning += rookPosTable[sq];
        rooks &= rooks - 1;
    }

    while (queens)
    {
        int sq = getSqInd(queens);
        uint64_t attacks = getQueenAttackPattern(sq, chessBoard->allPieces, attackTables) & ~friendlyPieces;
        mobility += (countPieces(attacks) * QUEEN_MOBILITY_VALUE);
        piecePositioning += queenPosTable[sq];
        queens &= queens - 1;
    }

    return mobility + piecePositioning;
}

int evaluatePawnPositioning(ChessBoard* chessBoard, int isBlack)
{
    int score = 0;
    
    if (isBlack)
    {
        uint64_t pawns = chessBoard->blackPawns;

        while (pawns)
        {
            int sq = getSqInd(pawns);
            score += blackPawnPosTable[sq];
            pawns &= pawns - 1;
        }   
    }
    else
    {
        uint64_t pawns = chessBoard->whitePawns;

        while (pawns)
        {
            int sq = getSqInd(pawns);
            score += whitePawnPosTable[sq];
            pawns &= pawns - 1;
        }     
    }   
    
    return score; 
}

int evaluateMaterial(ChessBoard* chessBoard, int isBlack)
{
    int score = 0;

    if (isBlack)
    {
        score += countPieces(chessBoard->blackPawns)   * PAWN_VALUE;
        score += countPieces(chessBoard->blackKnights) * KNIGHT_VALUE;
        score += countPieces(chessBoard->blackBishops) * BISHOP_VALUE;
        score += countPieces(chessBoard->blackRooks)   * ROOK_VALUE;
        score += countPieces(chessBoard->blackQueens)  * QUEEN_VALUE;
    }
    else
    {
        score += countPieces(chessBoard->whitePawns)   * PAWN_VALUE;
        score += countPieces(chessBoard->whiteKnights) * KNIGHT_VALUE;
        score += countPieces(chessBoard->whiteBishops) * BISHOP_VALUE;
        score += countPieces(chessBoard->whiteRooks)   * ROOK_VALUE;
        score += countPieces(chessBoard->whiteQueens)  * QUEEN_VALUE;    
    }
    return score;
}

int evaluateCenter(ChessBoard* chessBoard, int isBlack)
{
    int score = 0;

    if (isBlack)
    {
        score += countPieces(chessBoard->blackPieces & innerCenterEval) * INNER_CENTER_VALUE;
        score += countPieces(chessBoard->blackPieces & outerCenterEval) * OUTER_CENTER_VALUE;
    }
    else
    {
        score += countPieces(chessBoard->whitePieces & innerCenterEval) * INNER_CENTER_VALUE;
        score += countPieces(chessBoard->whitePieces & outerCenterEval) * OUTER_CENTER_VALUE;    
    }
    return score;
}

int evaluateBishopPair(ChessBoard* chessBoard, int isBlack)
{
    int score = 0;

    if (isBlack)
    {
       int numberOfBishops = countPieces(chessBoard->blackBishops);

       if (numberOfBishops == 2)
       {
            score = BISHOP_PAIR_VALUE;
       }
       
    }
    else
    {
        int numberOfBishops = countPieces(chessBoard->whiteBishops);

       if (numberOfBishops == 2)
       {
            score = BISHOP_PAIR_VALUE;
       }    
    }
    return score;
}

int evaluatePosition(ChessBoard* chessBoard, AttackTables* attackTables)
{
    int score = 0;

    score += evaluateMaterial(chessBoard, white);
    score += evaluateCenter(chessBoard, white);
    score += evaluateMobility(chessBoard, attackTables, white);
    score += evaluatePawnPositioning(chessBoard, white);
    score += evaluateBishopPair(chessBoard, white);

    score -= evaluateMaterial(chessBoard, black);
    score -= evaluateCenter(chessBoard, black);
    score -= evaluateMobility(chessBoard, attackTables, black);
    score -= evaluatePawnPositioning(chessBoard, black);
    score -= evaluateBishopPair(chessBoard, black);

    return score;
}

void setBestMoveFirst(MoveList* moveList, ChessBoard* chessBoard, TranspositionTableEntry* transpositionTable, int moveCount)
{
    int moveInd = moveCount;
    TranspositionTableEntry* transposition = getTransposition(chessBoard, transpositionTable, 0, 1);

    for (int i = moveCount + 1; i < moveList->nextIndex; i++)
    {   
        if (transposition != NULL && transposition->moveScore.move.from == moveList->moves[i].from && transposition->moveScore.move.to == moveList->moves[i].to)
        {
            moveInd = i;
            break;
        }
        
        if (moveList->moves[i].score > moveList->moves[moveInd].score)
        {
            moveInd = i;
        }
        
        if (moveList->moves[moveInd].score == 0 && getHistoryHeuristic(moveList->moves[i]) > getHistoryHeuristic(moveList->moves[moveInd]))
        {
            moveInd = i;
        }
        
    }
    Move tmp = moveList->moves[moveCount];
    moveList->moves[moveCount] = moveList->moves[moveInd];
    moveList->moves[moveInd] = tmp;
}

int isValidQSearchMove(ChessBoard* chessBoard, AttackTables* attackTables, uint16_t moveFlags)
{
    int color = isBlack(chessBoard);
    uint64_t kingPos = chessBoard->blackKing;
    int isAttackedByWhite = 1;

    if (color == white)
    {
        kingPos = chessBoard->whiteKing;
        isAttackedByWhite = 0;
    }
     
    return getCapturedPiece(moveFlags)  ||
           getPromotionPiece(moveFlags) ||
           isSquareAttacked(getSqInd(kingPos), chessBoard, attackTables, isAttackedByWhite);
}

MoveScore qsearchWhite(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes, TranspositionTableEntry* transpositionTable, int depth, int alpha, int beta)
{
    //nodesSearched++;

    TranspositionTableEntry* transpositionScore;
    transpositionScore = getTransposition(chessBoard, transpositionTable, 0, 1);
    //transpositionSearches++;

    int originalBeta = beta;
    int originalAlpha = alpha;
    int transpositionFlag;

    if (transpositionScore != NULL)
    {
        transpositionHits++;
        if (transpositionScore->flag == alphaCutoff && transpositionScore->moveScore.eval <= alpha)
        {
            //transpositionCutoffs++;
            return transpositionScore->moveScore;
        }
        else if (transpositionScore->flag == betaCutoff && transpositionScore->moveScore.eval >= beta)
        {
            //transpositionCutoffs++;
            return transpositionScore->moveScore;
        }
        else if (transpositionScore->flag == exactCutoff)
        {
            //transpositionCutoffs++;
            return transpositionScore->moveScore;
        }
        
    }


    MoveScore bestMove;
    bestMove.eval = MIN_INT;

    int gotChecked = isSquareAttacked(getSqInd(chessBoard->whiteKing), chessBoard, attackTables, 0);

    if (!gotChecked)
    {
        bestMove.eval = evaluatePosition(chessBoard, attackTables);

        if (bestMove.eval >= beta)
        {
            bestMove.eval = beta;
            return bestMove;
        }

        if (bestMove.eval > alpha)
        {
            alpha = bestMove.eval;
        }
    }

    if (depth > qSearchDepthReached)
    {
        qSearchDepthReached = depth;
        printf("selective search max depth reached: %d\n", qSearchDepthReached);
    }
    

    MoveList moveList;
    Move moves[256];
    moveList.moves = moves;
    moveList.nextIndex = 0;

    int legalMoves = 0;

    MoveScore moveScore;

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
            return bestMove;
        }

        setBestMoveFirst(&moveList,chessBoard, transpositionTable, i);

        if (!gotChecked && !isValidQSearchMove(chessBoard, attackTables, moveList.moves[i].flags))
        {
            continue;
        }
        

        makeMove(chessBoard, &moveList.moves[i], hashes);

        int isNotLegalMove = isSquareAttacked(getSqInd(chessBoard->whiteKing), chessBoard, attackTables, 0);

        if (!isNotLegalMove)
        {
            legalMoves++;

            if (isThreeFoldRepetition(chessBoard))
            {
                moveScore.eval = DRAW;    
            }
            else
            {
                moveScore = qsearchBlack(chessBoard, attackTables, hashes, transpositionTable, depth + 1, alpha, beta);
            }

            if (moveScore.eval > bestMove.eval)
            {
                bestMove = moveScore;
            }
            
            if (moveScore.eval > alpha)
            {
                alpha = moveScore.eval;
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

    
    if (gotChecked && legalMoves == 0)
    {
        bestMove.eval = BLACK_MATED;
    }

    
    if (bestMove.eval >= originalBeta)
    {
        transpositionFlag = betaCutoff;
    }
    else if (bestMove.eval <= originalAlpha)
    {
        transpositionFlag = alphaCutoff;
    }
    else
    {
        transpositionFlag = exactCutoff;
    }

    setTransposition(chessBoard, transpositionTable, -1, transpositionFlag, &bestMove);

    return bestMove;
}

MoveScore qsearchBlack(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes, TranspositionTableEntry* transpositionTable, int depth, int alpha, int beta)
{
    
    TranspositionTableEntry* transpositionScore;
    transpositionScore = getTransposition(chessBoard, transpositionTable, 0, 1);
    
    int originalBeta = beta;
    int originalAlpha = alpha;
    int transpositionFlag;

    if (transpositionScore != NULL)
    {
        if (transpositionScore->flag == alphaCutoff && transpositionScore->moveScore.eval <= alpha)
        {
            return transpositionScore->moveScore;
        }
        else if (transpositionScore->flag == betaCutoff && transpositionScore->moveScore.eval >= beta)
        {
            return transpositionScore->moveScore;
        }
        else if (transpositionScore->flag == exactCutoff)
        {
            return transpositionScore->moveScore;
        }
        
    }

    MoveScore bestMove;
    bestMove.eval = MAX_INT;

    int gotChecked = isSquareAttacked(getSqInd(chessBoard->blackKing), chessBoard, attackTables, 1);

    if (!gotChecked)
    {
        bestMove.eval = evaluatePosition(chessBoard, attackTables);

        if (bestMove.eval <= alpha)
        {
            bestMove.eval = alpha;
            return bestMove;
        }

        if (bestMove.eval < beta)
        {
            beta = bestMove.eval;
        }
    }
    

    if (depth > qSearchDepthReached)
    {
        qSearchDepthReached = depth;
        printf("selective search max depth reached: %d\n", qSearchDepthReached);
    }

    MoveList moveList;
    Move moves[256];
    moveList.moves = moves;
    moveList.nextIndex = 0;

    int legalMoves = 0;

    MoveScore moveScore;

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
            return bestMove;
        }

        setBestMoveFirst(&moveList, chessBoard, transpositionTable, i);

        if (!gotChecked && !isValidQSearchMove(chessBoard, attackTables, moveList.moves[i].flags))
        {
            continue;
        }

        makeMove(chessBoard, &moveList.moves[i], hashes);

        int isNotLegalMove = isSquareAttacked(getSqInd(chessBoard->blackKing), chessBoard, attackTables, 1);

        if (!isNotLegalMove)
        {
            legalMoves++;

            if (isThreeFoldRepetition(chessBoard))
            {
                moveScore.eval = DRAW;    
            }
            else
            {
                moveScore = qsearchWhite(chessBoard, attackTables, hashes, transpositionTable, depth + 1, alpha, beta);
            }

            if (moveScore.eval < bestMove.eval)
            {
                bestMove = moveScore;
            }
            
            if (moveScore.eval < beta)
            {
                beta = moveScore.eval;
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
    if (gotChecked && legalMoves == 0)
    {
        bestMove.eval = WHITE_MATED;
    }

    

    if (bestMove.eval >= originalBeta)
    {
        transpositionFlag = betaCutoff;
    }
    else if (bestMove.eval <= originalAlpha)
    {
        transpositionFlag = alphaCutoff;
    }
    else
    {
        transpositionFlag = exactCutoff;
    }

    setTransposition(chessBoard, transpositionTable, -1, transpositionFlag, &bestMove);
    
    return bestMove;
}

MoveScore blackMove(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes, TranspositionTableEntry* transpositionTable, int depthSearched, int alpha, int beta)
{
    MoveScore bestMove;
    bestMove.eval = MAX_INT;

    if (depthSearched == currentDepth)
    {
        bestMove = qsearchBlack(chessBoard, attackTables, hashes, transpositionTable, depthSearched, alpha, beta);
        return bestMove;
    }

    int originalAlpha = alpha;
    int originalBeta = beta;

    int transpositionFlag;

    MoveList moveList;
    Move moves[256];
    moveList.moves = moves;
    moveList.nextIndex = 0;

    MoveScore moveScore;
    TranspositionTableEntry* transpositionScore;
    int legalMoves = 0;

    transpositionScore = getTransposition(chessBoard, transpositionTable, currentDepth - depthSearched, 0);

    if (transpositionScore != NULL)
    {
        if (transpositionScore->flag == alphaCutoff && transpositionScore->moveScore.eval <= alpha)
        {
            return transpositionScore->moveScore;
        }
        else if (transpositionScore->flag == betaCutoff && transpositionScore->moveScore.eval >= beta)
        {
            return transpositionScore->moveScore;
        }
        else if (transpositionScore->flag == exactCutoff)
        {
            return transpositionScore->moveScore;
        }
        
    }

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

            if (isThreeFoldRepetition(chessBoard))
            {
                moveScore.move = moveList.moves[i];
                moveScore.eval = DRAW;    
            }
            else
            {
                moveScore = whiteMove(chessBoard, attackTables, hashes, transpositionTable, depthSearched + 1, alpha, beta);
            }
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
                if (!getPromotionPiece(moveList.moves[i].flags) && !getCapturedPiece(moveList.moves[i].flags))
                {
                    setKillerMove(moveList.moves[i], depthSearched);
                    updateHistoryHeuristic(moveList.moves[i], currentDepth - depthSearched);

                    /*
                    for (int moveInd = i - 1; moveInd >= 0; moveInd--)
                    {
                        if (moveList.moves[moveInd].score != 0)
                        {
                            break;
                        }
                        
                        penalizeHistoryHeuristic(moveList.moves[moveInd], currentDepth - depthSearched);
                    }
                        */
                }
                
                
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
            bestMove.eval = DRAW;
    }

    if (bestMove.eval >= originalBeta)
    {
        transpositionFlag = betaCutoff;
    }
    else if (bestMove.eval <= originalAlpha)
    {
        transpositionFlag = alphaCutoff;
    }
    else
    {
        transpositionFlag = exactCutoff;
    }

    setTransposition(chessBoard, transpositionTable, currentDepth - depthSearched, transpositionFlag, &bestMove);
    return bestMove;
}

MoveScore whiteMove(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes, TranspositionTableEntry* transpositionTable, int depthSearched, int alpha, int beta)
{
    MoveScore bestMove;
    bestMove.eval = MIN_INT - 1;

    if (depthSearched == currentDepth)
    {
        bestMove = qsearchWhite(chessBoard, attackTables, hashes, transpositionTable, depthSearched, alpha, beta);
        return bestMove;
    }

    int originalAlpha = alpha;
    int originalBeta = beta;

    int transpositionFlag;

    MoveList moveList;
    Move moves[256];
    moveList.moves = moves;
    moveList.nextIndex = 0;

    MoveScore moveScore;
    TranspositionTableEntry* transpositionScore;
    int legalMoves = 0;

    transpositionScore = getTransposition(chessBoard, transpositionTable, currentDepth - depthSearched, 0);

    if (transpositionScore != NULL)
    {
        if (transpositionScore->flag == alphaCutoff && transpositionScore->moveScore.eval <= alpha)
        {
            return transpositionScore->moveScore;
        }
        else if (transpositionScore->flag == betaCutoff && transpositionScore->moveScore.eval >= beta)
        {
            return transpositionScore->moveScore;
        }
        else if (transpositionScore->flag == exactCutoff)
        {
            return transpositionScore->moveScore;
        }
        
    }
    

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

            if (isThreeFoldRepetition(chessBoard))
            {
                moveScore.move = moveList.moves[i];
                moveScore.eval = DRAW;    
            }
            else
            {
                moveScore = blackMove(chessBoard, attackTables, hashes, transpositionTable, depthSearched + 1, alpha, beta);
            }

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
                if (!getPromotionPiece(moveList.moves[i].flags) && !getCapturedPiece(moveList.moves[i].flags))
                {
                    setKillerMove(moveList.moves[i], depthSearched);
                    updateHistoryHeuristic(moveList.moves[i], currentDepth - depthSearched);

                    /*
                    for (int moveInd = i - 1; moveInd >= 0; moveInd--)
                    {
                        if (moveList.moves[moveInd].score != 0)
                        {
                            break;
                        }

                        penalizeHistoryHeuristic(moveList.moves[moveInd], currentDepth - depthSearched);
                    }
                    */
                }
                
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
            bestMove.eval = DRAW;
    }

    if (bestMove.eval >= originalBeta)
    {
        transpositionFlag = betaCutoff;
    }
    else if (bestMove.eval <= originalAlpha)
    {
        transpositionFlag = alphaCutoff;
    }
    else
    {
        transpositionFlag = exactCutoff;
    }

    setTransposition(chessBoard, transpositionTable, currentDepth - depthSearched, transpositionFlag, &bestMove);
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
    qSearchDepthReached = 1;
    while (!timeLimitReached)
    {
        /*
        nodesSearched = 0;
        transpositionSearches = 0;
        transpositionHits = 0;
        transpositionCutoffs = 0;
        */

        printf("Current search depth: %d\n", currentDepth);
        depthBestMove = iterativeSearch(chessBoard, attackTables, transpositionTable, hashes);
        
        //printf("Nodes: %d, Transposition searches: %d, hits: %d, Cutoffs: %d\n", nodesSearched, transpositionSearches, transpositionHits, transpositionCutoffs);
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