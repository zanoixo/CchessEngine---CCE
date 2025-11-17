#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define Q 9
#define K 127
#define R 5
#define N 3
#define B 3
#define P 1
#define E 0
#define MAXNAME 64

void sendError(char errorMsg[]){

    printf("[ERROR]: %s\n", errorMsg);
    exit(1);
}

typedef struct {

    char piece;
    int color;
    int value;
    int x;
    int y;

}chessPiece;


typedef struct {

    chessPiece position[8][8];

}chessBoard;

void showPosition(chessBoard board){

    for (int y = 0; y < 8; y++){

        for (int x = 0; x < 8; x++){

            printf("%c ", board.position[y][x].piece);
        }

        printf("\n");
    }
}

void showValue(chessBoard board){

    for (int y = 0; y < 8; y++){

        for (int x = 0; x < 8; x++){

            printf("%d ", board.position[y][x].value);
        }

        printf("\n");
    }
}


chessBoard createPosition(char fileName[]){
    
    chessBoard board;
    int pieceCounter = 0;

    FILE *positionFile = fopen(fileName, "r");

    if (positionFile == NULL){
        
        sendError("failed to open file");
    }

    while (!feof(positionFile)){

        char piece[3];
        char pieceName;
        char pieceValue;
        char pieceColor;

        fscanf(positionFile, "%s", piece);

        if (piece[0] == 'W'){

            pieceColor = 1;

        } else if (piece[0] == 'B'){

            pieceColor = -1;

        }else {

            pieceColor = 0;
        }

        pieceName = piece[1];

        switch (pieceName){
        case 'Q':
            pieceValue = Q;
            break;
        case 'R':
            pieceValue = R;
            break;
        case 'B':
            pieceValue = B;
            break;
        case 'N':
            pieceValue = N;
            break;
        case 'P':
            pieceValue = P;
            break;
        case 'K':
            pieceValue = K;
            break;
        case '0':
            pieceValue = 0;
            break;
        default:
            sendError("Wrong format in file");
        }

        pieceValue = pieceColor * pieceValue;

        board.position[pieceCounter / 8][pieceCounter % 8].piece = pieceName;
        board.position[pieceCounter / 8][pieceCounter % 8].color = pieceColor;
        board.position[pieceCounter / 8][pieceCounter % 8].value = pieceValue;
        board.position[pieceCounter / 8][pieceCounter % 8].x = pieceCounter % 8;
        board.position[pieceCounter / 8][pieceCounter % 8].y = pieceCounter / 8;

        pieceCounter++;

    }
    
    return board;
    
}

int main(int argc, char const *argv[]){

    chessBoard startingPosition = createPosition("startingPosition.txt");
    showPosition(startingPosition);
    showValue(startingPosition);

    return 0;
}
