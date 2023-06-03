/*
19
A Dictionary stores keywords and its meanings. Provide facility for adding new
keywords, deleting keywords, updating values of any entry. Provide facility to
display whole data sorted in ascending/ Descending order. Also find how many
maximum comparisons may require for finding any keyword. Use Height balance tree
and find the complexity for finding a keyword */

#include <iostream>
using namespace std;

class node {
   public:
    string key;
    string value;
    node* left;
    node* right;
    node(string key = "", string value = "") {
        this->key = key;
        this->value = value;
        this->left = NULL;
        this->right = NULL;
    }
};

class AVL {
    node* root = NULL;
    int height(node* n) {
        if (n == NULL) {
            return 0;
        }
        return 1 + max(height(n->left), height(n->right));
    }

    int balanceFactor(node* n) {
        if (n == NULL) {
            return 0;
        }
        return (height(n->left) - height(n->right));
    }

    node* rightRotate(node* y) {
        // get changing nodes
        node* x = y->left;

        node* t2 = x->right;

        // change the nodes
        x->right = y;
        y->left = t2;

        // return
        return x;
    }
    node* leftRotate(node* x) {
        // get changing nodes
        node* y = x->right;
        node* t2 = y->left;

        // change the nodes
        y->left = x;
        x->right = t2;

        // return
        return y;
    }

    // recursive insertion function which will be called by insert function
    node* insertion(node* temp, string key, string value) {
        if (temp == NULL) {
            node* nn = new node(key, value);
            return nn;
        }
        if (key < temp->key) {
            temp->left = insertion(temp->left, key, value);
        }
        if (key > temp->key) {
            temp->right = insertion(temp->right, key, value);
        }
        int bf = balanceFactor(temp);
        // LL Rotation
        if (bf > 1 && balanceFactor(root->left) >= 0) {
            return rightRotate(temp);
        }
        // RR Rotation
        if (bf < -1 && balanceFactor(root->right) <= 0) {
            return leftRotate(temp);
        }
        // LR Rotation
        if (bf > 1 && balanceFactor(root->left) < 0) {
            temp->left = leftRotate(temp->left);
            return rightRotate(temp);
        }
        // RL Rotation
        if (bf < -1 && balanceFactor(root->right) > 0) {
            temp->right = rightRotate(temp->right);
            return leftRotate(temp);
        }
        return temp;
    }

    void ascending(node* n) {
        if (n != NULL) {
            ascending(n->left);
            cout << n->key << ":" << n->value << endl;
            ascending(n->right);
        }
    }

    void descending(node* n) {
        if (n != NULL) {
            descending(n->right);
            cout << n->key << ":" << n->value << endl;
            descending(n->left);
        }
    }
    bool isPresent(string key) {
        node* temp = root;
        while (temp != NULL) {
            if (temp->key == key) {
                return true;
            } else if (temp->key < key) {
                temp = temp->right;
            } else {
                temp = temp->left;
            }
        }
        return false;
    }
    node* minNode(node* root) {
        node* n = root;
        while (n->left != NULL) {
            n = n->left;
        }
        return n;
    }

    node* remove(node*& temp_root, string key) {
        // step1 bst deletion
        if (temp_root == NULL) {
            return NULL;
        }

        if (key < temp_root->key) {
            temp_root->left = remove(temp_root->left, key);
        } else if (key > temp_root->key) {
            temp_root->right = remove(temp_root->right, key);
        } else {
            node* temp1 = temp_root;
            // one and no child
            if (temp_root->left == NULL || temp_root->right == NULL) {
                if (temp_root->left == NULL) {
                    temp_root = temp_root->right;
                } else {
                    temp_root = temp_root->left;
                }
                delete temp1;
            } else {
                // two child
                node* temp2 = minNode(temp_root->right);
                temp_root->key = temp2->key;
                temp_root->value = temp2->value;

                temp_root->right = remove(temp_root->right, temp2->key);
            }
        }

        // check if root is NULL
        if (temp_root == NULL) return temp_root;

        // step2 avl balancing

        int bf = balanceFactor(temp_root);

        // LL Rotation
        // if (bf > 1 && key < temp_root->left->key) {
        if (bf > 1 && balanceFactor(root->left) >= 0) {
            return rightRotate(temp_root);
        }
        // RR Rotation
        // if (bf < -1 && key > temp_root->right->key) {
        if (bf < -1 && balanceFactor(root->right) <= 0) {
            return leftRotate(temp_root);
        }
        // LR Rotation
        // if (bf > 1 && key > temp_root->left->key) {
        if (bf > 1 && balanceFactor(root->left) < 0) {
            temp_root->left = leftRotate(temp_root->left);
            return rightRotate(temp_root);
        }
        // RL Rotation
        // if (bf < -1 && key < temp_root->right->key) {
        if (bf < -1 && balanceFactor(root->right) > 0) {
            temp_root->right = rightRotate(temp_root->right);
            return leftRotate(temp_root);
        }
        return temp_root;
    }

   public:
    string search(string key) {
        node* temp = root;
        while (temp != NULL) {
            if (temp->key == key) {
                return temp->value;
            } else if (temp->key < key) {
                temp = temp->right;
            } else {
                temp = temp->left;
            }
        }
        return "\0";
    }

    bool insert(string key, string value) {
        if (isPresent(key)) {
            return false;
        } else {
            root = insertion(root, key, value);
            return true;
        }
    }

    bool update(string key, string value) {
        node* temp = root;
        while (temp != NULL) {
            if (temp->key == key) {
                temp->value = value;
                return true;
            } else if (temp->key < key) {
                temp = temp->right;
            } else {
                temp = temp->left;
            }
        }
        return false;
    }

    bool remove(string key) {
        if (!isPresent(key)) {
            return false;
        } else {
            root = remove(root, key);
            return true;
        }
    }
    void ascending() {
        if (root == NULL) {
            cout << "Tree is Empty" << endl;
            return;
        }

        cout << "Ascending Traversal is" << endl;
        ascending(root);
    }

    void descending() {
        if (root == NULL) {
            cout << "Tree is Empty" << endl;
            return;
        }

        cout << "Descending Traversal is" << endl;
        descending(root);
    }
};

int main() {
    // implement AVL tree
    AVL a;
    cout << a.insert("1", "a") << endl;
    cout << a.insert("2", "b") << endl;
    cout << a.insert("3", "c") << endl;
    cout << a.insert("4", "d") << endl;
    a.descending();
    cout << a.remove("1") << endl;
    a.ascending();
    return 0;
}