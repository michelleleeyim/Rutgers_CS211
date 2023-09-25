#include <stdlib.h>
#include <stdio.h>

int num = 0;

struct node {
    int val;
    struct node *next;
};

struct node* insert_node(struct node* head, struct node* temp) {
    int val = temp -> val;
    if (head == NULL || head -> val > val) {
        temp-> next = head;
        head = temp;
        num++;
        return head;
    }

    struct node *p = head;
    struct node *prev;

    while (p != NULL) {
        if (p -> val < val) {
            prev = p;
            p = p-> next;
        }
        else if (p -> val == val) {
            free(temp);
            return head;
        }

        else if (p-> val > val) {
            temp -> next = p;
            prev->next = temp;
            num++;
            return head;
        }
    }

        if (p == NULL) {
            prev -> next = temp;
            num++;
        }
    return head;
}

struct node* delete_node (struct node* head, int val) {
    struct node *p = head;
    struct node *temp;

    if (head == NULL) {
        return head;
    }

    else if (head -> val == val) {
        head = p -> next;
        free(p);
        num--;
        return head;
    }
    while (p -> next != NULL) {
        if (p ->next->val == val) {
            temp = p->next;
            p -> next = temp->next;
            free(temp);
            num--;
            return head;
        } else if (p->val < val) {
            p = p->next;
        } else if (p -> val > val){
            return head;
        }
    }
    return head;
}

//struct node* LinkedList (char c, int i, struct node* head) {
//
//    int num;
//    if (c == 'i') {
//        head = insert_node(head, i);
//    } else {
//        head = delete_node(head, i);
//    }
//
//    num = counter(head);
//    printf("%d :", num);
//
//    struct node* p = head;
//
//    while (p != NULL) {
//        if (p -> next != NULL) {
//            printf("%d ", p -> val);
//        } else {
//            printf("%d\n", p->val);
//        }
//        p = p->next;
//    }
//
//    return head;
//
//}
void printLinkedList (struct node *head) {
    struct node *p = head;

//    if (head == NULL) {
//        printf("0 : \n");
//    }
    printf("%d :", num);
    while (p != NULL) {
        printf(" %d", p->val);
        p = p->next;
    }
    printf("\n");
}

int main(int argc, char **argv) {

    struct node *head = NULL;

    char c;
    int i;

    while (scanf(" %c%d", &c,&i) != EOF) {
        if (c == 'i') {
            struct node *temp = malloc(sizeof(struct node));
            temp-> val = i;
            temp->next = NULL;

            head = insert_node(head, temp);
            printLinkedList(head);

        } else if (c == 'd') {
            head = delete_node(head, i);
            printLinkedList(head);
        }

    }
    struct node *p = head;

    while (p->next != NULL) {
        head = p;
        p = p -> next;
        free(head);
    }
    free(p);

    p = NULL;

    return EXIT_SUCCESS;
}

