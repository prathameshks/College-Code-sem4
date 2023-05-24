/*You have a business with several offices; you want to lease phone lines to
connect them up with each other; and the phone company charges different amounts
of money to connect different pairs of cities. You want a set of lines that
connects all your offices with a minimum total cost. Solve the problem by
suggesting appropriate data structures*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class graph {
   private:
    vector<vector<int>> ajd_matrix;
    vector<string> cities;
    vector<vector<int>> mst;
    int num_of_vertices;
    int weight_of_mst;

   public:
    graph();

    bool notin(vector<int> b, int a) {
        for (int element : b) {
            if (element == a) return false;
        }
        return true;
    }

    int city_count() { return num_of_vertices; }

    void prims_algo(int start_city) {
        vector<int> visited;
        weight_of_mst = 0;
        visited.push_back(start_city);

        while (visited.size() != num_of_vertices) {
            int min_line = INT32_MAX;
            int min_to = 0;
            int min_from = 0;
            for (int from_city : visited) {
                for (int to_city = 0; to_city < num_of_vertices; to_city++) {
                    if (notin(visited, to_city)) {
                        if (ajd_matrix[from_city][to_city] < min_line) {
                            min_line = ajd_matrix[from_city][to_city];
                            min_to = to_city;
                            min_from = from_city;
                        }
                    }
                }
            }
            visited.push_back(min_to);
            mst.push_back({min_from, min_to});
            weight_of_mst += ajd_matrix[min_from][min_to];
        }
    }

    void display_mst() {
        for (auto edge : mst) {
            cout << cities[edge[0]] << " to " << cities[edge[1]] << " = "
                 << ajd_matrix[edge[0]][edge[1]] << endl;
        }
        cout << "\n Weight of MST is " << weight_of_mst << endl;
    }
};

graph::graph() {
    string city;
    cout << "Enter number of Cities: ";
    cin >> num_of_vertices;
    ajd_matrix.resize(num_of_vertices);
    for (int i = 0; i < num_of_vertices; i++) {
        ajd_matrix[i].resize(num_of_vertices);
        ajd_matrix[i][i] = INT16_MAX;
        cout << "Enter city name: ";
        cin >> city;
        cities.push_back(city);
    }
    int cost;
    for (int i = 0; i < num_of_vertices; i++) {
        for (int j = i + 1; j < num_of_vertices; j++) {
            cout << "Enter Cost of line Between city " << cities[i] << " and "
                 << cities[j] << "(-1 for no line): ";
            cin >> cost;
            if (cost == -1) {
                ajd_matrix[i][j] = INT32_MAX;
                ajd_matrix[j][i] = INT32_MAX;
            } else {
                ajd_matrix[i][j] = cost;
                ajd_matrix[j][i] = cost;
            }
        }
    }
}

int main() {
    int start_city;
    graph g;
    cout << "Enter starting city of network: ";
    cin >> start_city;
    if (start_city >= g.city_count()) {
        cout << "City not found considering first city ie 0" << endl;
        start_city = 0;
    }

    g.prims_algo(start_city);

    g.display_mst();
    return 0;
}

/*
5
a
b
c
d
e
5
6
-1
-1
4
3
-1
8
-1
5
*/