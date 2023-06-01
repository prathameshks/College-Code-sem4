/*You have a business with several offices; you want to lease phone lines to
connect them up with each other; and the phone company charges different amounts
of money to connect different pairs of cities. You want a set of lines that
connects all your offices with a minimum total cost. Solve the problem by
suggesting appropriate data structures.(Prim's Algorithm)*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool compare(vector<int> a, vector<int> b) { return a[2] < b[2]; }

class graph {
    vector<vector<int>> matrix;
    int no_of_vertices, no_of_edges;
    vector<vector<int>> edges;
    vector<vector<int>> mst;

   public:
    graph() {
        cout << "Enter Number of Vertices:";
        cin >> no_of_vertices;
        for (int i = 0; i < no_of_vertices; i++) {
            matrix.push_back(vector<int>(no_of_vertices, 0));
        }

        cout << "Enter Number of Edges:";
        cin >> no_of_edges;
        for (int i = 0; i < no_of_edges; i++) {
            int x, y, wt;
            cout << "Enter vertices of edge " << i + 1 << ":";
            cin >> x >> y;
            cout << "Enter weight of Edge:";
            cin >> wt;
            matrix[x][y] = wt;
            matrix[y][x] = wt;
            edges.push_back({x, y, wt});
        }
    }

    void display_matrix() {
        cout << "Matrix is :" << endl;
        for (int i = 0; i < no_of_vertices; i++) {
            for (int j = 0; j < no_of_vertices; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    void display_mst() {
        cout << "MST is :" << endl;
        for (int i = 0; i < mst.size(); i++) {
            for (int j = 0; j < 2; j++) {
                cout << mst[i][j] << " ";
            }
            cout << endl;
        }
    }

    int prims_algo() {
        vector<int> visited(no_of_vertices, 0);
        int weight = 0;
        sort(edges.begin(), edges.end(), compare);
        for (int i = 0; i < no_of_edges; i++) {
            if (visited[edges[i][0]] == 0 or visited[edges[i][1]] == 0) {
                visited[edges[i][0]] = 1;
                visited[edges[i][1]] = 1;
                mst.push_back(edges[i]);
                weight += edges[i][2];
            }
        }
        return weight;
    }
};

int main() {
    // code
    graph g;
    cout << g.prims_algo() << endl;
    g.display_mst();
    return 0;
}

/*
4 6
0 1 5
0 2 4
0 3 6
2 3 1
1 3 5
4 1 2

7 11
0 1 5
0 3 4
1 5 1
1 2 7
1 3 8
2 5 5
1 6 4
2 3 6
2 4 8
3 4 2
4 6 10
1 1 11
*/