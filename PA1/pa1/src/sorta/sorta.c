#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//int findmin (char** wordarr, int length) {
//    char* min = wordarr[1];
//    int index = 0;
//    int result;
//    char* curr;
//
//    for(int i = 2; i < length; i++) {
//        curr = wordarr[i];
//        result = strcmp(min, curr);
//
//        if (result <= 0) {
//            continue;
//        }
//        else if (result > 0) {
//            min = curr;
//            index = i;
//        }
//    }
//
//    printf("%s\n", min);
//    return index;
//
//
//}

int main (int argc, char * argv[]) {

    int length = argc;
    char** word = (char**)malloc (length * sizeof(char*));

    for (int i = 1; i < length; i++) {
        word[i] = argv[i];
    }

//    while (length > 2) {
//        int index = (findmin(word, length));
//        char* temp = word[index];
//        word[index] = word[length-1];
//        word[length-1] = temp;
//        length--;
//
//    }
    char* temp;
    for (int i = 1; i < length; i++) {
        for (int j = i; j < length; j++) {
            if (strcmp(word[i], word[j]) > 0) {
                temp = word[i];
                word[i] = word[j];
                word[j] = temp;

            }
        }
    }

    for (int i = 1; i < length; i++) {
        printf("%s\n", word[i]);
    }

    free(word);

    return EXIT_SUCCESS;
}