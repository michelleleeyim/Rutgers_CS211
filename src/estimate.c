#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

double** transpose(double** m, int row, int col) {
    // output the transpose of the given matrix m 
    double **transpose = (double**)malloc(col * sizeof(double*));
    for (int i = 0; i < col; i++) {
        *(transpose+i) = (double*)malloc(row*sizeof(double));
    }

    double x;
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            x = *(*(m+j)+i);
            *(*(transpose+i)+j) = x;
        }
    }

    return transpose;
}

double** multiply(double **m1, int rm1, int cm1, double **m2, int cm2) {
    // output the multiple of two given matrices m1 and m2

    double **mult = (double**)malloc(rm1*sizeof(double*));

    for (int i = 0; i <rm1; i++) {
        *(mult+i) = (double*)malloc(cm2 * sizeof(double));
    }


    for (int r1 = 0; r1 < rm1; r1++) {
        for (int c2 = 0; c2 < cm2; c2++) {
            *(*(mult+r1)+c2) = 0;
            for (int c1 = 0; c1 < cm1; c1++) {
                *(*(mult+r1)+c2) += *(*(m1+r1)+c1) * *(*(m2+c1)+c2);
            }
        }
    }
    return mult;
}
//row multiplication and addition functions for elementary matrix operations 
void row_mult(double **M, double c, int r, int n) {
    for (int i = 0; i < n; i++) {
        *(*(M+r)+i) = *(*(M+r)+i) * c;
    }
}

void row_add(double **M, int r1, int r2, int r3, int n, double m1) {
    for (int i = 0; i < n; i++) {
        *(*(M+r3)+i) = (m1 * *(*(M+r1)+i)) + *(*(M+r2)+i);
    }
}

double** inverse(double** M, int n) {
    // return the inverse of given matrix M
    double **A = (double**)malloc(n*sizeof(double*));

    for (int i = 0; i < n; i++) {
        *(A+i) = (double*)malloc(n*sizeof(double));
    }

    //initialize A as identity matrix 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                *(*(A+i)+j) = 1;
            }
            else {
                *(*(A+i)+j) = 0;
            }
        }
    }

    double index;
    //operations will be performed as if A and M were joined horizontally 
    for (int i = 0; i < n; i++) {
        //multiply each row by the inverse of the pivot entries in M 
        row_mult(A, 1/(*(*(M+i)+i)), i, n);
        row_mult(M, 1/(*(*(M+i)+i)), i, n);

        for (int j = i+1; j < n; j++) {
            // perform elementary row operations to change all entries below pivot entries to 0 
            if (*(*(M+j)+i) != 0) {
                index = *(*(M+j)+i);
                row_add(A,i,j,j,n,-index);
                row_add(M,i,j,j,n,-index);
            }
        }
    }

    for (int i = n-1; i >= 0; i--) {
        for (int j = i-1; j >= 0; j--) {
            // perform elementary row operations to change all entries above pivot entries to 0 
            index = *(*(M+j)+i);
            if (*(*(M+j)+i) != 0) {
                row_add(A,i,j,j,n,-index);
                row_add(M,i,j,j,n,-index);
            }

        }
    }
    return A;
}

int main(int argc, char **argv) {
    //pointer for train txt file 
    FILE *fptr1;
    //pointer for data txt file 
    FILE *fptr2;

    char *str1;
    str1 = malloc(7 * sizeof(char));
    char *str2;
    str2 = malloc(6 * sizeof(char));
    int num_attr1;
    int num_house1;
    int num_attr2;
    int num_house2;

    char *name1 = argv[1];
    fptr1 = fopen(name1, "r");
    if (fptr1 == NULL) {
        return EXIT_FAILURE;
    }

    fgets(str1, 7, fptr1);
    fscanf(fptr1, "%d", &num_attr1);
    num_attr1++;
    fscanf(fptr1, "%d", &num_house1);

    double **X;
    double **Y;
    //memory allocation for matrix X, representing the training data, and matrix Y, representing the house prices according to the training data 
    X = (double**)malloc(num_house1*sizeof(double*));
    Y = (double**)malloc(num_house1*sizeof(double*));

    for (int i = 0; i < num_house1; i++) {
        *(X+i) = (double*)malloc(num_attr1 *sizeof(double));
        *(Y+i) = (double*)malloc(sizeof(double));
    }

    double val;
    for (int i = 0; i < num_house1; i++) {
        *(*(X+i)+0) = 1;
        for (int j = 1; j < num_attr1; j++) {
            fscanf(fptr1, "%lf", &val);
            *(*(X+i)+j) = val;
        }

        fscanf(fptr1, "%lf", &val);
        *(*(Y+i)+0) = val;
    }

    fclose(fptr1);

    //perform matrix calculations according to the algorithm to find the matrix W, where each row gives the weight of an attribute 

    double **X_T = transpose(X, num_house1, num_attr1);

    double **XTX = multiply(X_T, num_attr1, num_house1, X, num_attr1);
    double **inv = inverse(XTX, num_attr1);

    double **invXT = multiply(inv, num_attr1, num_attr1, X_T, num_house1);
    double **W = multiply(invXT, num_attr1, num_house1, Y, 1);
    char *name2 = argv[2];

    fptr2 = fopen(name2, "r");
    if (fptr2 == NULL) {
        return EXIT_FAILURE;
    }
    fgets(str2, 6, fptr2);

    fscanf(fptr2, "%d", &num_attr2);
    fscanf(fptr2, "%d", &num_house2);

    //read the values in data file, multiply attributes by its appropriate weight, and print out the calculated housing prices 
    for (int i = 0; i < num_house2; i++) {
        double price = *(*(W+0)+0), temp;
        for (int j = 1; j < num_attr2+1; j++) {
            fscanf(fptr2, "%lf", &temp);
            price += *(*(W+j)+0) * temp;

        }

        printf("%.0f\n", price);
    }

    fclose(fptr2);

    for (int i = 0; i < num_house1; i++) {
        free(*(X+i));
        free(*(Y+i));
    }

    for (int i = 0; i < num_attr1; i++) {
        free(*(XTX+i));
        free(*(W+i));
        free(*(X_T+i));
        free(*(inv+i));
        free(*(invXT+i));
    }

    free(X);
    free(Y);
    free(W);
    free(X_T);
    free(XTX);
    free(inv);
    free(invXT);
    free(str1);
    free(str2);

    return EXIT_SUCCESS;

}