/*A Dictionary stores keywords and its meanings. Provide facility for adding new
keywords, deleting keywords, updating values of any entry. Provide facility to
display whole data sorted in ascending/ Descending order. Also find how many
maximum comparisons may require for finding any keyword. Use Binary Search Tree
for implementation. */
#include <iostream>
#include <string>
using namespace std;

class node {
   public:
    string key, value;
    node *left, *right;
    node();
    node(string, string);
};

node::node() {
    key = "";
    value = "";
    left = NULL;
    right = NULL;
}

node::node(string key, string value) {
    this->key = key;
    this->value = value;
    left = NULL;
    right = NULL;
}

class bst {
   public:
    node *root;
    bst();
    bst(string, string);
    bool insert(string, string);
    string search(string);
    bool update(string, string);
    bool delete_key(string);
    void display(node *cur);
    void display_asc(node *cur);
};

bst::bst() { root = NULL; }

bst::bst(string key, string value) { root = new node(key, value); }

bool bst::insert(string key, string value) {
    if (root == NULL) {
        root = new node(key, value);
        return 1;
    }

    node *temp, *prev;
    prev = root;
    temp = root;
    while (temp != NULL) {
        prev = temp;
        if (temp->key == key) {
            return 0;
        } else if (temp->key < key) {
            temp = temp->right;
        } else {
            temp = temp->left;
        }
    }
    if (prev->key < key) {
        prev->right = new node(key, value);
    } else {
        prev->left = new node(key, value);
    }
    return 1;
}

string bst::search(string key) {
    node *temp = root;
    while (temp != NULL) {
        if (temp->key == key) {
            return temp->value;
        } else if (temp->key < key) {
            temp = temp->right;
        } else {
            temp = temp->left;
        }
    }
    return "\0";  // not present
}

bool bst::update(string key, string value) {
    node *temp;
    temp = root;
    while (temp != NULL) {
        if (temp->key == key) {
            temp->value = value;
            return 1;
        } else if (temp->key < key) {
            temp = temp->right;
        } else {
            temp = temp->left;
        }
    }
    return 0;
}

bool bst::delete_key(string key) {
    if (root == NULL) {
        return 0;
    }

    node *temp, *prev;
    prev = root;
    temp = root;

    if (temp->key == key) {
        // delete root case
        if (temp->left == NULL && temp->right == NULL) {
            // no child
            root = NULL;
            delete temp;
        } else if (temp->left != NULL && temp->right == NULL) {
            // single child left
            root = temp->left;
            delete temp;
        } else if (temp->left == NULL && temp->right != NULL) {
            // single child right
            root = temp->right;
            delete temp;
        } else {
            // two child
            // using left largest
            node *l_temp = temp->left;
            node *l_prev = temp;
            if (l_temp->right == NULL) {
                l_prev->left = l_temp->left;
            } else {
                while (l_temp->right != NULL) {
                    l_prev = l_temp;
                    l_temp = l_temp->right;
                }
                l_prev->right = l_temp->left;
            }

            // deleting temp
            l_temp->right = temp->right;
            l_temp->left = temp->left;
            root = l_temp;
            delete temp;
        }
        return 1;
    } else if (temp->key < key) {
        temp = temp->right;
    } else {
        temp = temp->left;
    }

    while (temp != NULL) {
        // delete non root node
        if (temp->key == key) {
            if (temp->left == NULL && temp->right == NULL) {
                // no child
                if (temp->key < prev->key) {
                    // left child
                    prev->left = NULL;
                } else {
                    // right child
                    prev->right = NULL;
                }
                delete temp;
            } else if (temp->left != NULL && temp->right == NULL) {
                // single child left
                if (temp->key < prev->key) {
                    // left child
                    prev->left = temp->left;
                    delete temp;
                } else {
                    // right child
                    prev->right = temp->left;
                    delete temp;
                }
            } else if (temp->left == NULL && temp->right != NULL) {
                // single child right
                if (temp->key < prev->key) {
                    // left child
                    prev->left = temp->right;
                    delete temp;
                } else {
                    // right child
                    prev->right = temp->right;
                    delete temp;
                }
            } else {
                // two child
                // using left largest
                node *l_temp = temp->left;
                node *l_prev = temp;
                if (l_temp->right == NULL) {
                    l_prev->left = l_temp->left;
                } else {
                    while (l_temp->right != NULL) {
                        l_prev = l_temp;
                        l_temp = l_temp->right;
                    }
                    l_prev->right = l_temp->left;
                }

                // deleting temp
                if (temp->key < prev->key) {
                    // left child
                    prev->left = l_temp;
                } else {
                    // right child
                    prev->right = l_temp;
                }
                l_temp->left = temp->left;
                l_temp->right = temp->right;
                delete temp;
            }
            return 1;
        } else if (temp->key < key) {
            prev = temp;
            temp = temp->right;
        } else {
            prev = temp;
            temp = temp->left;
        }
    }
    return 0;
}

void bst::display(node *cur) {
    if (cur == NULL) {
        return;
    }
    display(cur->left);
    cout << cur->key << " : " << cur->value << endl;
    display(cur->right);
}

void bst::display_asc(node *cur) {
    if (cur == NULL) {
        return;
    }
    display_asc(cur->right);
    cout << cur->key << " : " << cur->value << endl;
    display_asc(cur->left);
}

// void printTree(node *root, int space = 0, int height = 20) {
//     if (root == nullptr) return;
//     space += height;
//     printTree(root->right, space);
//     cout << endl;
//     for (int i = height; i < space; i++) cout << " ";
//     cout << root->key << endl;
//     printTree(root->left, space);
// }

int main() {
    bst tree;
    int ch;
    string k, v, ans;
    do {
        cout << "MENU" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Search" << endl;
        cout << "3. Update" << endl;
        cout << "4. Delete" << endl;
        cout << "5. Display Descending" << endl;
        cout << "6. Display Ascending" << endl;
        cout << "0. Exit" << endl;
        cout << "~ Enter your Choice:";
        cin >> ch;
        switch (ch) {
            case 1:
                cout << "Enter key to insert:";
                cin >> k;
                cout << "Enter value:";
                cin >> v;
                if (tree.insert(k, v)) {
                    cout << "Element Inserted Successfully" << endl;
                } else {
                    cout << "Element Already Present" << endl;
                }
                break;
            case 2:
                cout << "Enter key to search:";
                cin >> k;
                ans = tree.search(k);
                if (ans == "\0") {
                    cout << "Element Not Found" << endl;
                } else {
                    cout << "Value is " << ans << endl;
                }
                break;
            case 3:
                cout << "Enter key to Update:";
                cin >> k;
                cout << "Enter new value:";
                cin >> v;
                if (tree.update(k, v)) {
                    cout << "Element Updated Successfully" << endl;
                } else {
                    cout << "Element Not Present" << endl;
                }
                break;
            case 4:
                cout << "Enter key to Delete:";
                cin >> k;
                if (tree.delete_key(k)) {
                    cout << "Element Deleted Successfully" << endl;
                } else {
                    cout << "Element Not Present" << endl;
                }
                break;
            case 5:
                cout << "Data in Descending order is " << endl;
                tree.display(tree.root);
                break;
            case 6:
                cout << "Data in Ascending order is " << endl;
                tree.display_asc(tree.root);
                break;
            case 0:
                cout << "Thank You!" << endl;
                break;
            default:
                cout << "Please Enter a valid choice" << endl;
                break;
        }
    } while (ch != 0);

    return 0;
}

/*
1
akhilesh mali
1
shivam thorat
1
parth desai
1
omkar chougule
1
yash jadhav
1
zara company
1
petha seth
1
aakbar raja


         akhilesh
        /        \
    aakbar      shivam
                /     \
            parth     yash
            /   \        \
        omkar  petha     zara


*/