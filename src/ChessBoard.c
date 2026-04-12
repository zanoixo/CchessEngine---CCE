#include <stdio.h>
#include "ChessBoard.h"

void sendError(char errorMsg[]){

    printf("[ERROR]: %s\n", errorMsg);
    exit(1);
}

void showPosition(const ChessBoard* chessBoard)
{
    for (int rank = 7; rank >= 0; rank--)
    {
        printf("%d  ", rank + 1);

        for (int file = 0; file < 8; file++)
        {
            int square = rank * 8 + file;
            uint64_t mask = 1ULL << square;

            char piece = '.';

            if (chessBoard->whitePawns & mask) piece = 'P';
            else if (chessBoard->whiteKnights & mask) piece = 'N';
            else if (chessBoard->whiteBishops & mask) piece = 'B';
            else if (chessBoard->whiteRooks & mask) piece = 'R';
            else if (chessBoard->whiteQueens & mask) piece = 'Q';
            else if (chessBoard->whiteKing & mask) piece = 'K';

            else if (chessBoard->blackPawns & mask) piece = 'p';
            else if (chessBoard->blackKnights & mask) piece = 'n';
            else if (chessBoard->blackBishops & mask) piece = 'b';
            else if (chessBoard->blackRooks & mask) piece = 'r';
            else if (chessBoard->blackQueens & mask) piece = 'q';
            else if (chessBoard->blackKing & mask) piece = 'k';

            printf("%c ", piece);
        }

        printf("\n");
    }

    printf("   a b c d e f g h\n\n");
}

ChessBoard* initChessBoard()
{
    ChessBoard* chessBoard = malloc(sizeof(ChessBoard));

    chessBoard->whitePawns = 0;
    chessBoard->whiteKnights = 0;
    chessBoard->whiteBishops = 0;
    chessBoard->whiteRooks = 0;
    chessBoard->whiteQueens = 0;
    chessBoard->whiteKing = 0;

    chessBoard->blackPawns = 0;
    chessBoard->blackKnights = 0;
    chessBoard->blackBishops = 0;
    chessBoard->blackRooks = 0;
    chessBoard->blackQueens = 0;
    chessBoard->blackKing = 0;
    
    return chessBoard;
}

void createPosition(char fileName[], ChessBoard *chessBoard)
{
    int squareIndex = 0;

    FILE *positionFile = fopen(fileName, "r");

    if (positionFile == NULL)
    {
        sendError("failed to open file");
    }

    while (!feof(positionFile))
    {
        char piece[3];
        char pieceName;

        fscanf(positionFile, "%s", piece);

        pieceName = piece[1];

        if (piece[0] == 'W')
        {
            switch (pieceName)
            {
            case 'Q': chessBoard->whiteQueens = chessBoard->whiteQueens | (1ULL << squareIndex); break;
            case 'R': chessBoard->whiteRooks = chessBoard->whiteRooks | (1ULL << squareIndex); break;
            case 'N': chessBoard->whiteKnights = chessBoard->whiteKnights | (1ULL << squareIndex); break;
            case 'B': chessBoard->whiteBishops = chessBoard->whiteBishops | (1ULL << squareIndex); break;
            case 'P': chessBoard->whitePawns = chessBoard->whitePawns | (1ULL << squareIndex); break;
            case 'K': chessBoard->whiteKing = chessBoard->whiteKing | (1ULL << squareIndex); break;
            default: sendError("Wrong format in file");   
            }

        } else if (piece[0] == 'B')
        {
            switch (pieceName)
            {
            case 'Q': chessBoard->blackQueens = chessBoard->blackQueens | (1ULL << squareIndex); break;
            case 'R': chessBoard->blackRooks = chessBoard->blackRooks | (1ULL << squareIndex); break;
            case 'N': chessBoard->blackKnights = chessBoard->blackKnights | (1ULL << squareIndex); break;
            case 'B': chessBoard->blackBishops = chessBoard->blackBishops | (1ULL << squareIndex); break;
            case 'P': chessBoard->blackPawns = chessBoard->blackPawns | (1ULL << squareIndex); break;
            case 'K': chessBoard->blackKing = chessBoard->blackKing | (1ULL << squareIndex); break;
            default: sendError("Wrong format in file");   
            }
        }
        squareIndex++;
    }
}
