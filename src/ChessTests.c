#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ChessMoveGenerator.h"
#include "ChessUtils.h"

uint64_t positionsGenerated = 0;

void ASSERT_BIT_TABLE(uint64_t acctual, uint64_t expected)
{
    if (acctual != expected)
    {
        printf("ASSERT FAILED acctual: %llu == %llu :expected\n", (unsigned long long)acctual, (unsigned long long)expected);
        printf("GOT: \n");
        showBitBoard(acctual);
        printf("EXPECTED: \n");
        showBitBoard(expected);
        exit(1);
    }
    
}

void ASSERT(int acctual, int expected)
{
    if (acctual != expected)
    {
        printf("ASSERT FAILED acctual: %d == %d :expected\n", acctual, expected);
        printf("GOT: \n");
        printf("EXPECTED: \n");
        exit(1);
    }
    
}

void ASSERT_CHESS_BOARD(ChessBoard *original, ChessBoard *modified)
{
    int isSame = 1;
    if (original->allPieces != modified->allPieces)
    {
        printf("ALL PIECES ASSERT FAILED\n");
        printf("EXPECTED: \n");
        showBitBoard(original->allPieces);
        printf("GOT: \n");
        showBitBoard(modified->allPieces);
        isSame = 0;
    }

    if (original->blackPieces != modified->blackPieces)
    {
        printf("BLACK PIECES ASSERT FAILED\n");
        printf("EXPECTED: \n");
        showBitBoard(original->blackPieces);
        printf("GOT: \n");
        showBitBoard(modified->blackPieces);
        isSame = 0;
    }

    if (original->blackPawns != modified->blackPawns)
    {
        printf("BLACK PAWNS ASSERT FAILED\n");
        printf("EXPECTED: \n");
        showBitBoard(original->blackPawns);
        printf("GOT: \n");
        showBitBoard(modified->blackPawns);
        isSame = 0;
    }

    if (original->blackKnights != modified->blackKnights)
    {
        printf("BLACK KNIGHTS ASSERT FAILED\n");
        printf("EXPECTED: \n");
        showBitBoard(original->blackKnights);
        printf("GOT: \n");
        showBitBoard(modified->blackKnights);
        isSame = 0;
    }
    
    if (original->blackBishops != modified->blackBishops)
    {
        printf("BLACK BISHOPS ASSERT FAILED\n");
        printf("EXPECTED: \n");
        showBitBoard(original->blackBishops);
        printf("GOT: \n");
        showBitBoard(modified->blackBishops);
        isSame = 0;
    }

    if (original->blackRooks != modified->blackRooks)
    {
        printf("BLACK ROOKS ASSERT FAILED\n");
        printf("EXPECTED: \n");
        showBitBoard(original->blackRooks);
        printf("GOT: \n");
        showBitBoard(modified->blackRooks);
        isSame = 0;
    }

    if (original->blackQueens != modified->blackQueens)
    {
        printf("BLACK QUEENS ASSERT FAILED\n");
        printf("EXPECTED: \n");
        showBitBoard(original->blackQueens);
        printf("GOT: \n");
        showBitBoard(modified->blackQueens);
        isSame = 0;
    }

    if (original->blackKing != modified->blackKing)
    {
        printf("BlACK KING ASSERT FAILED\n");
        printf("EXPECTED: \n");
        showBitBoard(original->blackKing);
        printf("GOT: \n");
        showBitBoard(modified->blackKing);
        isSame = 0;
    }

    if (original->whitePieces != modified->whitePieces)
    {
        printf("WHITE PIECES ASSERT FAILED\n");
        printf("EXPECTED: \n");
        showBitBoard(original->whitePieces);
        printf("GOT: \n");
        showBitBoard(modified->whitePieces);
        isSame = 0;
    }

    if (original->whitePawns != modified->whitePawns)
    {
        printf("WHITE PAWNS ASSERT FAILED\n");
        printf("EXPECTED: \n");
        showBitBoard(original->whitePawns);
        printf("GOT: \n");
        showBitBoard(modified->whitePawns);
        isSame = 0;
    }

    if (original->whiteKnights != modified->whiteKnights)
    {
        printf("WHITE KNIGHTS ASSERT FAILED\n");
        printf("EXPECTED: \n");
        showBitBoard(original->whiteKnights);
        printf("GOT: \n");
        showBitBoard(modified->whiteKnights);
        isSame = 0;
    }

    if (original->whiteBishops != modified->whiteBishops)
    {
        printf("WHITE BISHOPS ASSERT FAILED\n");
        printf("EXPECTED: \n");
        showBitBoard(original->whiteBishops);
        printf("GOT: \n");
        showBitBoard(modified->whiteBishops);
        isSame = 0;
    }

    if (original->whiteRooks != modified->whiteRooks)
    {
        printf("WHITE ROOKS ASSERT FAILED\n");
        printf("EXPECTED: \n");
        showBitBoard(original->whiteRooks);
        printf("GOT: \n");
        showBitBoard(modified->whiteRooks);
        isSame = 0;
    }

    if (original->whiteQueens != modified->whiteQueens)
    {
        printf("WHITE QUEENS ASSERT FAILED\n");
        printf("EXPECTED: \n");
        showBitBoard(original->whiteQueens);
        printf("GOT: \n");
        showBitBoard(modified->whiteQueens);
        isSame = 0;
    }

    if (original->whiteKing != modified->whiteKing)
    {
        printf("WHITE KING ASSERT FAILED\n");
        printf("EXPECTED: \n");
        showBitBoard(original->whiteKing);
        printf("GOT: \n");
        showBitBoard(modified->whiteKing);
        isSame = 0;
    }

    if (original->flags != modified->flags)
    {
        printf("FLAG ASSERT FAILED\n");
        printf("EXPECTED: \n");
        showBitBoard(original->whiteKing);
        printf("GOT: \n");
        showBitBoard(modified->whiteKing);
        isSame = 0;
    }

    if (original->enPassantSq != modified->enPassantSq)
    {
        printf("ENPASSANTSQ ASSERT FAILED\n");
        printf("EXPECTED: \n");
        showBitBoard(original->enPassantSq);
        printf("GOT: \n");
        showBitBoard(modified->enPassantSq);
        isSame = 0;
    }

    if (original->positionHash != modified->positionHash)
    {
        printf("POSITION HASH ASSERT FAILED\n");
        printf("EXPECTED: %llu\n", (unsigned long long)original->positionHash);
        printf("GOT: %llu\n", (unsigned long long)modified->positionHash);
        isSame = 0;
    }
    

    if (!isSame)
    {
        exit(1);
    }
}

void resetPiecePositions(ChessBoard* chessBoard)
{
    chessBoard->whitePieces = 0;
    chessBoard->blackPieces = 0;
    chessBoard->allPieces = 0;
}

void runAttackTablesTests()
{
    printf("\nRunning attack table tests:\n");

    AttackTables* attackTables = initAttackTables();

    ASSERT_BIT_TABLE(attackTables->kingAttacks[0],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000011ULL << 8  |
    0b00000010ULL);

    ASSERT_BIT_TABLE(attackTables->kingAttacks[7],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b11000000ULL << 8  |
    0b01000000ULL);

    ASSERT_BIT_TABLE(attackTables->kingAttacks[56],
    0b00000010ULL << 56 |
    0b00000011ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->kingAttacks[63],
    0b01000000ULL << 56 |
    0b11000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->kingAttacks[24],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000011ULL << 32 |
    0b00000010ULL << 24 |
    0b00000011ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->kingAttacks[31],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b11000000ULL << 32 |
    0b01000000ULL << 24 |
    0b11000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->kingAttacks[3],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00011100ULL << 8  |
    0b00010100ULL);

    ASSERT_BIT_TABLE(attackTables->kingAttacks[59],
    0b00010100ULL << 56 |
    0b00011100ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->kingAttacks[27],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00011100ULL << 32 |
    0b00010100ULL << 24 |
    0b00011100ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    printf("[PASS] ALL KING ATTACK TESTS PASSED\n");

    ASSERT_BIT_TABLE(attackTables->whitePanwsAttacks[8],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000010ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->whitePanwsAttacks[15],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b01000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->whitePanwsAttacks[9],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000101ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->whitePanwsAttacks[56],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->whitePanwsAttacks[63],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->whitePanwsAttacks[57],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    printf("[PASS] ALL WHITE PAWN ATTACK TESTS PASSED\n");

    ASSERT_BIT_TABLE(attackTables->blackPanwsAttacks[48],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000010ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->blackPanwsAttacks[55],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b01000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->blackPanwsAttacks[49],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000101ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->blackPanwsAttacks[0],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->blackPanwsAttacks[7],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->blackPanwsAttacks[1],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    printf("[PASS] ALL BLACK PAWN ATTACK TESTS PASSED\n");

    ASSERT_BIT_TABLE(attackTables->knightAttacks[27],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00010100ULL << 40 |
    0b00100010ULL << 32 |
    0b00000000ULL << 24 |
    0b00100010ULL << 16 |
    0b00010100ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->knightAttacks[0],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000010ULL << 16 |
    0b00000100ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->knightAttacks[7],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b01000000ULL << 16 |
    0b00100000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->knightAttacks[56],
    0b00000000ULL << 56 |
    0b00000100ULL << 48 |
    0b00000010ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->knightAttacks[63],
    0b00000000ULL << 56 |
    0b00100000ULL << 48 |
    0b01000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->knightAttacks[46],
    0b10100000ULL << 56 |
    0b00010000ULL << 48 |
    0b00000000ULL << 40 |
    0b00010000ULL << 32 |
    0b10100000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->knightAttacks[48],
    0b00000100ULL << 56 |
    0b00000000ULL << 48 |
    0b00000100ULL << 40 |
    0b00000010ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b00000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->knightAttacks[8],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000010ULL << 24 |
    0b00000100ULL << 16 |
    0b00000000ULL << 8  |
    0b00000100ULL);

    ASSERT_BIT_TABLE(attackTables->knightAttacks[14],
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b10100000ULL << 24 |
    0b00010000ULL << 16 |
    0b00000000ULL << 8  |
    0b00010000ULL);

    printf("[PASS] ALL KNIGHT ATTACK TESTS PASSED\n");

    ASSERT_BIT_TABLE(attackTables->rookMagicHashTable[0].mask,
    0b00000000ULL << 56 |
    0b00000001ULL << 48 |
    0b00000001ULL << 40 |
    0b00000001ULL << 32 |
    0b00000001ULL << 24 |
    0b00000001ULL << 16 |
    0b00000001ULL << 8  |
    0b01111110ULL);

    ASSERT_BIT_TABLE(attackTables->rookMagicHashTable[7].mask,
    0b00000000ULL << 56 |
    0b10000000ULL << 48 |
    0b10000000ULL << 40 |
    0b10000000ULL << 32 |
    0b10000000ULL << 24 |
    0b10000000ULL << 16 |
    0b10000000ULL << 8  |
    0b01111110ULL);

    ASSERT_BIT_TABLE(attackTables->rookMagicHashTable[27].mask,
    0b00000000ULL << 56 |
    0b00001000ULL << 48 |
    0b00001000ULL << 40 |
    0b00001000ULL << 32 |
    0b01110110ULL << 24 |
    0b00001000ULL << 16 |
    0b00001000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->rookMagicHashTable[24].mask,
    0b00000000ULL << 56 |
    0b00000001ULL << 48 |
    0b00000001ULL << 40 |
    0b00000001ULL << 32 |
    0b01111110ULL << 24 |
    0b00000001ULL << 16 |
    0b00000001ULL << 8  |
    0b00000000ULL);

    printf("[PASS] ALL ROOK MASK TESTS PASSED\n");

    uint64_t emptyBlockers = 0;
    uint64_t blockers = 0b00000000ULL << 56 |
                        0b00100100ULL << 48 |
                        0b01000000ULL << 40 |
                        0b00000100ULL << 32 |
                        0b00100000ULL << 24 |
                        0b00000000ULL << 16 |
                        0b01010000ULL << 8  |
                        0b00001000ULL;

    ASSERT_BIT_TABLE(getRookAttackPattern(0, emptyBlockers, attackTables),
    0b00000001ULL << 56 |
    0b00000001ULL << 48 |
    0b00000001ULL << 40 |
    0b00000001ULL << 32 |
    0b00000001ULL << 24 |
    0b00000001ULL << 16 |
    0b00000001ULL << 8  |
    0b11111110ULL);

    ASSERT_BIT_TABLE(getRookAttackPattern(7, emptyBlockers, attackTables),
    0b10000000ULL << 56 |
    0b10000000ULL << 48 |
    0b10000000ULL << 40 |
    0b10000000ULL << 32 |
    0b10000000ULL << 24 |
    0b10000000ULL << 16 |
    0b10000000ULL << 8  |
    0b01111111ULL);

    ASSERT_BIT_TABLE(getRookAttackPattern(56, emptyBlockers, attackTables),
    0b11111110ULL << 56 |
    0b00000001ULL << 48 |
    0b00000001ULL << 40 |
    0b00000001ULL << 32 |
    0b00000001ULL << 24 |
    0b00000001ULL << 16 |
    0b00000001ULL << 8  |
    0b00000001ULL);

    ASSERT_BIT_TABLE(getRookAttackPattern(27, emptyBlockers, attackTables),
    0b00001000ULL << 56 |
    0b00001000ULL << 48 |
    0b00001000ULL << 40 |
    0b00001000ULL << 32 |
    0b11110111ULL << 24 |
    0b00001000ULL << 16 |
    0b00001000ULL << 8  |
    0b00001000ULL);

    ASSERT_BIT_TABLE(getRookAttackPattern(12, emptyBlockers, attackTables),
    0b00010000ULL << 56 |
    0b00010000ULL << 48 |
    0b00010000ULL << 40 |
    0b00010000ULL << 32 |
    0b00010000ULL << 24 |
    0b00010000ULL << 16 |
    0b11101111ULL << 8  |
    0b00010000ULL);

    ASSERT_BIT_TABLE(getRookAttackPattern(7, blockers, attackTables),
    0b10000000ULL << 56 |
    0b10000000ULL << 48 |
    0b10000000ULL << 40 |
    0b10000000ULL << 32 |
    0b10000000ULL << 24 |
    0b10000000ULL << 16 |
    0b10000000ULL << 8  |
    0b01111000ULL);

    ASSERT_BIT_TABLE(getRookAttackPattern(49, blockers, attackTables),
    0b00000010ULL << 56 |
    0b00000101ULL << 48 |
    0b00000010ULL << 40 |
    0b00000010ULL << 32 |
    0b00000010ULL << 24 |
    0b00000010ULL << 16 |
    0b00000010ULL << 8  |
    0b00000010ULL);

    ASSERT_BIT_TABLE(getRookAttackPattern(13, blockers, attackTables),
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00100000ULL << 24 |
    0b00100000ULL << 16 |
    0b01010000ULL << 8  |
    0b00100000ULL);

    printf("[PASS] ALL ROOK ATTACK TESTS PASSED\n");

    ASSERT_BIT_TABLE(attackTables->bishopMagicHashTable[0].mask,
    0b00000000ULL << 56 |
    0b01000000ULL << 48 |
    0b00100000ULL << 40 |
    0b00010000ULL << 32 |
    0b00001000ULL << 24 |
    0b00000100ULL << 16 |
    0b00000010ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->bishopMagicHashTable[7].mask,
    0b00000000ULL << 56 |
    0b00000010ULL << 48 |
    0b00000100ULL << 40 |
    0b00001000ULL << 32 |
    0b00010000ULL << 24 |
    0b00100000ULL << 16 |
    0b01000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->bishopMagicHashTable[27].mask,
    0b00000000ULL << 56 |
    0b01000000ULL << 48 |
    0b00100010ULL << 40 |
    0b00010100ULL << 32 |
    0b00000000ULL << 24 |
    0b00010100ULL << 16 |
    0b00100010ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(attackTables->bishopMagicHashTable[24].mask,
    0b00000000ULL << 56 |
    0b00001000ULL << 48 |
    0b00000100ULL << 40 |
    0b00000010ULL << 32 |
    0b00000000ULL << 24 |
    0b00000010ULL << 16 |
    0b00000100ULL << 8  |
    0b00000000ULL);

    printf("[PASS] ALL BISHOP MASK TESTS PASSED\n");

    emptyBlockers = 0;
    blockers =  0b00000000ULL << 56 |
                0b00100100ULL << 48 |
                0b01000000ULL << 40 |
                0b00000100ULL << 32 |
                0b00100000ULL << 24 |
                0b00000000ULL << 16 |
                0b01010000ULL << 8  |
                0b00001000ULL;

    ASSERT_BIT_TABLE(getBishopAttackPattern(0, emptyBlockers, attackTables),
    0b10000000ULL << 56 |
    0b01000000ULL << 48 |
    0b00100000ULL << 40 |
    0b00010000ULL << 32 |
    0b00001000ULL << 24 |
    0b00000100ULL << 16 |
    0b00000010ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(getBishopAttackPattern(7, emptyBlockers, attackTables),
    0b00000001ULL << 56 |
    0b00000010ULL << 48 |
    0b00000100ULL << 40 |
    0b00001000ULL << 32 |
    0b00010000ULL << 24 |
    0b00100000ULL << 16 |
    0b01000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(getBishopAttackPattern(56, emptyBlockers, attackTables),
    0b00000000ULL << 56 |
    0b00000010ULL << 48 |
    0b00000100ULL << 40 |
    0b00001000ULL << 32 |
    0b00010000ULL << 24 |
    0b00100000ULL << 16 |
    0b01000000ULL << 8  |
    0b10000000ULL);

    ASSERT_BIT_TABLE(getBishopAttackPattern(27, emptyBlockers, attackTables),
    0b10000000ULL << 56 |
    0b01000001ULL << 48 |
    0b00100010ULL << 40 |
    0b00010100ULL << 32 |
    0b00000000ULL << 24 |
    0b00010100ULL << 16 |
    0b00100010ULL << 8  |
    0b01000001ULL);

    ASSERT_BIT_TABLE(getBishopAttackPattern(12, emptyBlockers, attackTables),
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000001ULL << 40 |
    0b10000010ULL << 32 |
    0b01000100ULL << 24 |
    0b00101000ULL << 16 |
    0b00000000ULL << 8  |
    0b00101000ULL);

    ASSERT_BIT_TABLE(getBishopAttackPattern(7, blockers, attackTables),
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000000ULL << 32 |
    0b00000000ULL << 24 |
    0b00000000ULL << 16 |
    0b01000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(getBishopAttackPattern(49, blockers, attackTables),
    0b00000101ULL << 56 |
    0b00000000ULL << 48 |
    0b00000101ULL << 40 |
    0b00001000ULL << 32 |
    0b00010000ULL << 24 |
    0b00100000ULL << 16 |
    0b01000000ULL << 8  |
    0b00000000ULL);

    ASSERT_BIT_TABLE(getBishopAttackPattern(13, blockers, attackTables),
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000100ULL << 32 |
    0b10001000ULL << 24 |
    0b01010000ULL << 16 |
    0b00000000ULL << 8  |
    0b01010000ULL);

    printf("[PASS] ALL BISHOP ATTACK TESTS PASSED\n");

    emptyBlockers = 0;
    blockers =  0b00000000ULL << 56 |
                0b00100100ULL << 48 |
                0b01000000ULL << 40 |
                0b00000100ULL << 32 |
                0b00100000ULL << 24 |
                0b00000000ULL << 16 |
                0b01010000ULL << 8  |
                0b00001000ULL;

    ASSERT_BIT_TABLE(getQueenAttackPattern(0, emptyBlockers, attackTables),
    0b10000001ULL << 56 |
    0b01000001ULL << 48 |
    0b00100001ULL << 40 |
    0b00010001ULL << 32 |
    0b00001001ULL << 24 |
    0b00000101ULL << 16 |
    0b00000011ULL << 8  |
    0b11111110ULL);

    ASSERT_BIT_TABLE(getQueenAttackPattern(7, emptyBlockers, attackTables),
    0b10000001ULL << 56 |
    0b10000010LL << 48 |
    0b10000100ULL << 40 |
    0b10001000ULL << 32 |
    0b10010000ULL << 24 |
    0b10100000ULL << 16 |
    0b11000000ULL << 8  |
    0b01111111ULL);

    ASSERT_BIT_TABLE(getQueenAttackPattern(56, emptyBlockers, attackTables),
    0b11111110ULL << 56 |
    0b00000011ULL << 48 |
    0b00000101ULL << 40 |
    0b00001001ULL << 32 |
    0b00010001ULL << 24 |
    0b00100001ULL << 16 |
    0b01000001ULL << 8  |
    0b10000001ULL);

    ASSERT_BIT_TABLE(getQueenAttackPattern(27, emptyBlockers, attackTables),
    0b10001000ULL << 56 |
    0b01001001ULL << 48 |
    0b00101010ULL << 40 |
    0b00011100ULL << 32 |
    0b11110111ULL << 24 |
    0b00011100ULL << 16 |
    0b00101010ULL << 8  |
    0b01001001ULL);

    ASSERT_BIT_TABLE(getQueenAttackPattern(12, emptyBlockers, attackTables),
    0b00010000ULL << 56 |
    0b00010000ULL << 48 |
    0b00010001ULL << 40 |
    0b10010010ULL << 32 |
    0b01010100ULL << 24 |
    0b00111000ULL << 16 |
    0b11101111ULL << 8  |
    0b00111000ULL);

    ASSERT_BIT_TABLE(getQueenAttackPattern(7, blockers, attackTables),
    0b10000000ULL << 56 |
    0b10000000ULL << 48 |
    0b10000000ULL << 40 |
    0b10000000ULL << 32 |
    0b10000000ULL << 24 |
    0b10000000ULL << 16 |
    0b11000000ULL << 8  |
    0b01111000ULL);

    ASSERT_BIT_TABLE(getQueenAttackPattern(49, blockers, attackTables),
    0b00000111ULL << 56 |
    0b00000101ULL << 48 |
    0b00000111ULL << 40 |
    0b00001010ULL << 32 |
    0b00010010ULL << 24 |
    0b00100010ULL << 16 |
    0b01000010ULL << 8  |
    0b00000010ULL);

    ASSERT_BIT_TABLE(getQueenAttackPattern(13, blockers, attackTables),
    0b00000000ULL << 56 |
    0b00000000ULL << 48 |
    0b00000000ULL << 40 |
    0b00000100ULL << 32 |
    0b10101000ULL << 24 |
    0b01110000ULL << 16 |
    0b01010000ULL << 8  |
    0b01110000ULL);

    printf("[PASS] ALL QUEEN ATTACK TESTS PASSED\n");

    free(attackTables);

}

void runPseudeLegalMovesTests()
{
    printf("\nRunning pseudo legal moves test:\n");
    ChessBoard* chessBoard = initChessBoard();
    AttackTables* attackTables = initAttackTables();
    MoveList* moveList = malloc(sizeof(MoveList));
    moveList->moves = malloc(sizeof(Move) * 64);
    moveList->nextIndex = 0;

    chessBoard->whiteKnights = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00001000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;

    generateKnightMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 8);

    moveList->nextIndex = 0;
    chessBoard->whiteKnights = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000001ULL;
                               
    generateKnightMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 2);

    moveList->nextIndex = 0;
    chessBoard->whiteKnights = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000001ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;
                               
    generateKnightMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 4);

    moveList->nextIndex = 0;
    chessBoard->whiteKnights = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00011000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;
                               
    generateKnightMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 16);

    moveList->nextIndex = 0;
    chessBoard->whiteKnights = 0b10000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000001ULL;
                               
    generateKnightMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 4);

    moveList->nextIndex = 0;
    chessBoard->whiteKnights = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b10000001ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;
                               
    generateKnightMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 8);

    moveList->nextIndex = 0;
    chessBoard->whitePieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00100000ULL << 8  |
                               0b00000000ULL;

    chessBoard->whiteKnights = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b10000000ULL;
                               
    generateKnightMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 1);

    moveList->nextIndex = 0;
    chessBoard->blackPieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b10000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;

    generateKnightMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 1);
    
    printf("[PASS] ALL KNIGH PSEUDO MOVE TESTS PASSED\n");

    resetPiecePositions(chessBoard);

    moveList->nextIndex = 0;
    chessBoard->whiteKing = 0b00000000ULL << 56 |
                            0b00000000ULL << 48 |
                            0b00000000ULL << 40 |
                            0b00000000ULL << 32 |
                            0b00001000ULL << 24 |
                            0b00000000ULL << 16 |
                            0b00000000ULL << 8  |
                            0b00000000ULL;

    generateKingMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 8);

    moveList->nextIndex = 0;
    chessBoard->whiteKing = 0b00000000ULL << 56 |
                            0b00000000ULL << 48 |
                            0b00000000ULL << 40 |
                            0b00000000ULL << 32 |
                            0b00000000ULL << 24 |
                            0b00000000ULL << 16 |
                            0b00000000ULL << 8  |
                            0b00000001ULL;

    generateKingMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 3);

    moveList->nextIndex = 0;
    chessBoard->whiteKing = 0b00000000ULL << 56 |
                            0b00000000ULL << 48 |
                            0b00000000ULL << 40 |
                            0b00000000ULL << 32 |
                            0b00000000ULL << 24 |
                            0b00000001ULL << 16 |
                            0b00000000ULL << 8  |
                            0b00000000ULL;
                               
    generateKingMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 5);

    moveList->nextIndex = 0;
    chessBoard->whitePieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00100000ULL << 8  |
                               0b00000000ULL;

    chessBoard->whiteKing = 0b00000000ULL << 56 |
                            0b00000000ULL << 48 |
                            0b00000000ULL << 40 |
                            0b00000000ULL << 32 |
                            0b00000000ULL << 24 |
                            0b01000000ULL << 16 |
                            0b00000000ULL << 8  |
                            0b00000000ULL;
                               
    generateKingMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 7);

    moveList->nextIndex = 0;
    chessBoard->blackPieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b10000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;

    generateKingMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 7);
    
    printf("[PASS] ALL KING PSEUDO MOVE TESTS PASSED\n");

    resetPiecePositions(chessBoard);

    moveList->nextIndex = 0;

    chessBoard->whiteBishops = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00001000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;

    generateBishopMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 13);

    moveList->nextIndex = 0;
    chessBoard->whiteBishops = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000001ULL;
                               
    generateBishopMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 7);

    moveList->nextIndex = 0;
    chessBoard->whiteBishops = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000001ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;
                               
    generateBishopMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 7);

    moveList->nextIndex = 0;
    chessBoard->whiteBishops = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00011000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;
                               
    generateBishopMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 26);

    moveList->nextIndex = 0;
    chessBoard->whiteBishops = 0b00000001ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000001ULL;
                               
    generateBishopMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 14);

    moveList->nextIndex = 0;
    chessBoard->whiteBishops = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b10000001ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;
                               
    generateBishopMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 14);

    moveList->nextIndex = 0;
    chessBoard->whitePieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00010000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;

    chessBoard->allPieces |= chessBoard->whitePieces;

    chessBoard->whiteBishops = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b10000000ULL;
                               
    generateBishopMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 2);

    moveList->nextIndex = 0;
    chessBoard->blackPieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b01000000ULL << 8  |
                               0b00000000ULL;
    
    chessBoard->allPieces |= chessBoard->blackPieces;

    generateBishopMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 1);
    
    printf("[PASS] ALL BISHOP PSEUDO MOVE TESTS PASSED\n");

    resetPiecePositions(chessBoard);

    moveList->nextIndex = 0;

    chessBoard->whiteRooks = 0b00000000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00001000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b00000000ULL << 8  |
                             0b00000000ULL;

    generateRookMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 14);

    moveList->nextIndex = 0;
    chessBoard->whiteRooks = 0b00000000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b00000000ULL << 8  |
                             0b00000001ULL;
                               
    generateRookMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 14);

    moveList->nextIndex = 0;
    chessBoard->whiteRooks = 0b00000000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000001ULL << 16 |
                             0b00000000ULL << 8  |
                             0b00000000ULL;
                               
    generateRookMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 14);

    moveList->nextIndex = 0;
    chessBoard->whiteRooks = 0b00000000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00010000ULL << 24 |
                             0b00001000ULL << 16 |
                             0b00000000ULL << 8  |
                             0b00000000ULL;
                               
    generateRookMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 28);

    moveList->nextIndex = 0;
    chessBoard->whiteRooks = 0b10000000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b00000000ULL << 8  |
                             0b00000001ULL;
                               
    generateRookMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 28);

    moveList->nextIndex = 0;
    chessBoard->whitePieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00010000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;

    chessBoard->allPieces |= chessBoard->whitePieces;

    chessBoard->whiteRooks = 0b00000000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00010000ULL << 16 |
                             0b00000000ULL << 8  |
                             0b00000000ULL;
                               
    generateRookMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 9);

    moveList->nextIndex = 0;
    chessBoard->blackPieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00010000ULL << 8  |
                               0b00000000ULL;
    
    chessBoard->allPieces |= chessBoard->blackPieces;

    generateRookMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 8);
    
    printf("[PASS] ALL ROOK PSEUDO MOVE TESTS PASSED\n");

    resetPiecePositions(chessBoard);

    moveList->nextIndex = 0;

    chessBoard->whiteQueens = 0b00000000ULL << 56 |
                              0b00000000ULL << 48 |
                              0b00000000ULL << 40 |
                              0b00000000ULL << 32 |
                              0b00001000ULL << 24 |
                              0b00000000ULL << 16 |
                              0b00000000ULL << 8  |
                              0b00000000ULL;

    generateQueenMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 27);

    moveList->nextIndex = 0;
    chessBoard->whiteQueens = 0b00000000ULL << 56 |
                              0b00000000ULL << 48 |
                              0b00000000ULL << 40 |
                              0b00000000ULL << 32 |
                              0b00000000ULL << 24 |
                              0b00000000ULL << 16 |
                              0b00000000ULL << 8  |
                              0b00000001ULL;
                               
    generateQueenMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 21);

    moveList->nextIndex = 0;
    chessBoard->whiteQueens = 0b00000000ULL << 56 |
                              0b00000000ULL << 48 |
                              0b00000000ULL << 40 |
                              0b00000000ULL << 32 |
                              0b00000000ULL << 24 |
                              0b00000001ULL << 16 |
                              0b00000000ULL << 8  |
                              0b00000000ULL;
                               
    generateQueenMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 21);

    moveList->nextIndex = 0;
    chessBoard->whiteQueens = 0b00000000ULL << 56 |
                              0b00000000ULL << 48 |
                              0b00000000ULL << 40 |
                              0b00000000ULL << 32 |
                              0b00001000ULL << 24 |
                              0b00000000ULL << 16 |
                              0b00000000ULL << 8  |
                              0b00000001ULL;
                               
    generateQueenMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 48);

    moveList->nextIndex = 0;
    chessBoard->whiteQueens = 0b00000000ULL << 56 |
                              0b00000000ULL << 48 |
                              0b00000000ULL << 40 |
                              0b00000000ULL << 32 |
                              0b00000000ULL << 24 |
                              0b00000000ULL << 16 |
                              0b10000000ULL << 8  |
                              0b00000001ULL;
                               
    generateQueenMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 42);

    moveList->nextIndex = 0;
    chessBoard->whitePieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00011000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;

    chessBoard->allPieces |= chessBoard->whitePieces;

    chessBoard->whiteQueens = 0b00000000ULL << 56 |
                              0b00000000ULL << 48 |
                              0b00000000ULL << 40 |
                              0b00000000ULL << 32 |
                              0b00000000ULL << 24 |
                              0b00010000ULL << 16 |
                              0b00000000ULL << 8  |
                              0b00000000ULL;
                               
    generateQueenMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 16);

    moveList->nextIndex = 0;
    chessBoard->blackPieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00010000ULL << 8  |
                               0b00000000ULL;
    
    chessBoard->allPieces |= chessBoard->blackPieces;

    generateQueenMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 15);
    
    printf("[PASS] ALL QUEEN PSEUDO MOVE TESTS PASSED\n");

    resetPiecePositions(chessBoard);

    moveList->nextIndex = 0;
    chessBoard->whitePieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b10000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;

    chessBoard->allPieces |= chessBoard->whitePieces;

    chessBoard->whitePawns = 0b00000000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b10000000ULL << 8  |
                             0b00000000ULL;
                               
    generatePawnMoves(chessBoard, attackTables, moveList);
    ASSERT(moveList->nextIndex, 0);

    moveList->nextIndex = 0;
    chessBoard->blackPieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b01000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;
    
    chessBoard->allPieces |= chessBoard->blackPieces;

    generatePawnMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 1);

    resetPiecePositions(chessBoard);

    moveList->nextIndex = 0;
    chessBoard->whitePieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;

    chessBoard->allPieces |= chessBoard->whitePieces;

    chessBoard->whitePawns = 0b00000000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b01000000ULL << 8  |
                             0b00000000ULL;

    chessBoard->blackPieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b11100000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;
    
    chessBoard->allPieces |= chessBoard->blackPieces;

    generatePawnMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 2);

    moveList->nextIndex = 0;
    chessBoard->whitePawns = 0b00000000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b11111111ULL << 8  |
                             0b00000000ULL;

    chessBoard->blackPieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b11111111ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;
    
    chessBoard->allPieces |= chessBoard->blackPieces;

    generatePawnMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 14);

    resetPiecePositions(chessBoard);

    moveList->nextIndex = 0;
    chessBoard->whitePieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b01000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;

    chessBoard->allPieces |= chessBoard->whitePieces;

    chessBoard->whitePawns = 0b00000000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b01000000ULL << 8  |
                             0b00000000ULL;

    chessBoard->blackPieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b10100000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;
    
    chessBoard->allPieces |= chessBoard->blackPieces;

    generatePawnMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 3);

    resetPiecePositions(chessBoard);

    moveList->nextIndex = 0;
    chessBoard->whitePieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;

    chessBoard->allPieces |= chessBoard->whitePieces;

    chessBoard->whitePawns = 0b00000000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b01000000ULL << 8  |
                             0b00000000ULL;

    chessBoard->blackPieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b11100000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;
    
    chessBoard->allPieces |= chessBoard->blackPieces;

    generatePawnMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 2);

    resetPiecePositions(chessBoard);

    moveList->nextIndex = 0;
    chessBoard->whitePieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00100000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;

    chessBoard->allPieces |= chessBoard->whitePieces;

    chessBoard->whitePawns = 0b00000000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b01000000ULL << 8  |
                             0b00000000ULL;

    chessBoard->blackPieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b10000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;
    
    chessBoard->allPieces |= chessBoard->blackPieces;

    generatePawnMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 3);

    resetPiecePositions(chessBoard);

    moveList->nextIndex = 0;
    chessBoard->whitePieces  = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b10101010ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;

    chessBoard->allPieces |= chessBoard->whitePieces;

    chessBoard->whitePawns = 0b00000000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b11111111ULL << 8  |
                             0b00000000ULL;

    generatePawnMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 12);

    resetPiecePositions(chessBoard);

    moveList->nextIndex = 0;

    chessBoard->allPieces |= chessBoard->whitePieces;

    chessBoard->whitePawns = 0b00000000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b01010101ULL << 16 |
                             0b10101010ULL << 8  |
                             0b00000000ULL;

    generatePawnMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 12);

    resetPiecePositions(chessBoard);

    moveList->nextIndex = 0;

    chessBoard->whitePawns = 0b00000000ULL << 56 |
                             0b00000001ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b00000000ULL << 8  |
                             0b00000000ULL;

    generatePawnMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 4);

    moveList->nextIndex = 0;

    chessBoard->whitePawns = 0b00000000ULL << 56 |
                             0b01010101ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b00000000ULL << 8  |
                             0b00000000ULL;

    generatePawnMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 16);

    resetPiecePositions(chessBoard);

    moveList->nextIndex = 0;

    chessBoard->whitePawns = 0b00000000ULL << 56 |
                             0b01000010ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b00000000ULL << 8  |
                             0b00000000ULL;

    chessBoard->blackPieces  = 0b00100111ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;
    
    chessBoard->allPieces |= chessBoard->blackPieces;

    generatePawnMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 16);

    resetPiecePositions(chessBoard);

    moveList->nextIndex = 0;

    chessBoard->whitePawns = 0b00000000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b10000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b00000000ULL << 8  |
                             0b00000000ULL;

    chessBoard->enPassantSq = 0b00000000ULL << 56 |
                              0b00000000ULL << 48 |
                              0b01000000ULL << 40 |
                              0b00000000ULL << 32 |
                              0b00000000ULL << 24 |
                              0b00000000ULL << 16 |
                              0b00000000ULL << 8  |
                              0b00000000ULL;
        
    chessBoard->allPieces = 0b00000000ULL << 56 |
                            0b00000000ULL << 48 |
                            0b10100000ULL << 40 |
                            0b00000000ULL << 32 |
                            0b00000000ULL << 24 |
                            0b00000000ULL << 16 |
                            0b00000000ULL << 8  |
                            0b00000000ULL;

    generatePawnMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 1);

    moveList->nextIndex = 0;

    chessBoard->whitePawns = 0b00000000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b10100000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b00000000ULL << 8  |
                             0b00000000ULL;
            
    generatePawnMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 2);

    printf("[PASS] ALL PAWN PSEUDO MOVE TESTS PASSED\n");

    resetPiecePositions(chessBoard);

    moveList->nextIndex = 0;

    chessBoard->whiteKing = 0b00000000ULL << 56 |
                            0b00000000ULL << 48 |
                            0b00000000ULL << 40 |
                            0b00000000ULL << 32 |
                            0b00000000ULL << 24 |
                            0b00000000ULL << 16 |
                            0b00000000ULL << 8  |
                            0b00010000ULL;
    
    chessBoard->whiteRooks = 0b00000000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b00000000ULL << 8  |
                             0b10000001ULL;
    
    generateCastleMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 0);

    chessBoard->flags = whiteShortCastleMask;

    generateCastleMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 1);

    moveList->nextIndex = 0;

    chessBoard->flags = whiteShortCastleMask + whiteLongCastleMask;

    generateCastleMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 2);

    moveList->nextIndex = 0;

    chessBoard->allPieces = 0b00000000ULL << 56 |
                            0b00000000ULL << 48 |
                            0b00000000ULL << 40 |
                            0b00000000ULL << 32 |
                            0b00000000ULL << 24 |
                            0b00000000ULL << 16 |
                            0b00000000ULL << 8  |
                            0b00000010ULL;
    
    generateCastleMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 1);

    moveList->nextIndex = 0;

    chessBoard->allPieces = 0;

    chessBoard->blackKnights = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000010ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;
    
    generateCastleMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 1);

    moveList->nextIndex = 0;

    chessBoard->blackRooks = 0b00100000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b00000000ULL << 8  |
                             0b00000000ULL;
    
    generateCastleMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 0);

    moveList->nextIndex = 0;

    chessBoard->blackRooks = 0b00000010ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b00000000ULL << 8  |
                             0b00000000ULL;
    
    chessBoard->blackKnights = 0;
    
    generateCastleMoves(chessBoard, attackTables, moveList);

    ASSERT(moveList->nextIndex, 2);

    printf("[PASS] ALL CASTLE PSEUDO MOVE TESTS PASSED\n");

    free(moveList);
    free(attackTables);
    free(chessBoard);
}

void generatePositions(ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes, int depth)
{
    if (depth == 0)
    {
        positionsGenerated++;
        return;
    }
    
    MoveList* moveList = malloc(sizeof(MoveList));
    moveList->moves = malloc(sizeof(Move) * 256);
    moveList->nextIndex = 0;

    uint8_t color = isBlack(chessBoard);

    ChessBoard* chessBoardOriginal = malloc(sizeof(ChessBoard));

    memcpy(chessBoardOriginal, chessBoard, sizeof(ChessBoard));

    uint64_t originalEnPassantSq = chessBoard->enPassantSq;

    generateMoves(chessBoard, attackTables, moveList);
    
    for (int i = 0; i < moveList->nextIndex; i++)
    {
        makeMove(chessBoard, &moveList->moves[i], hashes);

        uint64_t kingPosition = chessBoard->whiteKing;

        if (color == black)
        {
            kingPosition = chessBoard->blackKing;
        }

        if (!isSquareAttacked(getSqInd(kingPosition), chessBoard, attackTables, color))
        {
            generatePositions(chessBoard, attackTables, hashes, depth - 1);
        }
        
        
        unMakeMove(chessBoard, &moveList->moves[i], hashes);
        chessBoard->enPassantSq = originalEnPassantSq;

        ASSERT_CHESS_BOARD(chessBoardOriginal, chessBoard);

    }
    free(chessBoardOriginal);
    free(moveList->moves);
    free(moveList);
}

void runMakeMoveTests()
{
    printf("\nRunning make moves test:\n");
    ChessBoard* chessBoard = initChessBoard();
    AttackTables* attackTables = initAttackTables();
    TranspositionTableHashes* hashes = initTranpositionTableHashes();
    createPosition("startingPosition.txt", chessBoard);
    chessBoard->flags = whiteLongCastleMask | whiteShortCastleMask | blackLongCastleMask | blackShortCastleMask;
    generatePositions(chessBoard, attackTables, hashes, 1);

    ASSERT(positionsGenerated, 20);

    positionsGenerated = 0;

    free(attackTables);
    free(chessBoard);

    chessBoard = initChessBoard();
    attackTables = initAttackTables();
    createPosition("startingPosition.txt", chessBoard);
    chessBoard->flags = whiteLongCastleMask | whiteShortCastleMask | blackLongCastleMask | blackShortCastleMask;
    generatePositions(chessBoard, attackTables, hashes, 2);

    ASSERT(positionsGenerated, 400);

    positionsGenerated = 0;

    free(attackTables);
    free(chessBoard);

    chessBoard = initChessBoard();
    attackTables = initAttackTables();
    createPosition("startingPosition.txt", chessBoard);
    chessBoard->flags = whiteLongCastleMask | whiteShortCastleMask | blackLongCastleMask | blackShortCastleMask;
    generatePositions(chessBoard, attackTables, hashes, 3);

    ASSERT(positionsGenerated, 8902);

    positionsGenerated = 0;

    free(attackTables);
    free(chessBoard);

    chessBoard = initChessBoard();
    attackTables = initAttackTables();
    createPosition("startingPosition.txt", chessBoard);
    chessBoard->flags = whiteLongCastleMask | whiteShortCastleMask | blackLongCastleMask | blackShortCastleMask;
    generatePositions(chessBoard, attackTables, hashes, 4);

    ASSERT(positionsGenerated, 197281);

    positionsGenerated = 0;

    free(attackTables);
    free(chessBoard);

    chessBoard = initChessBoard();
    attackTables = initAttackTables();
    createPosition("startingPosition.txt", chessBoard);
    chessBoard->flags = whiteLongCastleMask | whiteShortCastleMask | blackLongCastleMask | blackShortCastleMask;
    generatePositions(chessBoard, attackTables, hashes, 5);

    ASSERT(positionsGenerated, 4865609);

    positionsGenerated = 0;

    free(attackTables);
    free(chessBoard);

    chessBoard = initChessBoard();
    attackTables = initAttackTables();
    createPosition("startingPosition.txt", chessBoard);
    chessBoard->flags = whiteLongCastleMask | whiteShortCastleMask | blackLongCastleMask | blackShortCastleMask;
    generatePositions(chessBoard, attackTables, hashes, 6);

    ASSERT(positionsGenerated, 119060324);

    positionsGenerated = 0;

    free(attackTables);
    free(chessBoard);

    printf("[PASS] START POSSITION MAKE AND UNMAKE MOVE TESTS PASSED\n");

    chessBoard = initChessBoard();
    attackTables = initAttackTables();
    createPosition("castellingPosition.txt", chessBoard);
    chessBoard->flags = whiteLongCastleMask | whiteShortCastleMask | blackLongCastleMask | blackShortCastleMask;

    generatePositions(chessBoard, attackTables, hashes, 6);

    free(attackTables);
    free(chessBoard);

    printf("[PASS] CASTLLLING MAKE AND UNMAKE MOVE TESTS PASSED\n");

    chessBoard = initChessBoard();
    attackTables = initAttackTables();
    createPosition("promotionPosition.txt", chessBoard);

    generatePositions(chessBoard, attackTables, hashes, 6);

    free(attackTables);
    free(chessBoard);
    free(hashes);

    printf("[PASS] PROMOTION MAKE AND UNMAKE MOVE TESTS PASSED\n");

    printf("[PASS] ALL MAKE AND UNMAKE MOVE TESTS PASSED\n");
}

void runAllTests()
{
    printf("Stating testing:\n");

    runAttackTablesTests();
    runPseudeLegalMovesTests();
    runMakeMoveTests();
}