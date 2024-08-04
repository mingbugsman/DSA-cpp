// directed graph
#include <bits/stdc++.h>
using namespace std;


int main() {
    int n,m; cin >> m >> n;
    vector <vector<int>> adjMatrix(n+1, vector<int>(n+1,0));
    for (int i = 0; i < m; i++) {
        int x,y; cin >> x >> y;
        adjMatrix[x][y] = 1;
    }
    for (int i = 1; i <= n ; i++) {
        for (int j = 1; j <= n; j++) {
            cout << adjMatrix[i][j] << " "; 
        }
        cout << endl;
    } 

}