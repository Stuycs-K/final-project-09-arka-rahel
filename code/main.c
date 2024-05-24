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
int compare_chars(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}
char *transpose(char *intermediate, char *key) {
    int len = strlen(intermediate);
    int key_len = strlen(key);
    int num_rows = (len + key_len - 1) / key_len;

    char sorted_key[key_len + 1];
    strcpy(sorted_key, key);
    qsort(sorted_key, key_len, sizeof(char), compare_chars);

    char *transposed = malloc(len + 1);
    int transposed_index = 0;

    for (int i = 0; i < key_len; i++) {
        int col = strchr(key, sorted_key[i]) - key;
        for (int j = 0; j < num_rows; j++) {
            int index = j * key_len + col;
            if (index < len) {
                transposed[transposed_index++] = intermediate[index];
            }
        }
    }
    transposed[transposed_index] = '\0';
    return transposed;
}
char *encrypt(char *plaintext, char *key) {
    char *intermediate = encryptsquare(plaintext);
    char *ciphertext = transpose(intermediate, key);
    free(intermediate);
    return ciphertext;
}
int main() {
    char plaintext[] = "AJFBGOIAUSDBGOIADFBGOAUHFGBO";
    char key[] = "POW";
    
    char *ciphertext = encrypt(plaintext, key);
    
    printf("Ciphertext: %s\n", ciphertext);
    
    free(ciphertext);
    return 0;
}
// DDAAVAFFGAGAGFGADDDFAAVGAFDF

// DDAAVAFFGAGAGFGADDDFAAVGAFDF

// GDFGDDGDAADAAAADFAAGXFAXFAAAAXFFDFDDDFAFADADAAAFGGFAAFDA
// GDFGDDGDAADAAAADFAAGXFAXFAAAAXFFDFDDDFAFADADAAAFGGFAAFDA

// AADGDAAAAFAADGDAAAAFDDAAFADGDXFFDFXFDDGAAGFGAFAADFAAADAXF   This is with key with repeating characters
// AADGDAAAAFAFGADAFDADDAAFADGDXFFDFXFDDGAAGFGAFAADFAAADAXF

// AADFFGAAADAADFADXAFAGAADAGGDFAGAAAFAAFAGAADAGGDFAGAAAFAAF
// AADFFGAAADAADFADXAFAGAADAGGDFAGAAAFAAFDXDFAFADFFAXDFGDDD

AADFFGAAADAADFADXAFAGAADAGGDFAGAAAFAAFDXDFAFADFFAXDFGDDD
AADFFGAAADAADFADXAFAGAADAGGDFAGAAAFAAFDXDFAFADFFAXDFGDDD