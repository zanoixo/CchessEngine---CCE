#include <stdio.h>

#include "ChessBoard.h"
#include "ChessUtils.h"
#include "ChessTranspositionTables.h"

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

    chessBoard->blackPieces = 0;
    chessBoard->whitePieces = 0;
    chessBoard->allPieces = 0;
    chessBoard->enPassantSq = 0;
    chessBoard->flags = 0;
    
    return chessBoard;
}

void initStartingPosition(ChessBoard *chessBoard, TranspositionTableHashes* hashes)
{
    chessBoard->whitePawns = 0b00000000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b11111111ULL << 8  |
                             0b00000000ULL;

    chessBoard->whiteKnights = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b01000010ULL;

    chessBoard->whiteBishops = 0b00000000ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00100100ULL;

    chessBoard->whiteRooks = 0b00000000ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b00000000ULL << 8  |
                             0b10000001ULL;

    chessBoard->whiteQueens = 0b00000000ULL << 56 |
                              0b00000000ULL << 48 |
                              0b00000000ULL << 40 |
                              0b00000000ULL << 32 |
                              0b00000000ULL << 24 |
                              0b00000000ULL << 16 |
                              0b00000000ULL << 8  |
                              0b00001000ULL;

    chessBoard->whiteKing = 0b00000000ULL << 56 |
                            0b00000000ULL << 48 |
                            0b00000000ULL << 40 |
                            0b00000000ULL << 32 |
                            0b00000000ULL << 24 |
                            0b00000000ULL << 16 |
                            0b00000000ULL << 8  |
                            0b00010000ULL;

    chessBoard->blackPawns = 0b00000000ULL << 56 |
                             0b11111111ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b00000000ULL << 8  |
                             0b00000000ULL;

    chessBoard->blackKnights = 0b01000010ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;

    chessBoard->blackBishops = 0b00100100ULL << 56 |
                               0b00000000ULL << 48 |
                               0b00000000ULL << 40 |
                               0b00000000ULL << 32 |
                               0b00000000ULL << 24 |
                               0b00000000ULL << 16 |
                               0b00000000ULL << 8  |
                               0b00000000ULL;

    chessBoard->blackRooks = 0b10000001ULL << 56 |
                             0b00000000ULL << 48 |
                             0b00000000ULL << 40 |
                             0b00000000ULL << 32 |
                             0b00000000ULL << 24 |
                             0b00000000ULL << 16 |
                             0b00000000ULL << 8  |
                             0b00000000ULL;

    chessBoard->blackQueens = 0b00001000ULL << 56 |
                              0b00000000ULL << 48 |
                              0b00000000ULL << 40 |
                              0b00000000ULL << 32 |
                              0b00000000ULL << 24 |
                              0b00000000ULL << 16 |
                              0b00000000ULL << 8  |
                              0b00000000ULL;

    chessBoard->blackKing = 0b00010000ULL << 56 |
                            0b00000000ULL << 48 |
                            0b00000000ULL << 40 |
                            0b00000000ULL << 32 |
                            0b00000000ULL << 24 |
                            0b00000000ULL << 16 |
                            0b00000000ULL << 8  |
                            0b00000000ULL;

    chessBoard->blackPieces = 0b11111111ULL << 56 |
                              0b11111111ULL << 48 |
                              0b00000000ULL << 40 |
                              0b00000000ULL << 32 |
                              0b00000000ULL << 24 |
                              0b00000000ULL << 16 |
                              0b00000000ULL << 8  |
                              0b00000000ULL;

    chessBoard->whitePieces = 0b00000000ULL << 56 |
                              0b00000000ULL << 48 |
                              0b00000000ULL << 40 |
                              0b00000000ULL << 32 |
                              0b00000000ULL << 24 |
                              0b00000000ULL << 16 |
                              0b11111111ULL << 8  |
                              0b11111111ULL;

    chessBoard->allPieces = 0b11111111ULL << 56 |
                            0b11111111ULL << 48 |
                            0b00000000ULL << 40 |
                            0b00000000ULL << 32 |
                            0b00000000ULL << 24 |
                            0b00000000ULL << 16 |
                            0b11111111ULL << 8  |
                            0b11111111ULL;

    chessBoard->positionHash = 0;

    for (int sq = 8; sq < 16; sq++)
    {
        chessBoard->positionHash ^= hashes->pieceHashes[whitePawnHash][sq];
    }

    for (int sq = 48; sq < 56; sq++)
    {
        chessBoard->positionHash ^= hashes->pieceHashes[blackPawnHash][sq];
    }

    chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][0];
    chessBoard->positionHash ^= hashes->pieceHashes[whiteRookHash][7];
    
    chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][56];
    chessBoard->positionHash ^= hashes->pieceHashes[blackRookHash][63];

    chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][1];
    chessBoard->positionHash ^= hashes->pieceHashes[whiteKnightHash][6];
    
    chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][57];
    chessBoard->positionHash ^= hashes->pieceHashes[blackKnightHash][62];

    chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][2];
    chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][5];
    
    chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][58];
    chessBoard->positionHash ^= hashes->pieceHashes[blackBishopHash][61];

    chessBoard->positionHash ^= hashes->pieceHashes[whiteBishopHash][3];

    chessBoard->positionHash ^= hashes->pieceHashes[blackQueenHash][60];

    chessBoard->positionHash ^= hashes->pieceHashes[whiteKingHash][4];

    chessBoard->positionHash ^= hashes->pieceHashes[blackKingHash][59];

    chessBoard->positionHash ^= hashes->castellingHashes[whiteShortCastleHash];
    chessBoard->positionHash ^= hashes->castellingHashes[whiteLongCastleHash];
    chessBoard->positionHash ^= hashes->castellingHashes[blackShortCastleHash];
    chessBoard->positionHash ^= hashes->castellingHashes[blackLongCastleHash];

    chessBoard->enPassantSq = 0;
    chessBoard->flags = whiteShortCastleMask | whiteLongCastleMask | blackShortCastleMask | blackLongCastleMask;     
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

        uint64_t square = 1ULL << squareIndex;
        pieceName = piece[1];

        if (piece[0] == 'W')
        {
            switch (pieceName)
            {
            case 'Q': chessBoard->whiteQueens |= square; break;
            case 'R': chessBoard->whiteRooks |= square; break;
            case 'N': chessBoard->whiteKnights |= square; break;
            case 'B': chessBoard->whiteBishops |= square; break;
            case 'P': chessBoard->whitePawns |= square; break;
            case 'K': chessBoard->whiteKing |= square; break;
            default: sendError("Wrong format in file");   
            }
            chessBoard->whitePieces |= square;
        } else if (piece[0] == 'B')
        {
            switch (pieceName)
            {
            case 'Q': chessBoard->blackQueens |= square; break;
            case 'R': chessBoard->blackRooks |= square; break;
            case 'N': chessBoard->blackKnights |= square; break;
            case 'B': chessBoard->blackBishops |= square; break;
            case 'P': chessBoard->blackPawns |= square; break;
            case 'K': chessBoard->blackKing |= square; break;
            default: sendError("Wrong format in file");   
            }
            chessBoard->blackPieces |= square;
        }
        squareIndex++;
    }
    chessBoard->allPieces = chessBoard->whitePieces | chessBoard->blackPieces;
}
