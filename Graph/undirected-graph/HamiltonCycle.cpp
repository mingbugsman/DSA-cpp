#include <iostream>
#include <vector>
using namespace std;

class HamiltonianCycle {
    int V; // Số đỉnh
    vector<vector<int>> graph; // Ma trận kề
    vector<int> path; // Lưu đường đi Hamilton

public:
    HamiltonianCycle(int V) : V(V) {
        graph.resize(V, vector<int>(V, 0));
        path.resize(V, -1);
    }

    void addEdge(int u, int v) {
        graph[u][v] = 1;
        graph[v][u] = 1; // Đồ thị vô hướng
    }

    // Kiểm tra xem đỉnh v có thể được thêm vào đường đi tại vị trí pos
    bool isSafe(int v, int pos) {
        // Kiểm tra xem v có kề với đỉnh trước đó trong path không
        if (graph[path[pos - 1]][v] == 0) return false;

        // Kiểm tra xem v đã xuất hiện trong path chưa
        for (int i = 0; i < pos; i++) {
            if (path[i] == v) return false;
        }
        return true;
    }

    // Hàm backtracking để tìm chu trình Hamilton
    bool hamiltonianCycleUtil(int pos) {
        // Nếu tất cả các đỉnh đã được thêm vào đường đi
        if (pos == V) {
            // Kiểm tra xem có cạnh quay lại đỉnh bắt đầu không
            return graph[path[pos - 1]][path[0]] == 1;
        }

        // Thử tất cả các đỉnh làm đỉnh tiếp theo trong chu trình
        for (int v = 1; v < V; v++) {
            if (isSafe(v, pos)) {
                path[pos] = v;

                if (hamiltonianCycleUtil(pos + 1)) return true;

                // Backtrack
                path[pos] = -1;
            }
        }
        return false;
    }
    void print() {
        for (int i = 0; i < V; i++) {
            cout << i << " : ";
            for (int u : graph[i]) {
                cout << u << " ";
            }
            cout << endl;
        }
    }

    // Tìm chu trình Hamilton
    void findHamiltonianCycle() {
        path[0] = 0; // Bắt đầu từ đỉnh 0

        if (!hamiltonianCycleUtil(1)) {
            cout << "Không tồn tại chu trình Hamilton.\n";
            return;
        }

        // In chu trình Hamilton
        cout << "Chu trình Hamilton: ";
        for (int i = 0; i < V; i++) {
            cout << path[i] << " ";
        }
        cout << path[0] << endl; // Quay lại đỉnh ban đầu
    }
};

int main() {
    cout << "Nhap so dinh : ";
    int n; cin >> n;
    HamiltonianCycle g(n);
    
    while (true) {
        int x,y;
        cin >> x; cin >> y;
        
        if (x == -1 && y == -1) { //điều kiện dừng nhập input
            break;
        }
        g.addEdge(x,y);
    }
    
    g.print();
    g.findHamiltonianCycle();

    return 0;
}
