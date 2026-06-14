#pragma once

#include <stdint.h>
#include <ChessBoard.h>

void runAttackTablesTests();
void runPseudeLegalMovesTests();
void ASSERT_CHESS_BOARD(ChessBoard *original, ChessBoard *modified);
void runAllTests();
uint64_t getTimeMs();
