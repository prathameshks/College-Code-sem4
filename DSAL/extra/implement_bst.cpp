#include <iostream>
using namespace std;


class node{
    public:
    int data;
    node* left,*right;
    node(){
        data = 0;
        left =NULL;
        right =NULL;
    }
    
    node(int val){
        data = val;
        left =NULL;
        right =NULL;
    }
};

class bst{
    public:
    node* root;
    
    bst(){
        root = NULL;
    }
    bst(int data){
        root = new node(data);
    }
    void insert(int elmt){
        
    }
};

int main(){
    
    return 0;
}