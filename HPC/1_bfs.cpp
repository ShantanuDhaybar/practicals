#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

void bfs(int start, vector<vector<int>>& graph, vector<bool>& visited) {
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int size = q.size();

        #pragma omp parallel for
        for (int i = 0; i < size; i++) {
            int current;
            #pragma omp critical
            {
                current = q.front();
                q.pop();
            }

            cout << current << " ";

            for (int j = 0; j < graph[current].size(); j++) {
                int neighbor = graph[current][j];
                if (!visited[neighbor]) {
                    #pragma omp critical
                    {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
        }
    }
}

int main() {
    int vertices, edges;
    cout << "Enter the number of vertices: ";
    cin >> vertices;
    cout << "Enter the number of edges: ";
    cin >> edges;

    vector<vector<int>> graph(vertices);
    vector<bool> visited(vertices, false);

    cout << "Enter the edges (format: vertex1 vertex2):\n";
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int start;
    cout << "Enter the starting vertex: ";
    cin >> start;

    cout << "BFS traversal: ";
    bfs(start, graph, visited);
    cout << endl;

    return 0;
}



// The provided code is an implementation of Breadth-First Search (BFS) algorithm using OpenMP for parallelization. It performs a BFS traversal on an undirected graph. Let's go through the code step by step:

// The code includes necessary libraries such as <iostream>, <vector>, <queue>, and <omp.h>.

// The code starts with the bfs function definition. This function takes the starting vertex, the graph represented as an adjacency list (vector<vector<int>>), and a boolean vector to keep track of visited vertices.

// Inside the bfs function, a queue (q) is initialized, and the starting vertex is marked as visited and added to the queue.

// The BFS traversal is performed using a while loop that continues until the queue is empty.

// Within the while loop, the size of the queue (q) is stored in the variable size.

// The #pragma omp parallel for directive is used to parallelize the loop that processes the elements in the queue. It splits the iterations of the loop across multiple threads.

// Inside the loop, each thread retrieves an element from the queue (q) using q.front(), and a critical section (#pragma omp critical) is used to ensure that only one thread accesses the queue at a time. The retrieved element is then removed from the queue using q.pop().

// The current element is printed (cout << current << " ";).

// The neighbors of the current element are traversed, and if a neighbor has not been visited, it is marked as visited and added to the queue.

// The main function is defined, which is the entry point of the program.

// The user is prompted to enter the number of vertices and edges in the graph.

// A 2D vector graph is created to represent the adjacency list of the graph, and a boolean vector visited is created to track visited vertices.

// The user is prompted to enter the edges of the graph, and the corresponding adjacency list is updated accordingly.

// The user is prompted to enter the starting vertex for the BFS traversal.

// The BFS traversal is performed by calling the bfs function, passing the starting vertex, graph, and visited vector.

// The BFS traversal is printed to the console.

// The program ends with a return statement.

// Overall, the code implements parallel BFS traversal using OpenMP, allowing multiple threads to process elements in the queue simultaneously.





