#include <iostream>
#include <vector>
using namespace std;

class HamiltonianPath {
    int V;
    vector<vector<int>> graph;
    vector<bool> visited;

public:
    HamiltonianPath(int V) : V(V) {
        graph.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v) {
        if (u < 0 || v < 0 || u >= V || v >= V) {
            cout << "Canh khong hop le!\n";
            return;
        }
        graph[u][v] = 1;
        graph[v][u] = 1; // Đồ thị vô hướng
    }

    bool hamiltonianPathUtil(int v, int count) {
        if (count == V) return true; // Nếu đi qua tất cả đỉnh thì là đường đi Hamilton
        
        for (int u = 0; u < V; u++) {
            if (graph[v][u] == 1 && !visited[u]) { // Nếu có cạnh và chưa thăm
                visited[u] = true;
                if (hamiltonianPathUtil(u, count + 1)) return true;
                visited[u] = false; // Quay lui
            }
        }
        return false;
    }

    bool hasHamiltonianPath() {
        for (int start = 0; start < V; start++) { // Thử từ mọi đỉnh
            visited.assign(V, false);
            visited[start] = true;
            if (hamiltonianPathUtil(start, 1)) {
                cout << "Ton tai duong di Hamilton bat dau tu dinh " << start << endl;
                return true;
            }
        }
        cout << "Khong ton tai duong di Hamilton.\n";
        return false;
    }
};

int main() {
    cout << "Nhap so dinh: ";
    int n;
    cin >> n;

    HamiltonianPath g(n);
    cout
}