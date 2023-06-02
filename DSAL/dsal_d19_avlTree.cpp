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
    node() {
        left = NULL;
        right = NULL;
    }
};

class AVL {
    int height(node* n) {
        if (n == NULL) {
            return 0;
        }
        return 1 + max(height(n->left), height(n->right));
    }

    void balance(){
        
    }

   public:
    AVL(){}
    void insert(string key,string value){

    }
};


int main() {
    // implement AVL tree
    AVL a;
    return 0;
}