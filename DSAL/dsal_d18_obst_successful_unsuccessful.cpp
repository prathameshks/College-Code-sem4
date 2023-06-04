#include <iomanip>
#include <iostream>

using namespace std;

#define MAX_NODES 10

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
    int keys[MAX_NODES] = {0};          // for storing keys
    int p[MAX_NODES] = {0};             // for storing frequencies
    int q[MAX_NODES] = {0};             // for storing frequencies
    int n;                              // count of nodes
    int c[MAX_NODES][MAX_NODES] = {0};  // cost matrix
    int w[MAX_NODES][MAX_NODES] = {0};  // cost matrix
    int r[MAX_NODES][MAX_NODES] = {0};  // cost matrix
    node* root;
    // initialize the values
    OBST(int count, int keys_arr[], int p_arr[], int q_arr[]) {
        root = NULL;
        n = count;
        for (int i = 0; i <= n; i++) {
            this->keys[i] = keys_arr[i];
            this->p[i] = p_arr[i];
            this->q[i] = q_arr[i];
        }
    }

    // display matrix
    void display_matrix(int mat[MAX_NODES][MAX_NODES]) {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (i <= j) {
                    cout << setw(2) << mat[i][j] << " ";
                } else {
                    cout << "   ";
                }
            }
            cout << endl;
        }
    }

    int get_w(int i, int j) {
        if (i >= j) {
            return q[i];
        }
        return w[i][j - 1] + p[j] + q[j];
    }

    // generate cost matrix
    void generate_cost_table() {
        // initialize diagonal
        for (int i = 0; i <= n; i++) {
            c[i][i] = 0;
            r[i][i] = 0;
            w[i][i] = q[i];
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
                    int cost = c[i][k - 1] + c[k][j];
                    if (cost < min_cost) {
                        min_cost = cost;
                        min_root = k;
                    }
                }

                // updating the c matrix
                w[i][j] = get_w(i, j);
                c[i][j] = min_cost + w[i][j];
                r[i][j] = min_root;

                // cout<<i<<j<<endl;
                // cout << "w=" << w[i][j] << endl;
                // cout << "c=" << c[i][j] << endl;
                // cout << "r=" << r[i][j] << endl;

                i++;
                j++;
            }
        }
        cout << "Matrix C" << endl;
        display_matrix(c);
        cout << "Matrix W" << endl;
        display_matrix(w);
        cout << "Matrix R" << endl;
        display_matrix(r);
    }

    // get node for [i,j]
    node* get_node(int i, int j) {
        if (i == j) {
            return NULL;
        }

        int rij = r[i][j];
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
        cout<<"PreOrder Traversal Is"<<endl;
        pre_order(root);
        cout << endl;
    }
};

int main() {
    int k[] = {0, 10, 20, 30, 40};
    int p[] = {0, 3, 3, 1, 1};
    int q[] = {2, 3, 1, 1, 1};
    OBST o(4, k, p, q);
    o.generate_cost_table();
    o.generate_obst();
    return 0;
}