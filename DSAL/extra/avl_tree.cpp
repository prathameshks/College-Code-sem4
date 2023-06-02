#include <iostream>
using namespace std;

// creating node struct
struct node {
    int key;
    struct node* left;
    struct node* right;
    int height;
};

struct node* createNode(int key) {
    // allocate memory
    struct node* newNode = new node;
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// max function to get max of 2 numbers
int max(int a, int b) { return (a > b) ? a : b; }

// height function to get height of the node
int height(struct node* n) { return (n == NULL) ? 0 : n->height; }

// get balance factor of the node 0 if null else h_left-h_right
int balance_factor(struct node* n) {
    return (n == NULL) ? 0 : (height(n->left) - height(n->right));
}

struct node* leftRotate(struct node* x) {
    // getting the changing childs
    struct node* y = x->right;
    struct node* t2 = y->left;

    // changing the childs
    y->left = x;
    x->right = t2;

    // changing heights
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    // y will be new head of the tree/subtree
    return y;
}

struct node* rightRotate(struct node* y) {
    // getting the changing childs
    struct node* x = y->left;
    struct node* t2 = x->right;

    // changing the childs
    x->right = y;
    y->left = t2;

    // changing heights
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    // x will be new head of the tree/subtree
    return x;
}

struct node* insert(struct node* root, int key) {
    // if root is empty returning new node
    if (root == NULL) {
        return createNode(key);
    }
    if (key < root->key) {
        // insert new node at left of root
        root->left = insert(root->left, key);
    }
    if (key > root->key) {
        // insert new node at right of root
        root->right = insert(root->right, key);
    }

    // increasing height of node after insertion so that because of recursion
    // the height will be updated upto root from the node inserted at the leaf
    // position
    root->height = 1 + max(height(root->left), height(root->right));
    int bf = balance_factor(root);

    // LL rotation
    if (bf > 1 && key < root->left->key) {
        root = rightRotate(root);
    }

    // RR rotation
    if (bf < -1 && key > root->right->key) {
        root = leftRotate(root);
    }

    // LR rotation
    if (bf > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        root = rightRotate(root);
    }

    // RL rotation
    if (bf < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        root = leftRotate(root);
    }
    return root;
}

void preorder(struct node* n) {
    if (n != NULL) {
        cout << n->key << " ";
        preorder(n->left);
        preorder(n->right);
    }
}

int main() {
    struct node* root = NULL;
    root = insert(root, 1);
    root = insert(root, 2);
    root = insert(root, 4);
    root = insert(root, 5);
    root = insert(root, 6);
    root = insert(root, 3);

    preorder(root);

    return 0;
}