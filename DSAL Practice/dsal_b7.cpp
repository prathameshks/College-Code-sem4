/*
Construct an expression tree from the given prefix expression eg. +--a*bc/def
and traverse it using post order traversal (non recursive) and then delete the
entire tree.
*/

#include <iostream>
#include <stack>
using namespace std;

class node {
   public:
    char data;
    node *left, *right;

    node(char d) {
        data = d;
        left = NULL;
        right = NULL;
    }
};

class tree {
    node* root = NULL;
    stack<node*> s;

   public:
    void insert(char c) {
        node* temp = new node(c);
        switch (c) {
            case '+':
            case '-':
            case '*':
            case '/':
                temp->left = s.top();
                s.pop();
                temp->right = s.top();
                s.pop();
                break;
            default:
                break;
        }
        s.push(temp);
    }

    void insert_prefix(string exp) {
        int n = exp.length();
        for (int i = n - 1; i >= 0; i--) {
            insert(exp[i]);
        }
        root = s.top();
        s.pop();
        post(root);
        cout << endl;
        postOrder();
        cout << endl;
    }

    void post(node* n) {
        if (n) {
            post(n->left);
            post(n->right);
            cout << n->data;
        }
    }
    
    void postOrder() {
        stack<node*> s2;
        s.push(root);
        while (!s.empty()) {
            node* temp = s.top();
            s.pop();
            s2.push(temp);
            if (temp->left != NULL) {
                s.push(temp->left);
            }
            if (temp->right != NULL) {
                s.push(temp->right);
            }
        }
        while (!s2.empty()) {
            cout << s2.top()->data;
            s2.pop();
        }
    }
};

int main() {
    // code here
    tree t;
    string e = "+--a*bc/def";
    t.insert_prefix(e);
    return 0;
}