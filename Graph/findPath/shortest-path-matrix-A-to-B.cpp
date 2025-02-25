#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

int n, m, startX, startY, endX, endY;
vector<vector<char>> matrix(1001, vector<char>(1001));
vector<vector<bool>> visited(1001, vector<bool>(1001, false));
vector<vector<int>> distances(1001, vector<int>(1001, -1));
int directions[4][2] = {
    {-1, 0}, 
    {1, 0}, 
    {0, -1}, 
    {0, 1}
};



// BFS implementation
bool bfs(int startX, int startY) {
    queue<pair<int, int>> q;
    q.push({startX, startY});
    visited[startX][startY] = true;
    distances[startX][startY] = 0;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if (matrix[x][y] == 'B') {
            return true;
        }

        for (auto& d : directions) {
            int newX = x + d[0], newY = y + d[1];
            if (newX >= 1 && newX <= n && newY >= 1 && newY <= m &&
                matrix[newX][newY] != 'x' && !visited[newX][newY]) {
                q.push({newX, newY});
                visited[newX][newY] = true;
                distances[newX][newY] = distances[x][y] + 1;
            }
        }
    }

    return false;
}

/*
    Mục đích: Tái tạo lại đường đi ngắn nhất từ điểm bắt đầu (startX, startY) đến điểm kết thúc (endX, endY) dựa trên thông tin khoảng cách đã tính toán trong hàm bfs.
*/


vector<pair<int, int>> reconstructPath(int startX, int startY, int endX, int endY) {
    vector<pair<int, int>> path;
    int currentX = endX, currentY = endY;

    while (currentX != startX || currentY != startY) {
        path.push_back({currentX, currentY});
        for (auto& d : directions) {
            int prevX = currentX - d[0];
            int prevY = currentY - d[1];
            if (prevX >= 1 && prevX <= n && prevY >= 1 && prevY <= m && distances[prevX][prevY] == distances[currentX][currentY] - 1) {
                currentX = prevX;
                currentY = prevY;
                break;
            }
        }
    }

    path.push_back({startX, startY});
    reverse(path.begin(), path.end());
    return path;
}


int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> matrix[i][j];
            if (matrix[i][j] == 'A') {
                startX = i;
                startY = j;
            }
            else if (matrix[i][j] == 'B') {
                endX = i;
                endY = j;
            }
        }
    }



    // Use BFS
    if (bfs(startX, startY)) {
        cout << "Shortest path length: " << distances[endX][endY] << endl;
        vector<pair<int, int>> shortestPath = reconstructPath(startX, startY, endX, endY);
        // Print the shortest path
        cout << "Shortest path: ";
        for (auto& p : shortestPath) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    } else {
        cout << "No path exists." << endl;
    }

    return 0;
}


/*
4 4
A o o x
x o o x
x o o o
x B o x
*/