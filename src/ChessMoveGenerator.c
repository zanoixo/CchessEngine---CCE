#include "ChessMoveGenerator.h"

const uint64_t hFile = 0b1000000010000000100000001000000010000000100000001000000010000000;
const uint64_t aFile = 0b0000000100000001000000010000000100000001000000010000000100000001;

void initBlackPawnAttacks(AttackTables* attackTables)
{
    for (int i = 0; i < 64; i++)
    {
        uint64_t attackBitTable = 0;

        attackBitTable |= (i >> 7) & ~aFile; //bottom left
        attackBitTable |= (i >> 9) & ~hFile; //bottom right

        attackTables->blackPanwsAttacks[i] = attackBitTable;
    }
}

void initWhitePawnAttacks(AttackTables* attackTables)
{
    for (int i = 0; i < 64; i++)
    {
        uint64_t attackBitTable = 0;

        attackBitTable |= (i << 9) & ~aFile; //top left
        attackBitTable |= (i << 7) & ~hFile; //top right

        attackTables->whitePanwsAttacks[i] = attackBitTable;
    }
}

void initKnightAttacks(AttackTables* attackTables)
{
    
}

void initKingAttacks(AttackTables* attackTables)
{
    for (int i = 0; i < 64; i++)
    {
        uint64_t kingPosition = 1ULL << i;  

        uint64_t attackBitTable = 0;
        
        attackBitTable |= (kingPosition << 8); //up
        attackBitTable |= (kingPosition >> 8); // down

        attackBitTable |= (kingPosition << 1) & ~aFile; //left
        attackBitTable |= (kingPosition >> 1) & ~hFile; //right

        attackBitTable |= (kingPosition << 9) & ~aFile; //top left
        attackBitTable |= (kingPosition << 7) & ~hFile; //top right

        attackBitTable |= (kingPosition >> 7) & ~aFile; //bottom left
        attackBitTable |= (kingPosition >> 9) & ~hFile; //bottom right

        attackTables->kingAttacks[i] = attackBitTable;
    }
}

AttackTables* initAttackTables()
{
    AttackTables* attackTables = malloc(sizeof(AttackTables));

    initBlackPawnAttacks(attackTables);
    initWhitePawnAttacks(attackTables);
    initKnightAttacks(attackTables);
    initKingAttacks(attackTables);
    
    return attackTables;
}