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

class graph {
    int no_of_vertices;
    int no_of_edges;
    vector<int> vertices;
    vector<vector<int>> adj_list;
    vector<vector<int>> adj_matrix;

   public:
    graph() {
        cout << "Enter the number of vertices: ";
        cin >> no_of_vertices;
        cout << "Enter number of edges: ";
        cin >> no_of_edges;
        vertices = {};
        adj_list.resize(no_of_vertices);
        for (int i = 0; i < no_of_vertices; i++) {
            adj_matrix.push_back(vector<int>(no_of_vertices, 0));
        }

        for (int i = 0; i < no_of_vertices; i++) {
            add_vertex(i);
        }
        for (int i = 0; i < no_of_edges; i++) {
            cout << "Enter the vertices of the edge: ";
            int vertex1, vertex2;
            cin >> vertex1 >> vertex2;
            add_edge(vertex1, vertex2);
        }
    }
    void add_vertex(int vertex) { vertices.push_back(vertex); }
    void add_edge(int vertex1, int vertex2) {
        adj_list[vertex1].push_back(vertex2);
        adj_list[vertex2].push_back(vertex1);
        adj_matrix[vertex1][vertex2] = 1;
        adj_matrix[vertex2][vertex1] = 1;
    }
    void print_adj_list() {
        for (int i = 0; i < no_of_vertices; i++) {
            cout << vertices[i] << "->";
            for (int j = 0; j < adj_list[i].size() - 1; j++) {
                cout << adj_list[i][j] << "->";
            }
            cout << adj_list[i].back() << endl;
        }
    }
    void print_adj_matrix() {
        for (int i = 0; i < no_of_vertices; i++) {
            for (int j = 0; j < no_of_vertices; j++) {
                cout << adj_matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void bfs(int start_vertex) {
        vector<int> visited(no_of_vertices, 0);
        // vector<int> queue;
        queue<int> q;
        q.push(start_vertex);
        visited[start_vertex] = 1;
        while (!q.empty()) {
            int vertex = q.front();
            cout << vertex << " ";
            q.pop();
            for (int i = 0; i < adj_list[vertex].size(); i++) {
                if (visited[adj_list[vertex][i]] == 0) {
                    q.push(adj_list[vertex][i]);
                    visited[adj_list[vertex][i]] = 1;
                }
            }
        }
    }

    void dfs(int start_vertex) {
        vector<int> visited(no_of_vertices, 0);
        stack<int> s;
        s.push(start_vertex);
        visited[start_vertex] = 1;
        while (!s.empty()) {
            int vertex = s.top();
            s.pop();
            cout << vertex << " ";
            for (int i = 0; i < no_of_vertices; i++) {
                if (i != vertex && adj_matrix[vertex][i] == 1 &&
                    visited[i] == 0) {
                    s.push(i);
                    visited[i] = 1;
                }
            }
        }
    }
};

int main() {
    graph g;
    cout << endl;
    cout << "Adjacency List Representation is :" << endl;
    g.print_adj_list();
    cout << endl;
    cout << "Matrix Representation is :" << endl;
    g.print_adj_matrix();
    cout << endl;
    cout << "Enter the starting vertex for BFS: ";
    int start_vertex;
    cin >> start_vertex;
    cout << "BFS: ";
    g.bfs(start_vertex);
    cout << endl;
    cout << endl;
    cout << "Enter the starting vertex for DFS: ";
    cin >> start_vertex;
    cout << "DFS: ";
    g.dfs(start_vertex);
    cout << endl;

    return 0;
}

// 7 11 0 1 0 3 1 5 1 2 1 3 2 5 1 6 2 3 2 4 3 4 4 6 1 1
