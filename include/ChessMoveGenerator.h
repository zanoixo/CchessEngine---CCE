#ifndef CHESS_MOVE_GENERATOR_H

#include "ChessBoard.h"

typedef struct AttackTables
{
    uint64_t whitePanwsAttacks[64];
    uint64_t blackPanwsAttacks[64];
    uint64_t knightAttacks[64];
    uint64_t kingAttacks[64];
}AttackTables;

AttackTables* initAttackTables();

#endif