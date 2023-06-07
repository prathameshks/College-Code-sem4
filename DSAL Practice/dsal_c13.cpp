/*
Represent a given graph using adjacency matrix/list to perform DFS and using
adjacency list to perform BFS. Use the map of the area around the college as the
graph. Identify the prominent land marks as nodes and perform DFS and BFS on
that.
*/

#include <iostream>
using namespace std;

class node {
   public:
    string key, value;
    node *left, *right;
    node(string k = "", string v = "") {
        key = k;
        value = v;
        left = NULL;
        right = NULL;
    }
};

class bst {
   private:
    node* root;

    node* min_val(node* n) {
        while (n->left != NULL) {
            n = n->left;
        }
        return n;
    }

    node* remove(node* n, string key) {
        if (n == NULL) {
            return NULL;
        }
        node* temp;
        if (key < n->key) {
            n->left = remove(n->left, key);
        } else if (key > n->key) {
            n->right = remove(n->right, key);
        } else {
            if (n->left == NULL and n->right == NULL) {
                return NULL;
            } else if (n->left != NULL and n->right == NULL) {
                temp = n->left;
                delete n;
                return temp;
            } else if (n->left == NULL and n->right != NULL) {
                temp = n->right;
                delete n;
                return temp;
            } else {
                temp = min_val(n->right);
                n->key = temp->key;
                n->value = temp->value;
                n->right = remove(n->right, temp->key);
            }
        }
        return n;
    }

    node* insert(node* n, string key, string val) {
        if (n == NULL) {
            node* t = new node(key, val);
            return t;
        }

        if (key < n->key) {
            n->left = insert(n->left, key, val);
        } else if (key > n->key) {
            n->right = insert(n->right, key, val);
        }
        return n;
    }

   public:
    bst() { root = NULL; }

    void insert(string key, string val) { root = insert(root, key, val); }

    string search(string key) {
        node* temp = root;
        while (temp != NULL) {
            if (key < temp->key) {
                temp = temp->left;
            } else if (key > temp->key) {
                temp = temp->right;
            } else {
                return temp->value;
            }
        }
        return "\0";
    }

    bool update(string key, string val) {
        node* temp = root;
        while (temp != NULL) {
            if (key < temp->key) {
                temp = temp->left;
            } else if (key > temp->key) {
                temp = temp->right;
            } else {
                temp->value = val;
                return true;
            }
        }
        return false;
    }

    void remove(string key) { root = remove(root, key); }
};

int main() {
    // code here
    bst t;
    t.insert("g", "1");
    t.insert("a", "2");
    t.insert("b", "3");
    t.insert("y", "4");
    t.insert("z", "5");
    t.insert("p", "6");
    t.insert("f", "7");
    return 0;
}