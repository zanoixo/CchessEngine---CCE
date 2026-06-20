#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ChessBoard.h"
#include "ChessEval.h"
#include "ChessMoveGenerator.h"
#include "ChessUtils.h"
#include "ChessTests.h"
#include "ChessTranspositionTables.h"

#define MAX_LINE 2048

Move userMove(char* from, char* to, char promotion, ChessBoard* chessBoard, AttackTables* attackTables, TranspositionTableHashes* hashes)
{
    uint16_t promotionFlag = 0;

    uint8_t fromFile = from[0] - 'a';
    uint8_t fromRank = from[1] - '1';

    uint8_t toFile = to[0] - 'a';
    uint8_t toRank = to[1] - '1';

    uint8_t fromSq = fromRank * 8 + fromFile;
    uint8_t toSq = toRank * 8 + toFile;

    uint64_t fromBitboard = 1ULL << fromSq;
    uint64_t toBitboard = 1ULL << toSq;

    switch (promotion)
    {
        case 'q':
            promotionFlag |= queenPromotion;
            break;
        case 'r':
            promotionFlag |= rookPromotion;
            break;
        case 'k':
            promotionFlag |= knightPromotion;
            break;
        case 'b':
            promotionFlag |= bishopPromotion;
            break;
        default:
            break;
    }

    MoveList* moveList = malloc(sizeof(MoveList));
    moveList->moves = malloc(sizeof(Move) * 256);
    moveList->nextIndex = 0;

    Move *playedMove = NULL;

    generateMoves(chessBoard, attackTables, moveList);

    for (int i = 0; i < moveList->nextIndex; i++)
    {
        if (fromBitboard == moveList->moves[i].from && toBitboard == moveList->moves[i].to && promotionFlag == (moveList->moves[i].flags & promotionPieceMask))
        {
            playedMove = &moveList->moves[i];
            break;
        }
            
    }

    if (playedMove == NULL)
    {
        free(moveList->moves);
        free(moveList);
        return *playedMove;   
    }
    

    makeMove(chessBoard, playedMove, hashes);

    free(moveList->moves);
    free(moveList);

    return *playedMove;
}

void bestMove(char* moveStr, ChessBoard *ChessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes, uint64_t timePerMove)
{
    
    MoveScore best = evaluate(ChessBoard, attackTables, hashes, timePerMove);

    int fromSq = getSqInd(best.move.from);
    int toSq   = getSqInd(best.move.to);

    moveStr[0] = 'a' + (fromSq % 8);
    moveStr[1] = '1' + (fromSq / 8);

    moveStr[2] = 'a' + (toSq % 8);
    moveStr[3] = '1' + (toSq / 8);

    if (getPromotionPiece(best.move.flags))
    {
        switch (getPromotionPiece(best.move.flags))
        {
            case queen:
                moveStr[4] = 'q';
                break;

            case rook:
                moveStr[4] = 'r';
                break;

            case bishop:
                moveStr[4] = 'b';
                break;

            case knight:
                moveStr[4] = 'n';
                break;

            default:
                moveStr[4] = 'q';
                break;
        }

        moveStr[5] = '\0';
    }
    else
    {
        moveStr[4] = '\0';
    }
        
}

void applyUCIMoves(char *moves, ChessBoard *chessBoard, AttackTables *attackTables, TranspositionTableHashes* hashes)
{
    char *token = strtok(moves, " ");

    char from[1024][3];
    char to[1024][3];
    char promotion[1024];

    int count = 0;

    while (token)
    {
        if (strlen(token) >= 4)
        {
            from[count][0] = token[0];
            from[count][1] = token[1];
            from[count][2] = '\0';

            to[count][0] = token[2];
            to[count][1] = token[3];
            to[count][2] = '\0';

            promotion[count] = 0;

            if (strlen(token) == 5)
                promotion[count] = token[4];

            count++;
        }

        token = strtok(NULL, " ");
    }

    for (int i = 0; i < count; i++)
    {
        userMove(from[i], to[i], promotion[i], chessBoard, attackTables, hashes);
    }
}

void uci_loop()
{
    char line[MAX_LINE];
    uint64_t timePerMove = 10000;

    ChessBoard* chessBoard = initChessBoard();
    AttackTables* attackTables = initAttackTables();
    TranspositionTableHashes* hashes = initTranpositionTableHashes();

    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    while (fgets(line, sizeof(line), stdin))
    {
        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, "uci") == 0)
        {
            printf("id name CCE\n");
            printf("id author Zan Hribar\n");
            printf("uciok\n");
            fflush(stdout);
        }

        else if (strcmp(line, "isready") == 0)
        {
            printf("readyok\n");
            fflush(stdout);
        }

        else if (strncmp(line, "position startpos", 17) == 0) 
        { 
            initStartingPosition(chessBoard, hashes);
            char *moves = strstr(line, "moves"); 
            if (moves)
            { 
                moves += 6; 
                applyUCIMoves(moves, chessBoard, attackTables, hashes); 
            } 
        } 
        
        else if (strncmp(line, "go", 2) == 0) 
        { 
            char *ptr;

            if ((ptr = strstr(line, "movetime")))
            {
                timePerMove = strtoull(ptr + 9, NULL, 10);
            }
                
            char moveStr[6];
            bestMove(moveStr, chessBoard, attackTables, hashes, timePerMove);
            printf("bestmove %s\n", moveStr);
            fflush(stdout); 
        }

        else if (strcmp(line, "quit") == 0)
        {
            break;
        }
    }

    free(chessBoard);
    free(attackTables);
}

int main() {
    uci_loop();
    return 0;
}