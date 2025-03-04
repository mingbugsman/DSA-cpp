#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>

using namespace std;

class Graph {
private:
    unordered_map<char, vector<char>> adjList;

    void dfsRecursive(char v, set<char> &visited) {
        if (visited.count(v)) return;

        cout << v << " ";
        visited.insert(v);

        for (char neighbor : adjList[v]) {
            dfsRecursive(neighbor, visited);
        }
    }

public:
    void addVertex(char v) {
        adjList[v]; 
    }

    void addEdge(char v, char w) {
        adjList[v].push_back(w);
}

    void bfs(char start) {
        set<char> visited;
        queue<char> q;

        q.push(start);
        visited.insert(start);

        while (!q.empty()) {
            char v = q.front();
            q.pop();
            cout << v << " ";

            for (char neighbor : adjList[v]) {
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    void dfs(char start) {
        set<char> visited;
        dfsRecursive(start, visited);
        cout << endl;
    }
};

int main() {
    Graph graph;
    graph.addVertex('S');
    graph.addVertex('A');
    graph.addVertex('B');
    graph.addVertex('C');
    graph.addVertex('D');
    graph.addVertex('E');
    graph.addVertex('F');
    graph.addVertex('G');

    graph.addEdge('S', 'A');
    graph.addEdge('S', 'B');
    graph.addEdge('S', 'C');
    graph.addEdge('A', 'D');
    graph.addEdge('D', 'G');
    graph.addEdge('B', 'E');
    graph.addEdge('C', 'F');

    cout << "BFS FROM S: ";
    graph.bfs('S');

    cout << "DFS FROM S: ";
    graph.dfs('S');

    return 0;
}
