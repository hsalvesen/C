#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFERSIZE 128

// A linked list node
typedef struct node {
    char name[BUFFERSIZE];
    int data;
    struct node *next;
} Node;

// create new node on the heap
Node *create_node(char *name, int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->name,name);
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// appends data to an exiting list
Node *append_node(Node *head, char *name, int data) {
    Node *new_node = create_node(name, data);
    if (head == NULL) {
        return(new_node);
    }
    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return(head);
}

// remove node from a list
Node *remove_node(Node *head, char *name) {
    Node *current = head;
    Node *previous = NULL;
    while (current != NULL) {
        if ( strcmp(current->name, name) == 0 ) {
            if (previous != NULL) {
                previous->next = current->next;
            }
            if (current == head) {
                head = current->next;
            }
            free(current);
            return head;
        }
        previous = current;
        current = current->next;
    }
    return head;
}

// traverse and print list
void print_list(Node *head) {
    Node *current = head;
    printf("list = [\n");
    while (current != NULL) {
        printf("%s: %d\n",current->name,current->data);
        current = current->next;
    }
    printf("]\n");
}

// free a list from the heap
void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *toremove = current;
        current = current->next;
        free(toremove);
    }
}

int main(void) {

    Node *head = NULL;
    head = append_node(head,"a",1);
    head = append_node(head,"b",2);
    head = append_node(head,"c",3);

    print_list(head);

    head = append_node(head,"d",4);
    head = append_node(head,"e",5);

    print_list(head);

    head = remove_node(head,"a");

    print_list(head);

    free_list(head);

}

