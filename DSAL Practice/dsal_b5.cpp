/*
A book consists of chapters, chapters consist of sections and sections consist
of subsections. Construct a tree and print the nodes. Find the time and space
requirements of your method.
*/

#include <iostream>
#include <vector>
using namespace std;

class node {
   public:
    string data;
    vector<node*> childs;
    node(string data = "") {
        this->data = data;
        childs.clear();
    }
};

class Book {
    node* root;

   public:
    Book(string bookname) { root = new node(bookname); }

    bool addChapter(string chName) {
        if (root == NULL) {
            return false;
        }
        for (auto n : root->childs) {
            if (n->data == chName) {
                return false;
            }
        }
        node* temp = new node(chName);
        root->childs.push_back(temp);
        return true;
    }

    bool addSection(int chNo, string secName) {
        if (chNo > root->childs.size()) {
            return false;
        }
        node* ch = root->childs[chNo - 1];
        for (auto n : ch->childs) {
            if (n->data == secName) {
                return false;
            }
        }
        node* temp = new node(secName);
        ch->childs.push_back(temp);
        return true;
    }

    bool addSubSection(int chNo, int secNo, string subSecName) {
        if (chNo > root->childs.size()) {
            return false;
        }
        node* ch = root->childs[chNo - 1];
        if (secNo > ch->childs.size()) {
            return false;
        }
        node* sec = ch->childs[secNo - 1];
        for (auto n : sec->childs) {
            if (n->data == subSecName) {
                return false;
            }
        }
        node* temp = new node(subSecName);
        sec->childs.push_back(temp);
        return true;
    }

    void print(string name, node* n) {
        if (n == NULL) {
            return;
        }
        cout << name << " - " << n->data << endl;
        string nextname;
        if (name == "Book") {
            nextname = "Chapter";
        } else if (name == "Chapter") {
            nextname = "Section";
        } else if (name == "Section") {
            nextname = "Sub Section";
        } else {
            return;
        }

        for (auto t : n->childs) {
            print(nextname, t);
        }
    }

    void display() {
        if (root == NULL) {
            cout << "Book is empty" << endl;
        } else {
            print("Book", root);
        }
    }
};

int main() {
    // code here
    Book b("DSA advanced");
    cout << "addChapter(intro)" << " - " << b.addChapter("intro") << endl;
    cout << "addChapter(intro)" << " - " << b.addChapter("intro") << endl;
    cout << "addChapter(tree)" << " - " << b.addChapter("tree") << endl;
    cout << "addChapter(graph)" << " - " << b.addChapter("graph") << endl;

    cout << "addSection(1,connected)" << " - " << b.addSection(1,"connected") << endl;
    cout << "addSection(1,dis connected)" << " - " << b.addSection(1,"dis connected") << endl;
    
    cout << "addSection(2,General)" << " - " << b.addSection(2,"General") << endl;
    cout << "addSection(2,Binary)" << " - " << b.addSection(2,"Binary") << endl;

    cout << "addSubSection(1,1,graph 1)" << " - " << b.addSubSection(1,1,"graph 1") << endl;
    cout << "addSubSection(1,1,graph 2)" << " - " << b.addSubSection(1,1,"graph 2") << endl;
    cout << "addSubSection(1,1,graph 2)" << " - " << b.addSubSection(1,1,"graph 2") << endl;

    cout << "addSubSection(2,1,Tree General)" << " - " << b.addSubSection(2,1,"Tree General") << endl;
    cout << "addSubSection(2,2,BST)" << " - " << b.addSubSection(2,2,"BST") << endl;
    cout << "addSubSection(2,2,AVL)" << " - " << b.addSubSection(2,2,"AVL") << endl;
    cout << "addSubSection(2,2,OBST)" << " - " << b.addSubSection(2,2,"OBST") << endl;
    cout << "addSubSection(2,2,OBST)" << " - " << b.addSubSection(2,2,"OBST") << endl;
    
    
    b.display();
    return 0;
}