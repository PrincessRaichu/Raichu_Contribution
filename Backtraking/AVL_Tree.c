#include <stdio.h>
#include <stdlib.h>

// AVL Tree node structure
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

// Function to get the height of the tree
int height(struct Node *node) {
    if (node == NULL) return 0;
    return node->height;
}

// Utility function to create a new node
struct Node* createNode(int key) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // New node is initially at height 1
    return node;
}

// Right rotation to balance the tree
struct Node* rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    // Return new root
    return x;
}

// Left rotation to balance the tree
struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    // Return new root
    return y;
}

// Get balance factor of node
int getBalance(struct Node *node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}

// Function to insert a key into the AVL tree and balance it
struct Node* insert(struct Node* node, int key) {
    // Perform normal BST insertion
    if (node == NULL) return createNode(key);

    if (key < node->key) node->left = insert(node->left, key);
    else if (key > node->key) node->right = insert(node->right, key);
    else return node; // Duplicates are not allowed

    // Update height of this ancestor node
    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    // Get balance factor to check if node is unbalanced
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key) return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key) return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the unchanged node pointer
    return node;
}

// Utility function to print the pre-order traversal of the tree
void preOrder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Main function to demonstrate AVL tree
int main() {
    struct Node *root = NULL;

    // Insert nodes into the AVL tree
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Preorder traversal of the AVL tree:\n");
    preOrder(root);

    return 0;
}
