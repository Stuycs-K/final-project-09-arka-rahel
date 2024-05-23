#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 6
#define LETTERS "ADFGVX"

char polybius_square[SIZE][SIZE] = {
    {'A', 'B', 'C', 'D', 'E', 'F'},
    {'G', 'H', 'I', 'J', 'K', 'L'},
    {'M', 'N', 'O', 'P', 'Q', 'R'},
    {'S', 'T', 'U', 'V', 'W', 'X'},
    {'Y', 'Z', '0', '1', '2', '3'},
    {'4', '5', '6', '7', '8', '9'}
};

void coordinate(char c, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (polybius_square[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
char *encryptsquare(char *plaintext){
    int len =strlen(plaintext);
    char *temp = malloc(len*2+1);
    for(int i = 0; i < len; i++){
        int row;
        int col;
        coordinate(plaintext[i], &row, &col);
        temp[2 * i] = LETTERS[row];
        temp[2 * i + 1] = LETTERS[col];
    }
    temp[len * 2] = '\0';
    printf("temp: %s\n", temp);
    return temp;
}

int main() {
    char plaintext[] = "BERLIN";
    // char key[] = "CODE";
    encryptsquare(plaintext);
    
    
   
    return 0;
}