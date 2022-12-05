// bst.c: Example implementation of a Binary Search Tree

#include <stdio.h>
#include <stdlib.h>

// Node: element in a Binary Search Tree
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Create a new node (on the heap)
struct Node* new_node(int data) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// search for a node by value, starting from the root
struct Node* search(struct Node* node, int value) {
    if (node == NULL || node->data == value) {
        return node;
    }
    else if (node->data < value) {
        return search(node->right, value);
    }
    else {
        return search(node->left, value);
    }
}

// Insert a new value into the tree
struct Node* insert(struct Node *node, int value) {
    if (node == NULL) {
        return new_node(value);
    }
    else if (node->data < value) {
        node->right = insert(node->right, value);
    }
    else {
        node->left = insert(node->left, value);
    }
    return node;
}

// find successor node (starts from right child)
struct Node* get_successor(struct Node *node) {
    while (node != NULL && node->left != NULL)
        node = node->left;
    return node;
}

// Remove a node from a BST
struct Node* remove_node(struct Node *node, int value) {
    if (node == NULL)
        return node;
    if (value < node->data)
        node->left = remove_node(node->left, value);
    else if (value > node->data)
        node->right = remove_node(node->right, value);
    else {
        if (node->left == NULL) {
            struct Node *child = node->right;
            free(node);
            return child;
        }
        else if (node->right == NULL) {
            struct Node* child = node->left;
            free(node);
            return child;
        }
        else {
            struct Node *successor = get_successor(node->right);
            node->data = successor->data;
            node->right = remove_node(node->right, successor->data);
        }
    }
    return node;
}


int main(void) {

    struct Node *root = NULL;
    int data[] = {10,7,15,4,9,12,19};
    int n = 7;

    for (int i = 0; i < n; i++) {
        root = insert(root, data[i]);
    }

    // Find a value
    struct Node *node = search(root, 4);
    if (node == NULL) {
        printf("value not found\n");
    }
    else {
        printf("value: %d found\n", node->data);
    }

    // remove node
    struct Node *r = remove_node(root, 4);
    node = search(root, 4);
    if (node == NULL) {
        printf("value not found\n");
    }
    else {
        printf("value: %d found\n", node->data);
    }

}


