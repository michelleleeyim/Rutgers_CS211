#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//int num = 0;

typedef struct node {
    int val;
    struct node* left;
    struct node* right;
}node;

 struct node* create_node(int val, node* left, node* right) {
     struct node *new = (node*)malloc(sizeof(node));
     new -> left = left;
     new -> right = right;
     new -> val = val;
     return new;
 }

struct node* insert(node* root, int i) {

    if (root == NULL) {
        struct node* new = create_node(i, NULL, NULL); 
        printf("inserted\n");
        return new; 
    }
    
    if (root -> val < i) {
        root -> right = insert(root -> right, i);
    } else if (root -> val > i) {
        root -> left = insert (root -> left, i);
    } else {
        printf("not inserted\n");
    }

    return root;
}

void search (node* root, int val) {
    if (root == NULL) {
        printf("absent\n");
        return;
    }

    if (root -> val == val) {
        printf("present\n");
        return;
    }


    if (root -> val < val) {
        return search(root->right, val);
    }

    if (root -> val > val) {
        return search(root -> left, val);
    }
}

void bstprint (node* root) {

    if (root == NULL) {
        //printf("\n");
        return;
    }
    printf("(");
    bstprint(root -> left);
    printf("%d", root -> val);
    bstprint(root->right);
    printf(")");
    return; 
}

struct node* delete(node*root, int n){
    if (root == NULL) {
        printf("absent\n");
        return root;
    }

    //printf("%d\n", root->val); 

    if (root -> val > n) {
        root->left = delete(root->left, n);
    } else if (root -> val < n) {
        root -> right = delete(root->right, n);
    }
    else {

        struct node* temp; 
        if (root->left == NULL) {
            temp = root->right;
            free(root);
            printf("deleted\n");
            return temp;
        } else if (root -> right == NULL) {
            temp = root -> left;
            free(root);
            printf("deleted\n");
            return temp;
        } else if (root->left == NULL && root->right == NULL) {
            free(root); 
            printf("deleted\n"); 
            return NULL;
        } else {
            temp = root -> right; 
            while (temp != NULL && temp -> left != NULL) {
                temp = temp -> left; 
            }

            root-> val = temp -> val;
            root->right = delete(root->right, temp->val);
            return (root);
        }
        printf("deleted\n");
    }
        return(root);
}

void freenode(node* root) {
    if (root == NULL) {
        return;
    }

    freenode(root->left); 
    freenode(root->right); 
    free(root);
}

int main(int argc, char **argv) {
    struct node* root = NULL;

    char c;
    int i; 

    while (scanf("%c", &c) != EOF) {
        if (c == 'p') {
            bstprint(root); 
            printf("\n"); 
        }else {
            scanf("%d", &i); 
            if (c == 'i') {
                root = insert(root, i);
                } else if(c == 'd') {
                    root = delete(root, i);
                    } else if(c == 's') {
                        search(root, i);
                        }
        }
    }

    freenode(root); 

    return EXIT_SUCCESS;
}

