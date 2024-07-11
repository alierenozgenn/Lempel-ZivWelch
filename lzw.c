#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DICT_SIZE 4096
#define BYTE_SIZE 256

typedef struct {
    int code;
    char *str;
} DictionaryEntry;

DictionaryEntry *dictionary[MAX_DICT_SIZE];
int dictSize = BYTE_SIZE;

void initDictionary() {
    for (int i = 0; i < BYTE_SIZE; i++) {
        dictionary[i] = (DictionaryEntry *)malloc(sizeof(DictionaryEntry));
        dictionary[i]->code = i;
        dictionary[i]->str = (char *)malloc(2);
        dictionary[i]->str[0] = (char)i;  // Hata düzeltildi
        dictionary[i]->str[1] = '\0';
    }
}

int searchDictionary(const char *str) {
    for (int i = 0; i < dictSize; i++) {
        if (strcmp(dictionary[i]->str, str) == 0) {
            return dictionary[i]->code;
        }
    }
    return -1;
}

void addToDictionary(const char *str) {
    if (dictSize < MAX_DICT_SIZE) {
        dictionary[dictSize] = (DictionaryEntry *)malloc(sizeof(DictionaryEntry));
        dictionary[dictSize]->code = dictSize;
        dictionary[dictSize]->str = (char *)malloc(strlen(str) + 1);
        strcpy(dictionary[dictSize]->str, str);
        dictSize++;
    }
}

void compress(const char *input, int inputSize, int *output, int *outputSize) {
    initDictionary();

    char w[1024] = "";
    int k;
    int outputIndex = 0;

    for (int i = 0; i < inputSize; i++) {
        char wc[1024];
        snprintf(wc, sizeof(wc), "%s%c", w, input[i]);

        if (searchDictionary(wc) != -1) {
            strcpy(w, wc);
        } else {
            k = searchDictionary(w);
            output[outputIndex++] = k;
            addToDictionary(wc);
            snprintf(w, sizeof(w), "%c", input[i]);
        }
    }

    k = searchDictionary(w);
    output[outputIndex++] = k;

    *outputSize = outputIndex;
}

int main() {
    char input[] = "TOBEORNOTTOBEORTOBEORNOT";
    int inputSize = (int)strlen(input);  // Hata düzeltildi
    int output[1024];
    int outputSize;

    compress(input, inputSize, output, &outputSize);

    printf("Compressed output:\n");
    for (int i = 0; i < outputSize; i++) {
        printf("%d ", output[i]);
    }
    printf("\n");

    return 0;
}
