#include<bits/stdc++.h>
using namespace std;

int n,m, s, t;
vector<int> adj[1001];
bool visited[1001];
int parent[1001];
void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            // remember parent of v is u
            parent[v] = u;
            dfs(v);
        }
    }
}

void bfs(int u) {
    queue<int> q;
    q.push(u);
    visited[u]= true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int x : adj[v]) {
            q.push(x);
            visited[x] = true;
            parent[x] = v;
        }
    }
}

void Path(int s, int t) {
    memset(visited,false,sizeof(visited));
    memset(parent, 0, sizeof(parent));
    dfs(s);
    if (!visited[t]) cout << "khong co duong di ! \n";

    else {
        vector<int> path;
        while (t != s) {
            path.push_back(t);
            t = parent[t];
        }
        path.push_back(s);
        reverse(path.begin(), path.end());
        for (int x :path) cout << x << " ";
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m ; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    cin>> s >> t;
    Path(s,t);
    return 0;
}

/*
10 8
1 2
2 3
2 4
3 6
3 7
6 7
5 8
8 9
1 7
*/