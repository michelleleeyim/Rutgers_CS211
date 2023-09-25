#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h>

struct inout{
    char* name; 
    int val;
};

struct gate{
    char* operation; 
    int inputnum;
    int* inarr; 
    struct gate* next; 
    int outputnum; 
    int* outarr; 
    int multi; 
}; 

struct gate* create_gate() {
    struct gate* new = malloc(sizeof(struct gate)); 
    new -> operation = NULL; 
    new -> next = NULL; 
    return new; 
}

int expo(int base, int e) {
    int n = base; 
    if (e == 0) {
        return 1; 
    }

    for (int i = 1; i < e; i++) {
        n = n * base; 
    }
    return n; 
}

int log_base_2(int n) {
    int count = 0; 
    double num = (double)n; 
    while ((num/2) >= 1) {
        num = num / 2; 
        count ++; 
    }
    return count; 
}

int find_index(struct inout* arr, const char* name, int n){
    for (int i = 0; i < n; i++) {
        char* str = arr[i].name; 
        if (strcmp(str, name) == 0) {
            return i; 
        } 
    }

    return -1; 
}

int check_in(struct inout* arr, int* inarr, int n) {
    int index; 
    for (int i = 0; i < n; i++) {
        index = inarr[i]; 
        if (arr[index].val == -5) {
            return -5; 
        }
    }

    return 0; 
}

int check(struct inout* arr, int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i].val == -5) {
            return -5; 
        }
    }

    return 0; 
}

int NOT(struct inout* arr, int index){
    return !(arr[index].val); 
}

int AND(struct inout* arr, int index1, int index2) {
    return arr[index1].val && arr[index2].val; 
}

int OR(struct inout* arr, int index1, int index2){
    return arr[index1].val || arr[index2].val; 
}

int NAND(struct inout* arr, int index1, int index2){
    return !(arr[index1].val && arr[index2].val); 
}

int NOR(struct inout* arr, int index1, int index2){
    return !(arr[index1].val || arr[index2].val); 
}

int XOR(struct inout* arr, int index1, int index2){
    return (arr[index1].val ^ arr[index2].val); 
}

int DECODER(int gate_n, struct inout* arr, int* inarr){
    int index;  
    int sum = 0; 
    for (int i = 0; i < gate_n; i++) {
        index = inarr[i]; 
        sum += arr[index].val * (expo(2, gate_n - 1 - i)); 
    }
    return sum; 
}

int MULTIPLEXER(int n, struct inout* arr, int* inarr){
    int index; 
    int num; 
    int sum = 0; 
    struct inout input_info; 

    for (int i = expo(2, n) + 1; i < expo(2,n) + n + 1; i++) {
        index = inarr[i]; 
        input_info = arr[index]; 
        num = input_info.val; 
        sum += num * (expo(2, expo(2,n) + n - i));  
        
    }

    return inarr[sum+1]; 

}

int PASS(struct inout* arr, int index){
    return arr[index].val; 
}

void free_total(struct inout* totalarr, int numinput) {
    for (int i = 0; i < numinput; i++) {
        free(totalarr[i].name);
    }

    free(totalarr); 
}

int main(int argc, char** argv) {
    FILE *fptr;

    char *title = argv[1];
    fptr = fopen(title, "r");
    if (fptr == NULL) {
        return EXIT_FAILURE;
    }

    int numinput; 
    int numoutput; 
    char* directive = (char*) malloc (17 * sizeof(char)); 

    fscanf(fptr, "%16s", directive); 
    fscanf(fptr, "%d", &numinput); 

    int numtotal = numinput + 2; 
    struct inout* total_arr = (struct inout*) malloc ((numtotal) * sizeof(struct inout)); 
    struct inout* new_arr; 
    total_arr[0].name = (char*)malloc(17*sizeof(char)); 
    total_arr[1].name = (char*)malloc(17*sizeof(char)); 

    strcpy(total_arr[0].name, "0\0");
    strcpy(total_arr[1].name, "1\0");


    for (int i = 2; i < numtotal; i++) {
        fscanf(fptr, "%16s", directive); 
        total_arr[i].name = (char*) malloc (17 * sizeof(char)); 
        strcpy(total_arr[i].name, directive); 
        total_arr[i].val = -5; 
    }
    fscanf(fptr, "%16s", directive); 
    fscanf(fptr, "%d", &numoutput); 

    numtotal += numoutput; 
    new_arr = realloc(total_arr, (numtotal) * sizeof(struct inout)); 
    total_arr = new_arr;

    for (int i = 0; i < numoutput; i++) {
        fscanf(fptr, "%16s", directive); 
        total_arr[i+numinput+2].name = (char*) malloc (17 * sizeof(char)); 
        strcpy(total_arr[i+numinput+2].name, directive); 
        total_arr[i+numinput+2].val = -5; 
    }

    int gateinput; 
    struct gate* head = create_gate(); 
    struct gate* ptr = head; 
    int index; 

    while (feof(fptr) != 1) {
        struct gate* logicgate = create_gate();
        logicgate->operation = (char*) malloc (17 * sizeof(char));  
        fscanf(fptr, "%16s", directive); 
        strcpy(logicgate->operation, directive); 

        if (strcmp(directive, "NOT") == 0 || strcmp(directive, "PASS") == 0) {
            logicgate->inputnum = 1; 
            logicgate->outputnum = 1; 
        }

        else if (strcmp(directive, "DECODER") == 0) {
            fscanf(fptr, "%d", &gateinput); 
            logicgate->inputnum = gateinput; 
            logicgate->outputnum = expo(2, gateinput); 
        }

        else if(strcmp(directive, "MULTIPLEXER") == 0) {
            fscanf(fptr, "%d", &gateinput); 
            logicgate->multi = gateinput; 
            logicgate->inputnum = expo(2, gateinput) + gateinput + 1; 
            logicgate->outputnum = 1; 
        }

        else {
            logicgate->inputnum = 2; 
            logicgate->outputnum = 1; 
        }

        logicgate->inarr = (int*)malloc(logicgate->inputnum * sizeof(int)); 
        logicgate->outarr = (int*)malloc(logicgate->outputnum * sizeof(int)); 

        for (int a = 0; a < logicgate->inputnum; a++) {
            if (strcmp(directive,"MULTIPLEXER") == 0 && a == 0) {
                logicgate->inarr[a] = logicgate->multi; 
            } else {
                fscanf(fptr, "%16s", directive);
                index = find_index(total_arr, directive, numtotal); 
                if (index != -1) {
                    logicgate->inarr[a] = index;
                } else {
                    new_arr = realloc(total_arr, (numtotal + 1) * sizeof(struct inout)); 
                    total_arr = new_arr;
                    total_arr[numtotal].name = (char*) malloc(17 * sizeof(char)); 
                    strcpy(total_arr[numtotal].name, directive); 
                    total_arr[numtotal].val = -5;
                    logicgate->inarr[a] = numtotal;
                    numtotal = numtotal +1 ;  
                }
            } 
        }

        for (int b = 0; b < logicgate->outputnum; b++) {
            fscanf(fptr, "%16s", directive); 
            index = find_index(total_arr, directive, numtotal); 
            if (index != -1) {
                logicgate->outarr[b] = index; 
            } else { 
                new_arr = realloc(total_arr, (numtotal + 1) * sizeof(struct inout)); 
                total_arr = new_arr;
                total_arr[numtotal].name = (char*) malloc(17 * sizeof(char)); 
                strcpy(total_arr[numtotal].name, directive); 
                total_arr[numtotal].val = -5;
                logicgate->outarr[b] = numtotal;
                numtotal = numtotal +1 ;  
            }
            }
            ptr-> next = logicgate; 
            ptr = ptr->next; 
        }

     fclose(fptr);
    
     int num = expo(2, numinput); 
     total_arr[0].val = 0; 
     total_arr[1].val = 1; 

     for (int m = 0; m < num; m++) {
        for (int p = 2; p < numtotal; p++) {
            total_arr[p].val = -5; 
        }
         int i = m; 

         if (m == 0) {
             for (int p = 0; p < numinput; p++) {
                 total_arr[2+p].val = 0; 
                 printf("0 ");
             }
         }
         else if (m != 0) {
             printf("\n"); 
             int x = log_base_2(i); 
         for (int j = 2; numinput + 1 -j > x; j++) {
             total_arr[j].val = 0; 
             printf("0 "); 
         }

         while (x>=0) {
             if (i - expo(2, x) >= 0) {
                 total_arr[numinput+1-x].val = 1; 
                 printf("1 "); 
                 i = i - expo(2,x); 
             } else {
                 total_arr[numinput+1-x].val = 0; 
                 printf("0 "); 
             }
             x--; 
         }
         }

         printf("|"); 

        // now must go through the logic struct gate linked list using the assigned input values to calculate the correct output 

        ptr = head;
        int val; 
        int checknum = -5; 
        while (checknum == -5) {
            //check if some of the outputs are -5, or not initialized 
            for (ptr = head -> next; ptr != NULL; ptr = ptr-> next) {
                //go through each logic gate loop to see what you can do 
                if (check_in(total_arr, ptr->inarr, ptr->inputnum) == -5) {
                    //see if any of the input values you need are not initialized 
                    continue; 
                    //move on to next iteration to see if there is a gate that you are able to compute 
                }

                else {
                    //you have corresponding values to all inputs you need 
                    if (strcmp(ptr->operation, "NOT") == 0) {
                val = NOT(total_arr, ptr->inarr[0]); 
                index = ptr->outarr[0]; 
                total_arr[index].val = val; 

             } 

             else if (strcmp(ptr->operation, "AND") == 0) {
                 val = AND(total_arr, ptr->inarr[0], ptr->inarr[1]); 
                 index = ptr->outarr[0]; 
                 total_arr[index].val = val; 
             }

             else if(strcmp(ptr->operation, "OR") == 0) {
                 val = OR(total_arr, ptr->inarr[0], ptr->inarr[1]); 
                 index = ptr->outarr[0]; 
                 total_arr[index].val = val; 

             }

             else if(strcmp(ptr->operation, "NAND") == 0) {
                 val = NAND(total_arr, ptr->inarr[0], ptr->inarr[1]); 
                 index = ptr->outarr[0]; 
                 total_arr[index].val = val; 
             }

             else if(strcmp(ptr->operation, "NOR") == 0) {
                 val = NOR(total_arr, ptr->inarr[0], ptr->inarr[1]);
                 index = ptr->outarr[0]; 
                 total_arr[index].val = val; 
             }

             else if(strcmp(ptr->operation, "XOR") == 0) {
                 val = XOR(total_arr, ptr->inarr[0], ptr->inarr[1]); 
                 index = ptr->outarr[0]; 
                 total_arr[index].val = val; 
             }

             else if(strcmp(ptr->operation, "DECODER") == 0) {
                 val = DECODER(ptr->inputnum, total_arr, ptr->inarr); 
                 for (int k = 0; k < ptr->outputnum; k++) {
                    index = ptr->outarr[k]; 
                     if (k == val) {
                         total_arr[index].val = 1; 
                     } else {
                         total_arr[index].val = 0; 
                     }
                 }
             }

             else if(strcmp(ptr->operation, "MULTIPLEXER") == 0) {
                 int n = ptr->inarr[0]; 
                 val = MULTIPLEXER(n, total_arr, ptr->inarr); 
                 index = ptr->outarr[0]; 
                 total_arr[index].val = total_arr[val].val; 
                 
             } else { 
                index = ptr->inarr[0]; 
                val = total_arr[index].val; 
                index = ptr->outarr[0]; 
                total_arr[index].val = val; 
             }

                }
            }
            checknum = check(total_arr, numtotal); 
            
            
             }
             
        int output; 
         for (int i = 2 + numinput; i < 2 + numinput + numoutput; i++) {
             output = total_arr[i].val; 
             printf(" %d", output); 

         }
         }

    free(directive); 
    for (int i = 0; i < numtotal; i++) {
        free(total_arr[i].name); 
    }
    free(total_arr);
    ptr = head->next; 
    free(head); 
    while (ptr != NULL) {
        struct gate* p = ptr; 
        free(p->operation); 
        free(p->inarr); 
        free(p->outarr); 
        ptr = ptr -> next; 
        free (p);
    }
    

    free(ptr); 
    return EXIT_SUCCESS; 
    
}



    // no need for the gate to include an inout value -> you can just make sure the order of 
    // input in int array, and the value is index of input array 
    // all of your input vals will be initialized, with numinput, when you have a temp variable 
    //reallocate the array, and start saving the value for each  output at number (i ++)


