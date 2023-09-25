#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

//void increment (int **p, int count) {
//    int *c = realloc(*p, 2 * (sizeof(*p)));
//    if (!c) {
//        free (*p);
//        *p = NULL;
//        return;
//    } else {
//        *p = c;
//    }
//}

void push(int *p, int num, int index, int count) {
//    if (index + 1 == ((count)/2)) {
//        increment(&p, count);
//    }
    *(p + index) = num;
    //printf("This is the current index: %d", *index);

    // check if number is being pushed properly
    //printf("number pushed is: %d \n", num);
}

int main(int argc, char **argv) {

    if (argc != 2) {
        return EXIT_FAILURE;
    }

    int *ptr = (int *) malloc(6 * (sizeof(int)));

    char* input = argv[1];
    // check if input is taking argv correctly
    //printf("%s \n", input);

    // correct length is being measured for the loop
    int length = strlen(input);
    //printf("%d \n", length);

    int num = 0;
    int index = 0;
    int count = 6;
    int x;
    //int digit;

    char lastdigit = argv[1][length-1];
    if (lastdigit != 'x' && lastdigit != '+' && lastdigit != '-' &&lastdigit != '/') {
        printf("The input does not end with an operator.\n");
        return EXIT_FAILURE;
    }

    int *c;
    for (int i = 0; i <length; i++) {
        char curr = argv[1][i];

        // print out each individual characters of the string; first one prints correctly but not the rest
        //printf("%c \n", curr);

        // check if is digit is working correctly on bool
        //printf("%d \n", digit);
        if (isdigit(curr) != 0) {
            x = curr - '0';
            //printf("%d \n", x);

            num = num * 10 + x;
            //printf("%d \n", num);
        }

        else if (curr == ',') {
            push(ptr, num, index, count);
            index ++;
            if (count / 3 == (index)) {
                count = count * 3;
                c = realloc(ptr, 3 * (sizeof(ptr)));
                if (!c) {
                    free (ptr);
                    ptr = NULL;
                } else {
                    ptr = c;
                }
            }
            //printf("%d ", num);
            num = 0;
        }

        else {

            if (isdigit(argv[1][i-1]) != 0) {
                push(ptr, num, index, count);
                //printf("%d ", index);
                index ++;
                if (count / 3 == (index)) {
                    count = count * 3;
                    c = realloc(ptr, 3 * (sizeof(ptr)));
                    if (!c) {
                        free (ptr);
                        ptr = NULL;
                    } else {
                        ptr = c;
                    }
                }
                //printf("%d", index);
                //printf("%d", num);
                num = 0;
            }

            if (index < 2) {
                printf("You do not have enough numbers for operation.\n");
                return EXIT_FAILURE;
            }

            index --;
            int num1 = *(ptr+index);
            //ptr[index] = 0;
            //printf("The index of num 1 is: %d, num 1 is: %d \n", (index), num1);
            index --;
            int num2 = *(ptr+index);
            //ptr[index] = 0;
            //printf("The index of num 2 is: %d, num 2 is: %d \n", (index), num2);
            int val;

            switch (curr) {
                case '+' :
                    val = num2 + num1;
                    break;
                case '-' :
                    val = num2 - num1;
                    break;
                case 'x' :
                    val = num2 * num1;
                    break;
                case '/':
                    if (num1 == 0) {
                        printf("Cannot divide by zero.\n");
                        return EXIT_FAILURE;
                    } else {
                        val = num2 / num1;
                    }
                    break;
            }
            //printf("\n%d", val);
            push(ptr, val, index, count);
            index ++;
            if (count / 3 == index) {
                count = count * 3;
                c = realloc(ptr, 3 * (sizeof(ptr)));
                if (!c) {
                    free (ptr);
                    ptr = NULL;
                } else {
                    ptr = c;
                }
            }
        }
    }

    if (index != 1) {
        printf("You do not have enough operators.\n");
        return EXIT_FAILURE;
    } else {
        printf("%d\n",ptr[0]);
        free(ptr);
        return EXIT_SUCCESS;
    }
}