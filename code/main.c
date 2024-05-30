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

char* text(char* file_name) { 
    FILE *file = fopen(file_name, "r");
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *text = malloc(length + 1);
    fread(text, 1, length, file);
    text[length] = 0;
    fclose(file);
    return text;
}

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

    char *tempa = malloc(len + 1);

    for (int i = 0; i < key_len; i++) {
        int col = strchr(key, sorted_key[i]) - key;
        for (int j = 0; j < num_rows; j++) {
            tempa[j * key_len + col] = ciphertext[i * num_rows + j];
        }
    }
    tempa[len] = '\0';
    printf("tempa: %s\n", tempa);
    return tempa;
}

char *decrypt(char *ciphertext, char *key) {
    char *intermediate = reverse_transpose(ciphertext, key);
    int len = strlen(intermediate);
    char *plaintext = malloc((len / 2) + 1);

    for (int i = 0; i < len / 2; i++) {
        int row = strchr(LETTERS, intermediate[2 * i]) - LETTERS;
        int col = strchr(LETTERS, intermediate[2 * i + 1]) - LETTERS;
        plaintext[i] = polybius_square[row][col];
    }
    plaintext[len / 2] = '\0';
    free(intermediate);
    return plaintext;
}

int main() {
    // char plaintext[] = "HELLOWORLDREDGREENBLUEPERMUTATIONSBRUTEFORCE"; // BERLIN
    // char key[] = "MONKEY";
    // char *ciphertext = encrypt(plaintext, key);
    // printf("ciphertext: %s\n", ciphertext);
    // free(ciphertext);

    // char ciphertext[] = "FFAFAADAFAFFDDAGADDFFFXDDDFFDXADAGAVFFGV";
    // char key[] = "CODE";
    // char *plaintext = decrypt(ciphertext, key);
    // printf("plaintext: %s\n", plaintext);
    // free(plaintext);
    char *txt = text(alice.txt);
    printf("string: %s\n", txt);

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

// DGDAFFGAGGFFAFVFXXAVXGAAFDDFVDDFAAAAAFGDGGAAAFFFDADFFAFAGFADXFGGVDVXDFAFXFXVXVXDFVFDDXVX
// DGDAFFGAGGFFAFVFXXAVXGAAFDDFVDDFAAAAAFGDGGAAAFFFDADFFAFAGFADXFGGVDVXDFAFXFXVXVXDFVFDDXVX