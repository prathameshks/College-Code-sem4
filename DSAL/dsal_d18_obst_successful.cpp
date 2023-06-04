#include <iomanip>
#include <iostream>

using namespace std;

#define MAX_NODES 10

struct cost_pair {
    int cost;
    int root = 0;
};

class node {
   public:
    int data;
    node* left;
    node* right;
    node(int data = 0) {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

class OBST {
   public:
    int keys[MAX_NODES];                // for storing keys
    int freq[MAX_NODES];                // for storing frequencies
    int n;                              // count of nodes
    cost_pair c[MAX_NODES][MAX_NODES];  // cost matrix
    node* root;
    // initialize the values
    OBST(int count, int keys_arr[MAX_NODES], int freq_arr[MAX_NODES]) {
        root = NULL;
        n = count;
        for (int i = 0; i <= n; i++) {
            this->keys[i] = keys_arr[i];
            this->freq[i] = freq_arr[i];
        }
    }

    // function to return weight of (i,j)
    int get_w(int i, int j) {
        int w = 0;
        for (int ind = i + 1; ind <= j; ind++) {
            w += freq[ind];
        }
        return w;
    }

    // display c matrix
    void display_c() {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (i <= j) {
                    cout << setw(2) << c[i][j].cost << "-" << c[i][j].root
                         << " ";
                } else {
                    cout << "  -  ";
                }
            }
            cout << endl;
        }
    }

    // generate cost matrix
    void generate_cost_table() {
        // initialize diagonal to 0
        for (int i = 0; i <= n; i++) {
            c[i][i].cost = 0;
            c[i][i].root = 0;
        }

        // for j-i = 0 to n
        for (int diff = 1; diff <= n; diff++) {
            int i, j;
            i = 0;
            j = i + diff;

            // for each pair with j-i = diff
            while (j <= n) {
                int min_cost = INT32_MAX, min_root;
                // getting minimum cost and root for c[i,j]
                for (int k = i + 1; k <= j; k++) {
                    int cost = c[i][k - 1].cost + c[k][j].cost;
                    if (cost < min_cost) {
                        min_cost = cost;
                        min_root = k;
                    }
                }

                // updating the c matrix
                c[i][j].cost = min_cost + get_w(i, j);
                c[i][j].root = min_root;

                // cout << "c" << i << j << endl;
                i++;
                j++;
            }
        }
        display_c();
    }

    //get node for [i,j]
    node* get_node(int i, int j) {
        if (i == j) {
            return NULL;
        }

        int rij = c[i][j].root;
        node* temp = new node(keys[rij]);
        // left node will be [i,r-1]
        temp->left = get_node(i, rij - 1);
        // right node will be [r,j]
        temp->right = get_node(rij, j);
        return temp;
    }

    void pre_order(node* temp) {
        if (temp != NULL) {
            cout << temp->data << " ";
            pre_order(temp->left);
            pre_order(temp->right);
        }
    }

    void generate_obst() {
        root = get_node(0, n);
        pre_order(root);
        cout << endl;
    }
};

int main() {
    int k[] = {0, 10, 20, 30, 40};
    int f[] = {0, 4, 2, 6, 3};
    OBST o(4, k, f);
    o.generate_cost_table();
    o.generate_obst();
    return 0;
}