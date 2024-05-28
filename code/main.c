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
char *encryptSquare(char *plaintext){
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
    char *intermediate = encryptSquare(plaintext);
    char *ciphertext = transpose(intermediate, key);
    free(intermediate);
    return ciphertext;
}
char *reverse_transpose(char *ciphertext, char *key) {
    int len = strlen(ciphertext);
    int key_len = strlen(key);
    int num_rows = len / key_len;

    char sorted_key[key_len + 1];
    strcpy(sorted_key, key);
    qsort(sorted_key, key_len, sizeof(char), compare_chars);

    char *intermediate = malloc(len + 1);

    for (int i = 0; i < key_len; i++) {
        int col = strchr(key, sorted_key[i]) - key;
        for (int j = 0; j < num_rows; j++) {
            intermediate[j * key_len + col] = ciphertext[i * num_rows + j];
        }
    }
    intermediate[len] = '\0';
    printf("Intermediate: %s\n", intermediate);
    return intermediate;
}

// char *adfgvx_decrypt(char *ciphertext, char *key) {
//     char *intermediate = reverse_transpose(ciphertext, key);
//     int len = strlen(intermediate);
//     char *plaintext = malloc((len / 2) + 1);

//     for (int i = 0; i < len / 2; i++) {
//         int row = strchr(LETTERS, intermediate[2 * i]) - LETTERS;
//         int col = strchr(LETTERS, intermediate[2 * i + 1]) - LETTERS;
//         plaintext[i] = polybius_square[row][col];
//     }
    plaintext[len / 2] = '\0';
    free(intermediate);
    return plaintext;
}

int main() {
    char ciphertext[] = "AFDADFVXDDXF"; // BERLIN
    char key[] = "CODE";

    char *plaintext = adfgvx_decrypt(ciphertext, key);
    printf("Plaintext: %s\n", plaintext);

    free(plaintext);
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

// AADFFGAAADAADFADXAFAGAADAGGDFAGAAAFAAFDXDFAFADFFAXDFGDDD
// AADFFGAAADAADFADXAFAGAADAGGDFAGAAAFAAFDXDFAFADFFAXDFGDDD