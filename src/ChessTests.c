#include <stdio.h>
#include "ChessMoveGenerator.h"
#include "ChessUtils.h"

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

void runAllTests()
{
    printf("Stating testing:\n");

    runAttackTablesTests();
    runPseudeLegalMovesTests();
}