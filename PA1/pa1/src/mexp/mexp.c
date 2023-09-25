#include <stdio.h>
#include <stdlib.h>

void matrix_mult(int n, int** m1, int** m2, int** mult) {

     for (int r1 = 0; r1 < n; r1++) {
        for (int c2 = 0; c2 < n; c2++) {
            *(*(mult+r1)+c2) = 0;
            for (int c1 = 0; c1 < n; c1++) {
                *(*(mult+r1)+c2) += *(*(m1+r1)+c1) * *(*(m2+c1)+c2);
            }
        }
    }

}

void swap (int n, int** m1, int** m2) {

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            int temp1 = m1[r][c];
            int temp2 = m2[r][c];
            m1[r][c] = temp2;
            m2[r][c] = temp1;
        }
    }

}

int main(int argc, const char **argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    FILE *fptr;
    const char *name = argv[1];
    fptr = fopen(name, "r");

    if (fptr == NULL) {
        return EXIT_FAILURE;
    }

    int n;
    fscanf(fptr, "%d", &n);

    int** matrix = (int**)malloc(n*sizeof(int*));
    int** return_matrix = (int**)malloc(n*sizeof(int*));
    int** new_matrix = (int**)malloc(n *sizeof(int*));

    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n*sizeof(int)); //int*?
        return_matrix[i] = (int*)malloc(n*sizeof(int));
        new_matrix[i] = (int*)malloc(n*sizeof(int));
    }

    int row;
    int col;
    int x;

    for (row = 0; row < n; row++) {
        for (col = 0; col < n; col ++) {
            fscanf(fptr, "%d", &x);
            matrix[row][col] = x;
            return_matrix[row][col] = x;
        }
    }

    int p;
    fscanf(fptr, "%d", &p);

    if (p == 0) {
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++) {
                int val;
                if (j == i) {
                    val = 1;
                } else val = 2;

                if (j == val-1) {
                    printf("%d", val);
                } else {
                    printf("%d ", val);
                }
            }
        }
    }
    else {
        for (int i = 0; i < p; i++) {
            matrix_mult(n,matrix, return_matrix, new_matrix);
            swap(n, return_matrix, new_matrix);
        }

        for (row = 0; row < n; row++) {
            for (col = 0; col < n; col++) {
                if (col == n-1) {
                    printf("%d", new_matrix[row][col]);
                }
                else {
                    printf("%d ", new_matrix[row][col]);
                }
            }
            printf("\n");
        }
    }

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
        free(return_matrix[i]);
        free(new_matrix[i]);
    }

    free(matrix);
    free(return_matrix);
    free(new_matrix);
    fclose(fptr);
    return EXIT_SUCCESS;
}