#include <stdio.h>
#include <time.h>
#include <string.h>
#include "ChessMoveGenerator.h"
#include "ChessUtils.h"

const uint64_t hFile = 0b10000000ULL << 56 |
                       0b10000000ULL << 48 |
                       0b10000000ULL << 40 |
                       0b10000000ULL << 32 |
                       0b10000000ULL << 24 |
                       0b10000000ULL << 16 |
                       0b10000000ULL << 8  |
                       0b10000000ULL;

const uint64_t aFile = 0b00000001ULL << 56 |
                       0b00000001ULL << 48 |
                       0b00000001ULL << 40 |
                       0b00000001ULL << 32 |
                       0b00000001ULL << 24 |
                       0b00000001ULL << 16 |
                       0b00000001ULL << 8  |
                       0b00000001ULL;

const uint64_t gFile = 0b01000000ULL << 56 |
                       0b01000000ULL << 48 |
                       0b01000000ULL << 40 |
                       0b01000000ULL << 32 |
                       0b01000000ULL << 24 |
                       0b01000000ULL << 16 |
                       0b01000000ULL << 8  |
                       0b01000000ULL;

const uint64_t bFile = 0b00000010ULL << 56 |
                       0b00000010ULL << 48 |
                       0b00000010ULL << 40 |
                       0b00000010ULL << 32 |
                       0b00000010ULL << 24 |
                       0b00000010ULL << 16 |
                       0b00000010ULL << 8  |
                       0b00000010ULL;

const uint64_t line7 = 0b00000000ULL << 56 |
                       0b11111111ULL << 48 |
                       0b00000000ULL << 40 |
                       0b00000000ULL << 32 |
                       0b00000000ULL << 24 |
                       0b00000000ULL << 16 |
                       0b00000000ULL << 8  |
                       0b00000000ULL;

const uint64_t line2 = 0b00000000ULL << 56 |
                       0b00000000ULL << 48 |
                       0b00000000ULL << 40 |
                       0b00000000ULL << 32 |
                       0b00000000ULL << 24 |
                       0b00000000ULL << 16 |
                       0b11111111ULL << 8  |
                       0b00000000ULL;

const uint64_t line8 = 0b11111111ULL << 56 |
                       0b00000000ULL << 48 |
                       0b00000000ULL << 40 |
                       0b00000000ULL << 32 |
                       0b00000000ULL << 24 |
                       0b00000000ULL << 16 |
                       0b00000000ULL << 8  |
                       0b00000000ULL;

const uint64_t line1 = 0b00000000ULL << 56 |
                       0b00000000ULL << 48 |
                       0b00000000ULL << 40 |
                       0b00000000ULL << 32 |
                       0b00000000ULL << 24 |
                       0b00000000ULL << 16 |
                       0b00000000ULL << 8  |
                       0b11111111ULL;

const uint64_t e1 = 0b00000000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00010000ULL; 

const uint64_t e8 = 0b00010000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00000000ULL;

const uint64_t b1 = 0b00000000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00000010ULL; 

const uint64_t c1 = 0b00000000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00000100ULL; 

const uint64_t d1 = 0b00000000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00001000ULL; 

const uint64_t f1 = 0b00000000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00100000ULL; 

const uint64_t g1 = 0b00000000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b01000000ULL; 

const uint64_t b8 = 0b00000010ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00000000ULL; 

const uint64_t c8 = 0b00000100ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00000000ULL; 

const uint64_t d8 = 0b00001000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00000000ULL; 

const uint64_t f8 = 0b00100000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00000000ULL; 

const uint64_t g8 = 0b01000000ULL << 56 |
                    0b00000000ULL << 48 |
                    0b00000000ULL << 40 |
                    0b00000000ULL << 32 |
                    0b00000000ULL << 24 |
                    0b00000000ULL << 16 |
                    0b00000000ULL << 8  |
                    0b00000000ULL; 


uint64_t MAX_NUMBER_OF_MAGICS = 10000000;

int attackPatternCounter = 0;
BlockerAttackPattern attackPatterns[64][4096];

uint64_t randomState;

uint64_t generateRandomMagic()
{
    randomState ^= randomState << 13;
    randomState ^= randomState >> 7;
    randomState ^= randomState << 17;

    uint64_t firstRandomPart = randomState;

    randomState ^= randomState << 13;
    randomState ^= randomState >> 7;
    randomState ^= randomState << 17;

    uint64_t secondRandomPart = randomState;

    randomState ^= randomState << 13;
    randomState ^= randomState >> 7;
    randomState ^= randomState << 17;

    uint64_t thirdRandomPart = randomState;
 
    return firstRandomPart & secondRandomPart & thirdRandomPart;
}

int numberOfRookMovementBits(int rookSqInd)
{
    int column = rookSqInd % 8;
    int row = rookSqInd / 8;

    int left  = column - 1;
    int right = 7 - column - 1;
    int up    = 7 - row - 1;
    int down  = row - 1;

    int bits = 0;

    if (left > 0)
    {
        bits += left;
    } 
    if (right > 0)
    {
        bits += right;
    } 
    if (up > 0)
    {
        bits += up;
    } 
    if (down > 0)
    {
        bits += down;
    } 

    return bits;
}

int numberOfBishopMovementBits(int bishopSqInd)
{
    int column = bishopSqInd % 8;
    int row = bishopSqInd / 8;
 
    int left  = column - 1;
    int right = 7 - column - 1;
    int up    = 7 - row - 1;
    int down  = row - 1;

    int topLeft    = (up < left) ? up : left;
    int topRight   = (up < right) ? up : right;
    int bottomLeft  = (down < left) ? down : left;
    int bottomRight = (down < right) ? down : right;

    int bits = 0;

    if (topLeft  > 0)
    {
        bits += topLeft;
    } 
    if (topRight > 0)
    {
        bits += topRight;
    } 
    if (bottomLeft > 0)
    {
        bits += bottomLeft;
    } 
    if (bottomRight  > 0)
    {
        bits += bottomRight;
    } 

    return bits;
}

void initBlackPawnAttacks(AttackTables* attackTables)
{
    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        uint64_t attackBitTable = 0;

        uint64_t pawnPosition = 1ULL << sqInd; 

        attackBitTable |= (pawnPosition >> 7) & ~aFile; //bottom left
        attackBitTable |= (pawnPosition >> 9) & ~hFile; //bottom right

        attackTables->blackPanwsAttacks[sqInd] = attackBitTable;
    }
}

void initWhitePawnAttacks(AttackTables* attackTables)
{
    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        uint64_t attackBitTable = 0;

        uint64_t pawnPosition = 1ULL << sqInd;

        attackBitTable |= (pawnPosition << 9) & ~aFile; //top left
        attackBitTable |= (pawnPosition << 7) & ~hFile; //top right

        attackTables->whitePanwsAttacks[sqInd] = attackBitTable;
    }
}

void initKnightAttacks(AttackTables* attackTables)
{
    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        uint64_t attackBitTable = 0;

        uint64_t knightPosition = 1ULL << sqInd;

        attackBitTable |= (knightPosition << 10) & ~(aFile | bFile); //top left corner
        attackBitTable |= (knightPosition << 17) & ~aFile;

        attackBitTable |= (knightPosition << 6) & ~(hFile | gFile); //top right corner
        attackBitTable |= (knightPosition << 15) & ~hFile;

        attackBitTable |= (knightPosition >> 6) & ~(aFile | bFile); //bottom left corner
        attackBitTable |= (knightPosition >> 15) & ~aFile;

        attackBitTable |= (knightPosition >> 10) & ~(hFile | gFile); //bottom right corner
        attackBitTable |= (knightPosition >> 17) & ~hFile;

        attackTables->knightAttacks[sqInd] = attackBitTable;
    } 
}

void initKingAttacks(AttackTables* attackTables)
{
    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        uint64_t kingPosition = 1ULL << sqInd;  

        uint64_t attackBitTable = 0;
        
        attackBitTable |= (kingPosition << 8); //up
        attackBitTable |= (kingPosition >> 8); // down

        attackBitTable |= (kingPosition << 1) & ~aFile; //left
        attackBitTable |= (kingPosition >> 1) & ~hFile; //right

        attackBitTable |= (kingPosition << 9) & ~aFile; //top left
        attackBitTable |= (kingPosition << 7) & ~hFile; //top right

        attackBitTable |= (kingPosition >> 7) & ~aFile; //bottom left
        attackBitTable |= (kingPosition >> 9) & ~hFile; //bottom right

        attackTables->kingAttacks[sqInd] = attackBitTable;
    }
}

int isMagicNumberValid(int sqInd, uint64_t magicNumber, int numOfIndexBits, int isRook)
{   
    int numberOfBits;

    if (isRook)
    {
        numberOfBits = numberOfRookMovementBits(sqInd);
    }else
    {
        numberOfBits = numberOfBishopMovementBits(sqInd);
    }

    uint64_t tempHashTable[1 << numOfIndexBits];
    uint64_t usedIndexes[1 << numOfIndexBits];

    memset(tempHashTable, 0, sizeof(tempHashTable));
    memset(usedIndexes, 0, sizeof(usedIndexes));
    

    for (int variation = 0; variation < 1 << numberOfBits; variation++)
    {
        BlockerAttackPattern blockerAttackPattern = attackPatterns[sqInd][variation];
        uint64_t newInd = (blockerAttackPattern.blockerPattern * magicNumber) >> (64 - numOfIndexBits);
        if (usedIndexes[newInd] != 0 && tempHashTable[newInd] != blockerAttackPattern.attackPattern)
        {
            return 0;
        }else
        {
            tempHashTable[newInd] = blockerAttackPattern.attackPattern;
            usedIndexes[newInd] = 1;
        }
    }

    return 1;
}

void saveMagics(uint64_t validMagicNumbers[], int numberOfBits[], int isRook)
{   
    FILE* file;

    if (isRook)
    {
        file = fopen("magics/rookMagics.csv", "w");
    }else
    {
        file = fopen("magics/bishopMagics.csv", "w");    
    }
    
    
    if (!file)
    {
        printf("Failed to open file\n");
        return;
    }

    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        fprintf(file, "%d,%d,%llu\n", sqInd, numberOfBits[sqInd],(unsigned long long)validMagicNumbers[sqInd]);
    }

    fclose(file);
}

void findAndSaveMagics(int isRook)
{
    uint64_t validMagicNumbers[64] = {0};
    int numberOfBits[64] = {0};
    uint64_t magicNumber;
    randomState = time(NULL);
    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        for (int nBits = 12; nBits > 0; nBits--)
        {
            int wasMagicFound = 0;
            for (uint64_t magicAttempt = 0; magicAttempt < MAX_NUMBER_OF_MAGICS; magicAttempt++)
            {
                magicNumber = generateRandomMagic();
                if (isMagicNumberValid(sqInd, magicNumber, nBits, isRook))
                {
                    validMagicNumbers[sqInd] = magicNumber;
                    numberOfBits[sqInd] = nBits;
                    wasMagicFound = 1;
                    break;
                }
            }
            if (!wasMagicFound)
            {
                printf("%d magic not found\n", nBits);
                break;
            }
             
        }
       
    }
    saveMagics(validMagicNumbers, numberOfBits, isRook);
}

void generateRookAttackMasks(AttackTables* attackTables)
{
    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        uint64_t rookPosition = 1ULL << sqInd;
        uint64_t mask = 0;

        int column = sqInd % 8;
        int row = sqInd / 8;
        
        for (int l = 1; l < column; l++)
        {
            mask |= rookPosition >> l;
        }

        for (int r = 1; r < 7 - column; r++)
        {
            mask |= rookPosition << r;
        }

        for (int u = 1; u < row; u++)
        {
            mask |= rookPosition >> (u * 8);
        }

        for (int d = 1; d < 7 - row; d++)
        {
            mask |= rookPosition << (d * 8);
        }

        attackTables->rookMagicHashTable[sqInd].mask = mask;
        attackTables->rookMagicHashTable[sqInd].shift = BOARD_SIZE - numberOfRookMovementBits(sqInd);
        
    }
    
}

void generateRookAttack(uint64_t blockers, int rookSqInd)
{
    BlockerAttackPattern newPattern;

    int column = rookSqInd % 8;
    int row = rookSqInd / 8;

    int left = column;
    int right = 7 - column;
    int up = 7 - row;
    int down = row;

    uint64_t attackMask = 0;
    
    for (int l = 1; l <= left; l++)
    {
        uint64_t sq = 1ULL << (rookSqInd - l);
        attackMask |= sq;
        if (sq & blockers)
        {
            break;
        }
        
    }

    for (int r = 1; r <= right; r++)
    {
        uint64_t sq = 1ULL << (rookSqInd + r);
        attackMask |= sq;

        if (sq & blockers)
        {
            break;
        }
    }

    for (int d = 1; d <= down; d++)
    {
        uint64_t sq = 1ULL << (rookSqInd - d * 8);
        attackMask |= sq;
        if (sq & blockers)
        {
            break;
        }
    }

    for (int u = 1; u <= up; u++)
    {
        uint64_t sq = 1ULL << (rookSqInd + u * 8);
        attackMask |= sq;

        if (sq & blockers)
        {
            break;
        }
    }

    newPattern.attackPattern = attackMask;
    newPattern.blockerPattern = blockers;
    attackPatterns[rookSqInd][attackPatternCounter] = newPattern;
    attackPatternCounter++;
}

void generateDownRookBlockers(uint64_t blockers, int sqInd, int blockerInd, int down)
{
    if (down <= 0)
    {
        generateRookAttack(blockers, sqInd);
        return;
    }
    
    int nextBlockerInd = blockerInd - 8;
    generateDownRookBlockers(blockers, sqInd, nextBlockerInd, down - 1);

    uint64_t newBlocker = blockers | (1ULL << nextBlockerInd);

    generateDownRookBlockers(newBlocker, sqInd, nextBlockerInd, down - 1);      

}

void generateUpRookBlockers(uint64_t blockers, int sqInd, int blockerInd, int up, int down)
{
    if (up <= 0)
    {
        generateDownRookBlockers(blockers, sqInd, sqInd, down);
        return;
    }
    
    int nextBlockerInd = blockerInd + 8;
    generateUpRookBlockers(blockers, sqInd, nextBlockerInd, up - 1, down);

    uint64_t newBlocker = blockers | (1ULL << nextBlockerInd);

    generateUpRookBlockers(newBlocker, sqInd, nextBlockerInd, up - 1, down);      

}

void generateRightRookBlockers(uint64_t blockers, int sqInd, int blockerInd, int right, int up, int down)
{
    if (right <= 0)
    {
        generateUpRookBlockers(blockers, sqInd, sqInd, up, down);
        return;
    }
    
    int nextBlockerInd = blockerInd + 1;
    generateRightRookBlockers(blockers, sqInd, nextBlockerInd, right - 1, up, down);

    uint64_t newBlocker = blockers | (1ULL << nextBlockerInd);

    generateRightRookBlockers(newBlocker, sqInd, nextBlockerInd, right - 1, up, down);      

}

void generateLeftRookBlockers(uint64_t blockers, int sqInd, int blockerInd, int left, int right, int up, int down)
{
    if (left <= 0)
    {
        generateRightRookBlockers(blockers, sqInd, sqInd, right, up, down);
        return;
    }
    
    int nextBlockerInd = blockerInd - 1;
    generateLeftRookBlockers(blockers, sqInd, nextBlockerInd, left - 1, right, up, down);

    uint64_t newBlocker = blockers | (1ULL << nextBlockerInd);

    generateLeftRookBlockers(newBlocker, sqInd, nextBlockerInd, left - 1, right, up, down);      

}

void loadRookAttacks(AttackTables* attackTables)
{
    uint64_t magicNumbers[64];
    int numOfBits[64];
    unsigned long long magicNumber;
    int nBits;
    int sq;

    FILE* file = fopen("magics/rookMagics.csv", "r");
    if (!file)
    {
        printf("Failed to open file\n");
        return;
    }

    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        fscanf(file, "%d,%d,%llu\n", &sq, &nBits, &magicNumber);
        magicNumbers[sq] = (uint64_t)magicNumber;
        numOfBits[sq] = nBits;
    }

    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        int shift = 64 - numOfBits[sqInd];
        magicNumber = magicNumbers[sqInd];
        attackTables->rookAttacks[sqInd] = malloc(sizeof(uint64_t) * (1 << numOfBits[sqInd]));
        attackTables->rookMagicHashTable[sqInd].magicNumber = magicNumber;
        attackTables->rookMagicHashTable[sqInd].shift = shift;

        for (int variation = 0; variation < 1 << numOfBits[sqInd]; variation++)
        {
            BlockerAttackPattern pattern = attackPatterns[sqInd][variation];
            uint64_t attackPattern = pattern.attackPattern;
            uint64_t newIndex = (pattern.blockerPattern * magicNumber) >> shift;

            attackTables->rookAttacks[sqInd][newIndex] = attackPattern;
        }
        
    }
    
    fclose(file);
}

void generateRookAttackPatterns()
{
    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        int column = sqInd % 8;
        int row = sqInd / 8;

        int left = column - 1;
        int right = 6 - column;
        int up = 6 - row;
        int down = row - 1;

        attackPatternCounter = 0;

        generateLeftRookBlockers(0, sqInd, sqInd, left, right, up, down);   
    }
}

void initRookAttacks(AttackTables* attackTables)
{
    generateRookAttackMasks(attackTables);
    generateRookAttackPatterns();
    //findAndSaveMagics(1);
    loadRookAttacks(attackTables);
}

uint64_t getRookAttackPattern(int sqInd, uint64_t position, AttackTables *attackTables)
{
    MagicTableHash magicTableHash = attackTables->rookMagicHashTable[sqInd];
    uint64_t index = (position & magicTableHash.mask) * magicTableHash.magicNumber;                 
    index = index >> magicTableHash.shift;

    return attackTables->rookAttacks[sqInd][index];
}

void generateBishopAttackMasks(AttackTables* attackTables)
{
    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        uint64_t bishopPosition = 1ULL << sqInd;
        uint64_t mask = 0;

        int column = sqInd % 8;
        int row = sqInd / 8;

        int left = column;
        int right = 7 - column;
        int up = 7 - row;
        int down = row;

        int topLeft    = (up < left) ? up : left;
        int topRight   = (up < right) ? up : right;
        int bottomLeft  = (down < left) ? down : left;
        int bottomRight = (down < right) ? down : right;
        
        for (int tl = 1; tl < topLeft; tl++)
        {
            mask |= bishopPosition << (tl * 7);
        }

        for (int tr = 1; tr < topRight; tr++)
        {
            mask |= bishopPosition << (tr * 9);
        }

        for (int bl = 1; bl < bottomLeft; bl++)
        {
            mask |= bishopPosition >> (bl * 9);
        }

        for (int br = 1; br < bottomRight; br++)
        {
            mask |= bishopPosition >> (br * 7);
        }

        attackTables->bishopMagicHashTable[sqInd].mask = mask;
        attackTables->bishopMagicHashTable[sqInd].shift = BOARD_SIZE - numberOfBishopMovementBits(sqInd);
        
    }
    
}

void generateBishopAttack(uint64_t blockers, int bishopSqInd)
{
    BlockerAttackPattern newPattern;

    int column = bishopSqInd % 8;
    int row = bishopSqInd / 8;

    int left = column;
    int right = 7 - column;
    int up = 7 - row;
    int down = row;

    int topLeft    = (up < left) ? up : left;
    int topRight   = (up < right) ? up : right;
    int bottomLeft  = (down < left) ? down : left;
    int bottomRight = (down < right) ? down : right;

    uint64_t attackMask = 0;
    
    for (int tl = 1; tl <= topLeft; tl++)
    {
        uint64_t sq = 1ULL << (bishopSqInd + tl * 7);
        attackMask |= sq;
        if (sq & blockers)
        {
            break;
        }
        
    }

    for (int tr = 1; tr <= topRight; tr++)
    {
        uint64_t sq = 1ULL << (bishopSqInd + tr * 9);
        attackMask |= sq;

        if (sq & blockers)
        {
            break;
        }
    }

    for (int bl = 1; bl <= bottomLeft; bl++)
    {
        uint64_t sq = 1ULL << (bishopSqInd - bl * 9);
        attackMask |= sq;
        if (sq & blockers)
        {
            break;
        }
    }

    for (int br = 1; br <= bottomRight; br++)
    {
        uint64_t sq = 1ULL << (bishopSqInd - br * 7);
        attackMask |= sq;

        if (sq & blockers)
        {
            break;
        }
    }

    newPattern.attackPattern = attackMask;
    newPattern.blockerPattern = blockers;
    attackPatterns[bishopSqInd][attackPatternCounter] = newPattern;
    attackPatternCounter++;
}

void generateBottomRightBishopBlockers(uint64_t blockers, int sqInd, int blockerInd, int bottomRight)
{
    if (bottomRight <= 0)
    {
        generateBishopAttack(blockers, sqInd);
        return;
    }
    
    int nextBlockerInd = blockerInd - 7;
    generateBottomRightBishopBlockers(blockers, sqInd, nextBlockerInd, bottomRight - 1);

    uint64_t newBlocker = blockers | (1ULL << nextBlockerInd);

    generateBottomRightBishopBlockers(newBlocker, sqInd, nextBlockerInd, bottomRight - 1);      

}

void generateBottomLeftBishopBlockers(uint64_t blockers, int sqInd, int blockerInd, int bottomLeft, int bottomRight)
{
    if (bottomLeft <= 0)
    {
        generateBottomRightBishopBlockers(blockers, sqInd, sqInd, bottomRight);
        return;
    }
    
    int nextBlockerInd = blockerInd - 9;
    generateBottomLeftBishopBlockers(blockers, sqInd, nextBlockerInd, bottomLeft - 1, bottomRight);

    uint64_t newBlocker = blockers | (1ULL << nextBlockerInd);

    generateBottomLeftBishopBlockers(newBlocker, sqInd, nextBlockerInd, bottomLeft - 1, bottomRight);      

}

void generateTopRightBishopBlockers(uint64_t blockers, int sqInd, int blockerInd, int topRight, int bottomLeft, int bottomRight)
{
    if (topRight <= 0)
    {
        generateBottomLeftBishopBlockers(blockers, sqInd, sqInd, bottomLeft, bottomRight);
        return;
    }
    
    int nextBlockerInd = blockerInd + 9;
    generateTopRightBishopBlockers(blockers, sqInd, nextBlockerInd, topRight - 1, bottomLeft, bottomRight);

    uint64_t newBlocker = blockers | (1ULL << nextBlockerInd);

    generateTopRightBishopBlockers(newBlocker, sqInd, nextBlockerInd, topRight - 1, bottomLeft, bottomRight);      

}

void generateTopLeftBishopBlockers(uint64_t blockers, int sqInd, int blockerInd, int topLeft, int topRight, int bottomLeft, int bottomRight)
{
    if (topLeft <= 0)
    {
        generateTopRightBishopBlockers(blockers, sqInd, sqInd, topRight, bottomLeft, bottomRight);
        return;
    }
    
    int nextBlockerInd = blockerInd + 7;
    generateTopLeftBishopBlockers(blockers, sqInd, nextBlockerInd, topLeft - 1, topRight, bottomLeft, bottomRight);

    uint64_t newBlocker = blockers | (1ULL << nextBlockerInd);

    generateTopLeftBishopBlockers(newBlocker, sqInd, nextBlockerInd, topLeft - 1, topRight, bottomLeft, bottomRight);      

}

void loadBishopAttacks(AttackTables* attackTables)
{
    uint64_t magicNumbers[64];
    int numOfBits[64];
    unsigned long long magicNumber;
    int nBits;
    int sq;

    FILE* file = fopen("magics/bishopMagics.csv", "r");
    if (!file)
    {
        printf("Failed to open file\n");
        return;
    }

    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        fscanf(file, "%d,%d,%llu\n", &sq, &nBits, &magicNumber);
        magicNumbers[sq] = (uint64_t)magicNumber;
        numOfBits[sq] = nBits;
    }

    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        int shift = 64 - numOfBits[sqInd];
        magicNumber = magicNumbers[sqInd];
        attackTables->bishopAttacks[sqInd] = malloc(sizeof(uint64_t) * (1 << numOfBits[sqInd]));
        attackTables->bishopMagicHashTable[sqInd].magicNumber = magicNumber;
        attackTables->bishopMagicHashTable[sqInd].shift = shift;

        for (int variation = 0; variation < 1 << numOfBits[sqInd]; variation++)
        {
            BlockerAttackPattern pattern = attackPatterns[sqInd][variation];
            uint64_t attackPattern = pattern.attackPattern;
            uint64_t newIndex = (pattern.blockerPattern * magicNumber) >> shift;

            attackTables->bishopAttacks[sqInd][newIndex] = attackPattern;
        }
        
    }
    
    fclose(file);
}

void generateBishopAttackPatterns()
{
    for (int sqInd = 0; sqInd < BOARD_SIZE; sqInd++)
    {
        int column = sqInd % 8;
        int row = sqInd / 8;

        int left = column - 1;
        int right = 6 - column;
        int up = 6 - row;
        int down = row - 1;

        int topLeft    = (up < left) ? up : left;
        int topRight   = (up < right) ? up : right;
        int bottomLeft  = (down < left) ? down : left;
        int bottomRight = (down < right) ? down : right;

        attackPatternCounter = 0;

        generateTopLeftBishopBlockers(0, sqInd, sqInd, topLeft, topRight, bottomLeft, bottomRight);
    }
}

void initBishopAttacks(AttackTables* attackTables)
{
    generateBishopAttackMasks(attackTables);
    generateBishopAttackPatterns();
    //findAndSaveMagics(0);
    loadBishopAttacks(attackTables);
}

uint64_t getBishopAttackPattern(int sqInd, uint64_t position, AttackTables *attackTables)
{
    MagicTableHash magicTableHash = attackTables->bishopMagicHashTable[sqInd];
    uint64_t index = (position & magicTableHash.mask) * magicTableHash.magicNumber;                 
    index = index >> magicTableHash.shift;

    return attackTables->bishopAttacks[sqInd][index];
}

uint64_t getQueenAttackPattern(int sqInd, uint64_t position, AttackTables *attackTables)
{
    
    MagicTableHash magicRookTableHash = attackTables->rookMagicHashTable[sqInd];
    uint64_t lineIndex = (position & magicRookTableHash.mask) * magicRookTableHash.magicNumber;                 
    lineIndex = lineIndex >> magicRookTableHash.shift;

    uint64_t lineAttacks = attackTables->rookAttacks[sqInd][lineIndex];

    MagicTableHash magicBishopTableHash = attackTables->bishopMagicHashTable[sqInd];
    uint64_t diagonalIndex = (position & magicBishopTableHash.mask) * magicBishopTableHash.magicNumber;                 
    diagonalIndex = diagonalIndex >> magicBishopTableHash.shift;

    uint64_t diagonalAttacks = attackTables->bishopAttacks[sqInd][diagonalIndex];

    return lineAttacks | diagonalAttacks;
}

uint8_t getAttackedPieceFromSquare(uint64_t sq, uint8_t isAttackerBlack, ChessBoard *chessBoard)
{
    uint64_t enemyPawns = chessBoard->blackPawns;
    uint64_t enemyKnights = chessBoard->blackKnights; 
    uint64_t enemyBishops = chessBoard->blackBishops; 
    uint64_t enemyRooks = chessBoard->blackRooks; 
    uint64_t enemyQueens = chessBoard->blackQueens;
    
    if (isAttackerBlack)
    {
        enemyPawns = chessBoard->whitePawns;
        enemyKnights = chessBoard->whiteKnights; 
        enemyBishops = chessBoard->whiteBishops; 
        enemyRooks = chessBoard->whiteRooks; 
        enemyQueens = chessBoard->whiteQueens;
    }

    if (enemyPawns & sq)
    {
        return pawnCaptured << captureFlagPostion;
    }
    
    if (enemyKnights & sq)
    {
        return knightCaptured << captureFlagPostion;
    }

    if (enemyBishops & sq)
    {
        return bishopCaptured << captureFlagPostion;
    }

    if (enemyRooks & sq)
    {
        return rookCaptured << captureFlagPostion;
    }

    if (enemyQueens & sq)
    {
        return queenCaptured << captureFlagPostion;
    }

    return 0;
}

uint8_t getSqInd(uint64_t sq)
{
    return __builtin_ctzll(sq);
}

uint8_t isBlack(ChessBoard *chessBoard)
{
    return chessBoard->flags & colorMask;
}

uint8_t canWhiteShortCastle(ChessBoard *chessBoard)
{
    return chessBoard->flags & whiteShortCastleMask;
}

uint8_t canWhiteLongCastle(ChessBoard *chessBoard)
{
    return chessBoard->flags & whiteLongCastleMask;
}

uint8_t canBlackShortCastle(ChessBoard *chessBoard)
{
    return chessBoard->flags & blackShortCastleMask;
}

uint8_t canBlackLongCastle(ChessBoard *chessBoard)
{
    return chessBoard->flags & blackLongCastleMask;
}

int isSquareAttacked(uint8_t sqInd, ChessBoard *chessBoard, AttackTables *attackTables, int isAttackedByWhite)
{
    uint64_t enemyKnights = chessBoard->blackKnights;
    uint64_t enemyBishops = chessBoard->blackBishops;
    uint64_t enemyRooks = chessBoard->blackRooks;
    uint64_t enemyQueens = chessBoard->blackQueens;
    uint64_t enemyPawns = chessBoard->blackPawns;
    uint64_t enemyKing = chessBoard->blackKing;
    uint64_t *friendlyPawnAttacks = attackTables->whitePanwsAttacks;

    if (isAttackedByWhite)
    {
        enemyKnights = chessBoard->whiteKnights;
        enemyBishops = chessBoard->whiteBishops;
        enemyRooks = chessBoard->whiteRooks;
        enemyQueens = chessBoard->whiteQueens;
        enemyPawns = chessBoard->whitePawns;
        enemyKing = chessBoard->whiteKing;
        friendlyPawnAttacks = attackTables->blackPanwsAttacks;

    }
    
    if (attackTables->knightAttacks[sqInd] & enemyKnights)
    {
        return 1;
    }

    if (attackTables->kingAttacks[sqInd] & enemyKing)
    {
        return 1;
    }

    uint64_t bishopAndQueenAttacks = getBishopAttackPattern(sqInd, chessBoard->allPieces, attackTables);

    if ((bishopAndQueenAttacks & enemyBishops) || (bishopAndQueenAttacks & enemyQueens))
    {
        return 1;
    }

    uint64_t rookAndQueenAttacks = getRookAttackPattern(sqInd, chessBoard->allPieces, attackTables);
    
    if ((rookAndQueenAttacks & enemyRooks) || (rookAndQueenAttacks & enemyQueens))
    {
        return 1;
    }

    if (friendlyPawnAttacks[sqInd] & enemyPawns)
    {
        return 1;
    }

    return 0;
}

void addMove(uint8_t from, uint8_t to, uint8_t flags, MoveList* moveList)
{
    moveList->moves[moveList->nextIndex] = (Move){ from, to, flags };
    moveList->nextIndex++;
}

void generatePawnPromotionMoves(uint8_t from, uint8_t to, uint8_t flags, MoveList* moveList)
{
    for (int i = 0; i < numOfPromotionPieces; i++)
    {
        addMove(from, to, flags + i, moveList);
    }
    
}

void generateKingMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint64_t kingPositions = chessBoard->whiteKing;
    uint64_t friendlyPieces = chessBoard->whitePieces;
    uint64_t enemyPieces = chessBoard->blackPieces;

    if (isBlack(chessBoard))
    {
        kingPositions = chessBoard->blackKing;
        friendlyPieces = chessBoard->blackPieces;
        enemyPieces = chessBoard->whitePieces;
    }  
    
    uint8_t fromSq =  getSqInd(kingPositions & -kingPositions);
    uint64_t kingAttacks = attackTables->kingAttacks[fromSq];
    kingAttacks &= ~friendlyPieces;

    while (kingAttacks != 0)
    {
        uint64_t nextKingAttack = kingAttacks & -kingAttacks;
        uint8_t toSq = getSqInd(nextKingAttack);

        if (nextKingAttack & enemyPieces)
        {
            uint8_t capturedPieceFlag = getAttackedPieceFromSquare(nextKingAttack, isBlack(chessBoard), chessBoard);
            addMove(fromSq, toSq, capturedPieceFlag, moveList);    
        }else
        {
            addMove(fromSq, toSq, 0, moveList);
        }
        
        kingAttacks &= kingAttacks - 1;
    }
}

void generateKnightMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint64_t knightPositions = chessBoard->whiteKnights;
    uint64_t friendlyPieces = chessBoard->whitePieces;
    uint64_t enemyPieces = chessBoard->blackPieces;

    if (isBlack(chessBoard))
    {
        knightPositions = chessBoard->blackKnights;
        friendlyPieces = chessBoard->blackPieces;
        enemyPieces = chessBoard->whitePieces;
    }  
    
    while (knightPositions != 0)
    {
        uint8_t fromSq =  getSqInd(knightPositions & -knightPositions);
        uint64_t knightAttacks = attackTables->knightAttacks[fromSq];
        knightAttacks &= ~friendlyPieces;

        while (knightAttacks != 0)
        {
            uint64_t nextKnightAttack = knightAttacks & -knightAttacks;
            uint8_t toSq = getSqInd(nextKnightAttack);
            if (nextKnightAttack & enemyPieces)
            {
                uint8_t capturedPieceFlag = getAttackedPieceFromSquare(nextKnightAttack, isBlack(chessBoard), chessBoard);
                addMove(fromSq, toSq, capturedPieceFlag, moveList);
            }else
            {
                addMove(fromSq, toSq, 0, moveList);
            }
            
            knightAttacks &= knightAttacks - 1;
        }

        knightPositions &= knightPositions - 1;
    }
}

void generateBishopMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint64_t bishopPositions = chessBoard->whiteBishops;
    uint64_t friendlyPieces = chessBoard->whitePieces;
    uint64_t enemyPieces = chessBoard->blackPieces;

    if (isBlack(chessBoard))
    {
        bishopPositions = chessBoard->blackBishops;
        friendlyPieces = chessBoard->blackPieces;
        enemyPieces = chessBoard->whitePieces;
    }  
    
    while (bishopPositions != 0)
    {
        uint8_t fromSq = getSqInd(bishopPositions & -bishopPositions);
        uint64_t bishopAttacks = getBishopAttackPattern(fromSq, chessBoard->allPieces, attackTables);
        bishopAttacks &= ~friendlyPieces;

        while (bishopAttacks != 0)
        {
            uint64_t nextBishopAttack = bishopAttacks & -bishopAttacks;
            uint8_t toSq = getSqInd(nextBishopAttack);
            if (nextBishopAttack & enemyPieces)
            {
                uint8_t capturedPieceFlag = getAttackedPieceFromSquare(nextBishopAttack, isBlack(chessBoard), chessBoard);
                addMove(fromSq, toSq, capturedPieceFlag, moveList);
            }else
            {
                addMove(fromSq, toSq, 0, moveList);
            }
            
            bishopAttacks &= bishopAttacks - 1;
        }

        bishopPositions &= bishopPositions - 1;
    }
}

void generateQueenMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint64_t queenPositions = chessBoard->whiteQueens;
    uint64_t friendlyPieces = chessBoard->whitePieces;
    uint64_t enemyPieces = chessBoard->blackPieces;

    if (isBlack(chessBoard))
    {
        queenPositions = chessBoard->blackQueens;
        friendlyPieces = chessBoard->blackPieces;
        enemyPieces = chessBoard->whitePieces;
    }  
    
    while (queenPositions != 0)
    {
        uint8_t fromSq = getSqInd(queenPositions & -queenPositions);
        uint64_t queenAttacks = getQueenAttackPattern(fromSq, chessBoard->allPieces, attackTables);
        queenAttacks &= ~friendlyPieces;

        while (queenAttacks != 0)
        {
            uint64_t nextQueenAttack = queenAttacks & -queenAttacks;
            uint8_t toSq = getSqInd(nextQueenAttack);
            if (nextQueenAttack & enemyPieces)
            {
                uint8_t capturedPieceFlag = getAttackedPieceFromSquare(nextQueenAttack, isBlack(chessBoard), chessBoard);
                addMove(fromSq, toSq, capturedPieceFlag, moveList);
            }else
            {
                addMove(fromSq, toSq, 0, moveList);
            }
            
            queenAttacks &= queenAttacks - 1;
        }

        queenPositions &= queenPositions - 1;
    }
}

void generatePawnMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint64_t pawnPositions = chessBoard->whitePawns;
    uint64_t enemyPieces = chessBoard->blackPieces;
    uint64_t *pawnAttackTable = attackTables->whitePanwsAttacks;
    uint64_t promotionLine = line8;

    if (isBlack(chessBoard))
    {
        pawnPositions = chessBoard->blackPawns;
        enemyPieces = chessBoard->whitePieces;
        pawnAttackTable = attackTables->blackPanwsAttacks;
        promotionLine = line1;
    }  
    
    while (pawnPositions != 0)
    {   
        uint64_t fromBitBoard = pawnPositions & -pawnPositions;
        uint8_t fromSq = getSqInd(fromBitBoard);

        if (isBlack(chessBoard))
        {
            uint64_t nextSq = fromBitBoard >> 8;
            if (nextSq & (~chessBoard->allPieces))
            {
                if (nextSq & promotionLine)
                {
                    generatePawnPromotionMoves(fromSq, getSqInd(nextSq), 0, moveList);
                }else
                {
                    addMove(fromSq, getSqInd(nextSq), 0, moveList);
                }

                if (fromBitBoard & line7 && ((fromBitBoard >> 16) & (~chessBoard->allPieces)))
                {
                    addMove(fromSq, getSqInd(fromBitBoard >> 16), 0, moveList);
                }
            }
                    
        }else
        {
            uint64_t nextSq = fromBitBoard << 8;
            if (nextSq & (~chessBoard->allPieces))
            {
                if (nextSq & promotionLine)
                {
                    generatePawnPromotionMoves(fromSq, getSqInd(nextSq), 0, moveList);
                }else
                {
                    addMove(fromSq, getSqInd(nextSq), 0, moveList);
                }

                if (fromBitBoard & line2 && ((fromBitBoard << 16) & (~chessBoard->allPieces)))
                {
                    addMove(fromSq, getSqInd(fromBitBoard << 16), 0, moveList);
                }
            } 
        }
        
        uint64_t pawnAttacks = pawnAttackTable[fromSq];

        while (pawnAttacks != 0)
        {   
            uint64_t nextPawnAttack = pawnAttacks & -pawnAttacks;
            uint8_t toSq = getSqInd(nextPawnAttack);

            if (nextPawnAttack & enemyPieces)
            {
                uint8_t capturedPieceFlag = getAttackedPieceFromSquare(nextPawnAttack, isBlack(chessBoard), chessBoard);
                if (nextPawnAttack & promotionLine)
                {
                    generatePawnPromotionMoves(fromSq, toSq, capturedPieceFlag, moveList);
                }else
                {
                    addMove(fromSq, toSq, capturedPieceFlag, moveList);
                }
                 
            }

            if (chessBoard->enPassantSq & nextPawnAttack)
            {
                uint8_t flags = (pawnCaptured << captureFlagPostion) | (1 << enPassantFlagPosition);
                addMove(fromSq, toSq, flags, moveList);
            }
            
            pawnAttacks &= pawnAttacks - 1;
        }

        pawnPositions &= pawnPositions - 1;
    }
}

void generateRookMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    uint64_t rookPositions = chessBoard->whiteRooks;
    uint64_t friendlyPieces = chessBoard->whitePieces;
    uint64_t enemyPieces = chessBoard->blackPieces;

    if (isBlack(chessBoard))
    {
        rookPositions = chessBoard->blackRooks;
        friendlyPieces = chessBoard->blackPieces;
        enemyPieces = chessBoard->whitePieces;
    }  
    
    while (rookPositions != 0)
    {
        uint8_t fromSq = getSqInd(rookPositions & -rookPositions);
        uint64_t rookAttacks = getRookAttackPattern(fromSq, chessBoard->allPieces, attackTables);
        rookAttacks &= ~friendlyPieces;

        while (rookAttacks != 0)
        {
            uint64_t nextRookAttack = rookAttacks & -rookAttacks;
            uint8_t toSq = getSqInd(nextRookAttack);
            if (nextRookAttack & enemyPieces)
            {
                uint8_t capturedPieceFlag = getAttackedPieceFromSquare(nextRookAttack, isBlack(chessBoard), chessBoard);
                addMove(fromSq, toSq, capturedPieceFlag, moveList);
            }else
            {
                addMove(fromSq, toSq, 0, moveList);   
            } 
            
            rookAttacks &= rookAttacks - 1;
        }

        rookPositions &= rookPositions - 1;
    }
}

void generateCastleMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    if (isBlack(chessBoard))
    {
        uint8_t kingSqInd = getSqInd(e8);

        if (canBlackShortCastle(chessBoard))
        {
            if (!(chessBoard->allPieces & f8) && !(chessBoard->allPieces & g8) && 
                !isSquareAttacked(kingSqInd, chessBoard, attackTables, 1) && 
                !isSquareAttacked(getSqInd(f8), chessBoard, attackTables, 1) && 
                !isSquareAttacked(getSqInd(g8), chessBoard, attackTables, 1))
            {
                addMove(kingSqInd, getSqInd(g8), 1 << castleFlagPostion, moveList);
            }
                
        }

        if (canBlackLongCastle(chessBoard))
        {
            if (!(chessBoard->allPieces & b8) && !(chessBoard->allPieces & c8) && !(chessBoard->allPieces & d8) && 
                !isSquareAttacked(kingSqInd, chessBoard, attackTables, 1) && 
                !isSquareAttacked(getSqInd(c8), chessBoard, attackTables, 1) &&  
                !isSquareAttacked(getSqInd(d8), chessBoard, attackTables, 1)) 
            {
                addMove(kingSqInd, getSqInd(c8), 1 << castleFlagPostion, moveList);
            }    
        }
    }else
    {
        uint8_t kingSqInd = getSqInd(e1);
        
        if (canWhiteShortCastle(chessBoard))
        {
            if (!(chessBoard->allPieces & f1) && !(chessBoard->allPieces & g1) && 
                !isSquareAttacked(kingSqInd, chessBoard, attackTables, 0) && 
                !isSquareAttacked(getSqInd(f1), chessBoard, attackTables, 0) && 
                !isSquareAttacked(getSqInd(g1), chessBoard, attackTables, 0))
            {
                addMove(kingSqInd, getSqInd(g1), 1 << castleFlagPostion, moveList);
            }    
        }

        if (canWhiteLongCastle(chessBoard))
        {
            if (!(chessBoard->allPieces & b1) && !(chessBoard->allPieces & c1) && !(chessBoard->allPieces & d1) && 
                !isSquareAttacked(kingSqInd, chessBoard, attackTables, 0) && 
                !isSquareAttacked(getSqInd(c1), chessBoard, attackTables, 0) &&  
                !isSquareAttacked(getSqInd(d1), chessBoard, attackTables, 0)) 
            {
                addMove(kingSqInd, getSqInd(c1), 1 << castleFlagPostion, moveList);
            } 
        }
    }
    
}

void generateMoves(ChessBoard *chessBoard, AttackTables *attackTables, MoveList *moveList)
{
    generateKnightMoves(chessBoard, attackTables, moveList);
    generateKingMoves(chessBoard, attackTables, moveList);
    generateBishopMoves(chessBoard, attackTables, moveList);
    generateRookMoves(chessBoard, attackTables, moveList);
    generateQueenMoves(chessBoard, attackTables, moveList);
    generatePawnMoves(chessBoard, attackTables, moveList);
    generateCastleMoves(chessBoard, attackTables, moveList);
}

AttackTables* initAttackTables()
{
    AttackTables* attackTables = malloc(sizeof(AttackTables));

    initBlackPawnAttacks(attackTables);
    initWhitePawnAttacks(attackTables);
    initKnightAttacks(attackTables);
    initKingAttacks(attackTables);
    initRookAttacks(attackTables);
    initBishopAttacks(attackTables);
    
    return attackTables;
}