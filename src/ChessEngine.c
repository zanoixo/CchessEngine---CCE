#include <stdio.h>
#include "ChessBoard.h"
#include "ChessMoveGenerator.h"
#include "ChessTests.h"

int main()
{
    ChessBoard *chessBoard = initChessBoard();
    AttackTables* attackTables = initAttackTables();

    char fileName[] = "startingPosition.txt";

    createPosition(fileName, chessBoard);

    printf("%llu \n", chessBoard->whiteRooks);

    runAllTests();

    return 0;
}