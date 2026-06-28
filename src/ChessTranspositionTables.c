#include <stdint.h>

#include "ChessTranspositionTables.h"
#include "ChessBoard.h"

uint64_t randomHash = 12121212121212121212ULL;
uint64_t transpositionTableSize = 1 << TRANSPOSITION_TABLE_NUM_OF_BITS;
uint64_t transpositionTableMask = (1 << TRANSPOSITION_TABLE_NUM_OF_BITS) - 1;

uint64_t getRandomHash()
{
    randomHash ^= randomHash << 13;
    randomHash ^= randomHash >> 7;
    randomHash ^= randomHash << 17;
    return randomHash;
}

TranspositionTableHashes* initTranpositionTableHashes()
{
    TranspositionTableHashes* hashes = malloc(sizeof(TranspositionTableHashes));
    hashes->colorHash = getRandomHash();

    for (int piece = 0; piece < DIFFERENT_PIECE_COUNT; piece++)
    {
        for (int sq = 0; sq < BOARD_SIZE; sq++)
        {
            hashes->pieceHashes[piece][sq] = getRandomHash();
        }
        
    }

    for (int right = 0; right < CASTLE_RIGHT_COUNT; right++)
    {
        hashes->castellingHashes[right] = getRandomHash();
    }

    for (int file = 0; file < ENPASSANT_FILES_COUNT; file++)
    {
        hashes->enPassantHashes[file] = getRandomHash();
    }
    
    return hashes;
}

TranspositionTableEntry* initTranpositionTable()
{
    TranspositionTableEntry* transpositionTable = malloc(sizeof(TranspositionTableEntry) * transpositionTableSize);

    clearTranspositionTable(transpositionTable);
    
    return transpositionTable;
}

void clearTranspositionTable(TranspositionTableEntry* transpositionTable)
{
    for (uint64_t i = 0; i < transpositionTableSize; i++)
    {
        transpositionTable[i].depth = -1;
    }   
}

TranspositionTableEntry* getTransposition(ChessBoard* chessBoard, TranspositionTableEntry* transpositionTable, int remainingDepth, int isEvalOnly)
{
    uint64_t index = chessBoard->positionHash & transpositionTableMask;

    if (isEvalOnly && transpositionTable[index].hash != chessBoard->positionHash)
    {
        return NULL;
    }
    

    if (!isEvalOnly && (transpositionTable[index].depth < remainingDepth || transpositionTable[index].hash != chessBoard->positionHash))
    {
        return NULL;
    }
        
    return &transpositionTable[index];
}

void checkTranspositionHit(ChessBoard* chessBoard, TranspositionTableEntry* transpositionTable, TranspositionTableEntry* transpositionScore, TranspositionTableHashes* hashes, int alpha, int beta)
{
    TranspositionTableEntry* transposition = getTransposition(chessBoard, transpositionTable, 0, 1);

    if (transpositionScore != NULL)
    {
        //transpositionHits++;
        if (transpositionScore->flag == alphaCutoff && transpositionScore->moveScore.eval <= alpha)
        {
            //transpositionCutoffs++;
            makeMove(chessBoard, &transpositionScore->moveScore.move, hashes);

            if (!isThreeFoldRepetition(chessBoard))
            {
                transpositionScore = transposition;
            }

            unMakeMove(chessBoard, &transpositionScore->moveScore.move, hashes);
            return;
        }
        else if (transpositionScore->flag == betaCutoff && transpositionScore->moveScore.eval >= beta)
        {
            //transpositionCutoffs++;
            makeMove(chessBoard, &transpositionScore->moveScore.move, hashes);
            
            if (!isThreeFoldRepetition(chessBoard))
            {
                transpositionScore = transposition;
            }

            unMakeMove(chessBoard, &transpositionScore->moveScore.move, hashes);
            return;
        }
        else if (transpositionScore->flag == exactCutoff)
        {
            //transpositionCutoffs++;
            makeMove(chessBoard, &transpositionScore->moveScore.move, hashes);
            
            if (!isThreeFoldRepetition(chessBoard))
            {
                transpositionScore = transposition;
            }

            unMakeMove(chessBoard, &transpositionScore->moveScore.move, hashes);
            return;
        } 
    }
}



void setTransposition(ChessBoard* chessBoard, TranspositionTableEntry* transpositionTable, int remainingDepth, MoveScore* moveScore, int alpha, int beta)
{
    if (moveScore->move.flags == 0)
    {
        return;
    }

    uint8_t transpositionFlag;

    if (moveScore->eval >= beta)
    {
        transpositionFlag = betaCutoff;
    }
    else if (moveScore->eval <= alpha)
    {
        transpositionFlag = alphaCutoff;
    }
    else
    {
        transpositionFlag = exactCutoff;
    }

    

    uint64_t index = chessBoard->positionHash & transpositionTableMask;

    if (transpositionTable[index].depth < remainingDepth)
    {
        transpositionTable[index].moveScore = *moveScore;
        transpositionTable[index].depth = remainingDepth;
        transpositionTable[index].hash = chessBoard->positionHash;
        transpositionTable[index].flag = transpositionFlag;
    }
}