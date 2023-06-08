/*
Represent a given graph using adjacency matrix/list to perform DFS and using
adjacency list to perform BFS. Use the map of the area around the college as the
graph. Identify the prominent land marks as nodes and perform DFS and BFS on
that.
*/

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
#define MAX 10

class graph {
   private:
    int adj_mat[MAX][MAX] = {0};
    vector<vector<int>> adj_list;
    int n;

   public:
    graph(int n) {
        this->n = n;
        adj_list.resize(n);
    }
    void insert(int edge_count) {
        int i, j;
        for (int k = 0; k < edge_count; k++) {
            cout << "Enter vertex of edge :";
            cin >> i >> j;
            adj_mat[i][j] = 1;
            adj_mat[j][i] = 1;
            adj_list[i].push_back(j);
            adj_list[j].push_back(i);
        }
    }
    void print_adj_list() {
        for (int i = 0; i < n; i++) {
            cout << i << "->";
            for (int j = 0; j < adj_list[i].size(); j++) {
                cout << adj_list[i][j] << "->";
            }
            cout << "NULL" << endl;
        }
    }
    void print_adj_matrix() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << adj_mat[i][j] << " ";
            }
            cout << endl;
        }
    }

    

    void bfs() {
        queue<int> s;
        vector<int> visited(n, 0);
        s.push(0);
        while (!s.empty()) {
            int i = s.front();
            s.pop();
            if (!visited[i]) {
                cout << i << " ";
                visited[i] = 1;
                for (int j:adj_list[i]) {
                    if (!visited[j] && j != i) {
                        s.push(j);
                    }
                }
            }
        }
        cout << endl;
    }

    void dfs() {
        stack<int> s;
        vector<int> visited(n, 0);
        s.push(0);
        while (!s.empty()) {
            int i = s.top();
            s.pop();
            if (!visited[i]) {
                cout << i << " ";
                visited[i] = 1;
                for (int j = 0; j < n; j++) {
                    if (!visited[j] && j != i && adj_mat[i][j] == 1) {
                        s.push(j);
                    }
                }
            }
        }
        cout << endl;
    }
};

int main() {
    // code here
    graph g(7);
    g.insert(11);
    // g.print_adj_matrix();
    // g.print_adj_list();
    g.dfs();
    g.bfs();
    return 0;
}

// 0 1 0 3 1 5 1 2 1 3 2 5 1 6 2 3 2 4 3 4 4 6