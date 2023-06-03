/*
You have a business with several offices; you want to lease phone lines to
connect them up with each other; and the phone company charges different amounts
of money to connect different pairs of cities. You want a set of lines that
connects all your offices with a minimum total cost. Solve the problem by
suggesting appropriate data structures.
*/
#include <iostream>
#include <vector>
#define MAX_NUM_CITIES 10

using namespace std;

struct edge {
    int start;
    int end;
    int wt;
};

class graph {
    int adj_mat[MAX_NUM_CITIES][MAX_NUM_CITIES] = {0};
    string city_names[MAX_NUM_CITIES];
    int city_count;
    edge mst[MAX_NUM_CITIES - 1];
    void add_to_list(vector<edge> &, edge);
    int cost;

   public:
    graph();

    void prims_algo(int);
    void display_mst();
};

void graph::add_to_list(vector<edge> &list, edge e) {
    list.push_back(e);
    for (int i = list.size() - 1; i > 0; i--) {
        if (list[i].wt < list[i - 1].wt) {
            swap(list[i], list[i - 1]);
        } else {
            break;
        }
    }
}

graph::graph() {
    cost = 0;
    cout << "Enter Number of Cities(1-" << MAX_NUM_CITIES << "):";
    cin >> city_count;
    city_count = (city_count > MAX_NUM_CITIES) ? MAX_NUM_CITIES : city_count;

    for (int i = 0; i < city_count; i++) {
        cout << "Enter City " << i + 1 << ":";
        cin >> city_names[i];
    }

    // initialize all matrix with max value
    for (int i = 0; i < city_count; i++)
        for (int j = 0; j < city_count; j++) adj_mat[i][j] = INT32_MAX;

    int num_pairs;
    cout << "Enter number of City Pairs:";
    cin >> num_pairs;
    cout << "City Codes Are" << endl;
    for (int i = 0; i < city_count; i++) {
        cout << i << " - " << city_names[i] << endl;
    }
    int x, y, wt;
    for (int i = 0; i < num_pairs; i++) {
        cout << "Enter Pair " << i + 1 << ":";
        cin >> x >> y;
        cout << "Enter Cost Between City " << city_names[x] << " & City "
             << city_names[y] << ":";
        cin >> wt;
        adj_mat[x][y] = wt;
        adj_mat[y][x] = wt;
    }
}

void graph::prims_algo(int start) {
    bool visited[MAX_NUM_CITIES] = {0};
    int visited_count = 1;
    visited[start] = 1;
    vector<edge> adj;
    for (int i = 0; i < city_count; i++) {
        if (adj_mat[start][i] != INT32_MAX) {
            edge e;
            e.start = start;
            e.end = i;
            e.wt = adj_mat[start][i];
            add_to_list(adj, e);
        }
    }

    while (visited_count != city_count) {
        edge m = adj.front();
        adj.erase(adj.begin());
        if (!visited[m.end]) {
            mst[visited_count - 1] = m;
            cost += m.wt;
            for (int i = 0; i < city_count; i++) {
                if (adj_mat[m.end][i] != INT32_MAX) {
                    edge e;
                    e.start = m.end;
                    e.end = i;
                    e.wt = adj_mat[e.start][i];
                    add_to_list(adj, e);
                }
            }
            visited[m.end] = 1;
            visited_count++;
        }
    }
}

void graph::display_mst() {
    cout << "The Most Efficient Network is " << endl;

    for (int i = 0; i < city_count - 1; i++) {
        cout << city_names[mst[i].start] << " to " << city_names[mst[i].end]
             << " of weight " << mst[i].wt << endl;
    }
    cout << endl << "The cost of network is " << cost << endl;
}

int main() {
    // prims algo
    graph g;
    int start;
    cout << "Enter Start City:";
    cin >> start;
    start = (start > MAX_NUM_CITIES - 1) ? 0 : start;
    g.prims_algo(start);
    g.display_mst();
    return 0;
}

/* example 1
4
a
b
c
d
6
0 1 2
0 2 3
0 3 6
1 2 4
1 3 5
2 3 7
1
*/

/* example 2
7
1
2
3
4
5
6
7
9
0 1 28
0 5 10
1 6 14
1 2 16
2 3 12
3 4 22
3 6 18
4 6 24
4 5 25
0
*/

/*
4
a
b
c
d
4
0 1 2
1 2 3
2 3 1
3 0 3

*/