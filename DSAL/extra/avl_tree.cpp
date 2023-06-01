#include <iostream>
using namespace std;
#define MAX 10
int find(int, int);
void print(int, int);
int p[MAX], q[MAX], w[10][10], c[10][10], r[10][10], i, j, k, n, m;
char idnt[7][10];

int main()

{
    cout << "enter a number of identifiers : ";
    cin >> n;
    cout << "enter identifiers : ";
    for (i = 1; i <= n; i++) cin >> idnt[i];
    cout << "enter success probability for identifiers : ";
    for (i = 1; i <= n; i++) cin >> p[i];
    cout << "enter failure probability  for identifiers : ";
    for (i = 0; i <= n; i++) cin >> q[i];
    cout << "\n Weight        Cost          Root \n";

    for (i = 0; i <= n; i++) {
        w[i][i] = q[i];
        c[i][i] = r[i][i] = 0;
        cout << "\n"
             << w[i][i] << "          " << c[i][i] << "             "
             << r[i][i];
        cout << "\n------------------------------------------------------------"
                "-------------";
    }
    cout << "\n----------------------------------------------------------------"
            "---------";
    for (i = 0; i < n; i++) {
        j = i + 1;
        w[i][j] = p[j] + q[j] + w[i][i];  // w(i,j)= p[j]+q[i]+w(i,j-1)
        c[i][j] =
            w[i][j] + c[j][j];  // c(i,j)= min { c (i,k-1)+c(k+1, j) }+ w(i,j))
        r[i][j] = j;
        cout << "\n"
             << w[i][j] << "           " << c[i][j] << "              "
             << r[i][j];
        cout << "\n------------------------------------------------------------"
                "-------------";
    }
    cout << "\n----------------------------------------------------------------"
            "---------";
    for (m = 2; m <= n; m++) {
        for (i = 0; i <= n - m; i++) {
            j = i + m;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            k = find(i, j);
            r[i][j] = k;
            c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
            cout << "\n"
                 << w[i][j] << "            " << c[i][j] << "           "
                 << r[i][j] << endl;
        }
    }
    cout << "------------------------------------------------------------------"
            "-------";
    cout << "\n THE FINAL OBST IS : \n ";
    print(0, n);
    return 0;
}
int find(int i, int j) {
    int min = 2000, m, l;  // c[i][j];
    for (m = i + 1; m <= j; m++)
        if (c[i][m - 1] + c[m][j] < min) {
            min = c[i][m - 1] + c[m][j];
            l = m;
        }
    return l;
}
void print(int i, int j) {
    if (i < j)
        cout << "\n" << idnt[r[i][j]];
    else
        return;
    print(i, r[i][j] - 1);
    print(r[i][j], j);
}

/*
4
do
if
read
write
1
3
1
3
1
2
1
1
3

*/