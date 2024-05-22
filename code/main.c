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

void get_coordinates(char c, int *row, int *col) {
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


int main() {
    char plaintext[] = "BERLIN";
    // char key[] = "CODE";
    
    
   
    return 0;
}