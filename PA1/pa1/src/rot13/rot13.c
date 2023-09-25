#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char **argv) {

    int num;
    char *str = argv[1];
    char c;
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    for (int i = 0; i < strlen(argv[1]); i++) {
        c = str[i];
        if (isalpha(c)) {
            num = c;
            num = num + 13;
            if (islower(c) && num > 122) {
                num = 96 + (num - 122);
            } else if (!islower(c) && num > 90) {
                num = 64 + (num - 90);
            }
            printf("%c", (char) num);
        } else {
            printf("%c", c);
        }
    }
    return EXIT_SUCCESS;
}