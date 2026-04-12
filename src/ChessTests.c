#include "stdio.h"
#include "ChessMoveGenerator.h"

void showBitBoard(uint64_t bitBoard)
{
    for (int rank = 7; rank >= 0; rank--)
    {
        for (int file = 0; file < 8; file++)
        {
            int square = rank * 8 + file;
            uint64_t mask = 1ULL << square;

            printf("%d ", (bitBoard & mask) ? 1 : 0);
        }

        printf("\n");
    }
}

void ASSERT_BIT_TABLE(uint64_t acctual, uint64_t expected)
{
    if (acctual != expected)
    {
        printf("GOT: \n");
        showBitBoard(acctual);
        printf("EXPECTED: \n");
        showBitBoard(expected);
        exit(1);
    }
    
}

void runAttackTablesTests()
{
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

    printf("ALL KING ATTACK TESTS PASSED\n");

    free(attackTables);

}

void runAllTests()
{
    printf("Stating testing:\n");
    printf("Running attack table tests testing:\n");

    runAttackTablesTests();
}