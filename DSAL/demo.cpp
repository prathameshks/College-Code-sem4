#include <iostream>
#include <string>
using namespace std;

struct node {
    string key;
    string meaning;
    node* left = NULL;
    node* right = NULL;
};
class dictionary {
   public:
    node* root = NULL;
    node* insert(node* root, node* temp);
    void asc_display(node* root);
    void dec_display(node* root);
    // node* balance(node *temp);
    node* right_rotate(node* root);
    node* left_rotate(node* root);
    int balance_factor(node* root);
    int height(node* root);
    node* find(node* r, string k);
    node* delete_key(node* r, string k);
};

node* dictionary ::insert(struct node* root, node* key) {
    // if root is empty returning new node
    if (root == NULL) {
        return key;
    }
    if (key->key < root->key) {
        // insert new node at left of root
        root->left = insert(root->left, key);
    }
    if (key->key > root->key) {
        // insert new node at right of root
        root->right = insert(root->right, key);
    }

    // increasing height of node after insertion so that because of recursion
    // the height will be updated upto root from the node inserted at the leaf
    // position
    // root->height = 1 + max(height(root->left), height(root->right));
    int bf = balance_factor(root);

    // LL rotation
    if (bf > 1 && key->key < root->left->key) {
        root = right_rotate(root);
    }

    // RR rotation
    if (bf < -1 && key->key > root->right->key) {
        root = left_rotate(root);
    }

    // LR rotation
    if (bf > 1 && key->key > root->left->key) {
        root->left = left_rotate(root->left);
        root = right_rotate(root);
    }

    // RL rotation
    if (bf < -1 && key->key < root->right->key) {
        root->right = right_rotate(root->right);
        root = left_rotate(root);
    }
    return root;
}

node* dictionary::right_rotate(node* par) {
    // node *temp,*temp1;
    // temp=par->left;
    // temp1=temp->right;
    // temp->right=par;
    // par->left= temp->right;
    // return temp;

    // node *new_root=par->left;
    // par->left=new_root->right;
    // new_root->right=par;
    // return new_root;

    // getting the changing childs
    struct node* x = par->left;
    struct node* t2 = x->right;

    // changing the childs
    x->right = par;
    par->left = t2;
    return x;
}

node* dictionary::left_rotate(node* par) {
    // node *temp,*temp1;
    // temp=par->right;
    // temp1=temp->left;
    // temp->left=par;
    // par->right=temp1;
    // return temp;

    // node *new_root=par->right;
    // par->right=new_root->left;
    // new_root->left=par;
    // return new_root;

    // getting the changing childs
    struct node* y = par->right;
    struct node* t2 = y->left;

    // changing the childs
    y->left = par;
    par->right = t2;
    return y;
}

int dictionary::balance_factor(node* root) {
    return root == NULL ? 0 : (height(root->left) - height(root->right));
}

int dictionary::height(node* root) {
    if (!root) {
        return 0;
    }
    return max(height(root->left), height(root->right)) + 1;
}

node* dictionary::delete_key(node* r, string k) {
    if (r == NULL) return NULL;
    if (r->key == k) {
        if (!r->left && !r->right) {
            delete (r);
            return NULL;
        }
        if (r->left && !r->right) {
            node* temp = r->left;
            delete (r);
            return temp;
        }
        if (!r->left && r->right) {
            node* temp = r->right;
            delete (r);
            return temp;
        }
        if (r->left && r->right) {
            node* rep = r->left;
            while (rep->right != NULL) rep = rep->right;
            r->key = rep->key;
            r->meaning = rep->meaning;
            r->right = delete_key(r->right, rep->key);
            // return balance(r);
        }
    }
    if (r->key > k) {
        r->left = delete_key(r->left, k);
    } else {
        r->right = delete_key(r->right, k);
    }
    // return balance(r);
    return r;
}

node* dictionary::find(node* r, string k) {
    while (r != NULL) {
        if (r->key == k) {
            return r;
        }
        if (r->key > k) {
            r = r->left;
        } else {
            r = r->right;
        }
    }
    return NULL;
}

void dictionary::asc_display(node* root) {
    if (root != NULL) {
        asc_display(root->left);
        cout << root->key << " - " << root->meaning << endl;
        asc_display(root->right);
    }
}
void dictionary::dec_display(node* root) {
    if (root != NULL) {
        dec_display(root->right);
        cout << root->key << " - " << root->meaning << endl;
        dec_display(root->left);
    }
}

int main() {
    dictionary obj;
    bool flag = true;
    int ch;
    string s, k;
    node* t;
    while (flag) {
        cout << "MENU" << endl;
        cout << "1.Insert" << endl;
        cout << "2.Ascending Display" << endl;
        cout << "4.Decending Display" << endl;
        cout << "5.Update" << endl;
        cout << "6.Delete" << endl;
        cout << "7.Exit" << endl;
        cout << "Enter choice:";
        cin >> ch;
        switch (ch) {
            case 1:
                t = new node();
                cout << "Enter key:";
                cin >> t->key;
                cout << "Enter meaning:";
                cin >> t->meaning;
                if (obj.root == NULL) {
                    obj.root = t;
                } else {
                    obj.insert(obj.root, t);
                }

                break;

            case 2:
                obj.asc_display(obj.root);
                cout << endl;
                break;

            case 3:
                obj.dec_display(obj.root);
                cout << endl;
                break;
                ;

            case 5:
                cout << "Enter key you want to update:";
                cin >> s;
                cout << "Enter new meaning:";
                cin >> k;
                obj.find(obj.root, s)->meaning = k;
                break;

            case 6:
                cout << "Enter key to be deleted:";
                cin >> s;
                obj.delete_key(obj.root, s);
                break;

            case 7:
                flag = false;
                break;

            default:
                cout << "Invalid input" << endl;
                break;
        }
    }

    return 0;
}

/*
1
50
kaustubh
1
30
prathamesh
1
20
siddharth
1
40
ayush
1
10
akhilesh
2
3

*/