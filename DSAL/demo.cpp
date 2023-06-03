#include <iostream>
#include <vector>
#define max_no_cities 10
using namespace std;

struct edge {
    int start;
    int end;
    int wt;
};

class graph {
    int adj_mat[max_no_cities][max_no_cities] = {0};
    int city_cnt;
    string city_name[max_no_cities];
    int cost;
    edge mst[max_no_cities - 1];
    void add_to_list(vector<edge> &, edge);

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
    cout << "Enter the number of cities : ";
    cin >> city_cnt;
    city_cnt = (city_cnt > max_no_cities) ? max_no_cities : city_cnt;
    for (int i = 0; i < city_cnt; i++) {
        cout << "Enter the city " << i + 1 << ":";
        cin >> city_name[i];
    }
    for (int i = 0; i < city_cnt; i++)
        for (int j = 0; j < city_cnt; j++) adj_mat[i][j] = INT32_MAX;

    int num_pairs;
    cout << "Enter the no. city of pairs : ";
    cin >> num_pairs;
    cout << "City codes are : " << endl;
    for (int i = 0; i < city_cnt; i++) {
        cout << i << "-" << city_name[i] << endl;
    }
    int x, y, wt;
    for (int i = 0; i < num_pairs; i++) {
        cout << "ENter the city " << i + 1 << ":";
        cin >> x >> y;
        cout << "enter the cost between " << city_name[x] << " and "
             << city_name[y] << ":";
        cin >> wt;
        adj_mat[x][y] = wt;
        adj_mat[y][x] = wt;
    }
}

void graph::prims_algo(int start) {
    bool visited[max_no_cities] = {0};
    int visited_cnt = 1;
    visited[start] = 1;
    vector<edge> adj;
    for (int i = 0; i < city_cnt; i++) {
        if (adj_mat[start][i] != INT32_MAX) {
            edge e;
            e.start = start;
            e.end = i;
            e.wt = adj_mat[start][i];
            add_to_list(adj, e);
        }
    }

    while (visited_cnt != city_cnt) {
        edge m = adj.front();
        adj.erase(adj.begin());
        if (!visited[m.end]) {
            mst[visited_cnt - 1] = m;
            cost += m.wt;
            for (int i = 0; i < city_cnt; i++) {
                if (adj_mat[start][i] != INT32_MAX) {
                    edge e;
                    e.start = m.end;
                    e.end = i;
                    e.wt = adj_mat[e.start][i];
                    add_to_list(adj, e);
                }
            }
            visited[m.end] = 1;
            visited_cnt++;
        }
    }
}

void graph::display_mst() {
    cout << "The most efficient network is : " << endl;
    for (int i = 0; i < city_cnt - 1; i++) {
        cout << city_name[mst[i].start] << "to" << city_name[mst[i].end]
             << " of weight " << mst[i].wt << endl;
    }
    cout << endl << "the cost of the network is  : " << cost << endl;
}

int main() {
    graph g;
    int start;
    cout << "Enter the start city : ";
    cin >> start;
    start = (start > max_no_cities - 1) ? 0 : start;
    g.prims_algo(start);
    g.display_mst();
    return 0;
}