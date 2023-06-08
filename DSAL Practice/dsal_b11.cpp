/*
A Dictionary stores keywords and its meanings. Provide facility for adding new
keywords, deleting keywords, updating values of any entry. Provide facility to
display whole data sorted in ascending/ Descending order. Also find how many
maximum comparisons may require for finding any keyword. Use Binary Search Tree
for implementation.
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

   public:
    bst() { root = NULL; }

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

    void remove(string key) { root = remove(root, key); }

    void ascending(node* root) {
        if (root) {
            ascending(root->left);
            cout << root->key << " : " << root->value << endl;
            ascending(root->right);
        }
    }

    void descending(node* root) {
        if (root) {
            descending(root->right);
            cout << root->key << " : " << root->value << endl;
            descending(root->left);
        }
    }

    void ascending() { ascending(root); }
    void descending() { descending(root); }
};

int main() {
    // code here
    bst t;
    t.remove("1");
    t.insert("g", "1");
    t.insert("a", "1");
    t.insert("b", "1");
    t.insert("y", "1");
    t.descending();
    t.remove("g");
    t.ascending();
    return 0;
}