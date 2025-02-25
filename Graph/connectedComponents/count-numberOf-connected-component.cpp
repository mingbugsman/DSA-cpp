#include<bits/stdc++.h>
using namespace std;


int n,m;

vector<int> adj[1001];

bool visited[1001];

void dfs(int u) {
    visited[u] = true;
    cout << u << " ";
    for (int x : adj[u]) {
        if (!visited[x]) dfs(x);
    }
    cout << endl;
}

void connectedComponent() {
    int ans = 0;
    memset(visited, false, sizeof(visited));
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            cout << "cac dinh thuoc thanh phan lien thong thu " << ans << " : ";
            ans++;
            dfs(i);
        }

    }
    if (ans == 1) {
        cout << "do thi lien thong" << endl;
    }
    else cout << "do thi khong lien thong";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    connectedComponent();
    return 0;
}