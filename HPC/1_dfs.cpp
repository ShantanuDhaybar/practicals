#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

void dfs(int start, vector<vector<int>>& graph, vector<bool>& visited) {
    stack<int> st;
    visited[start] = true;
    st.push(start);

    while (!st.empty()) {
        int current;
        #pragma omp critical
        {
            current = st.top();
            st.pop();
        }

        cout << current << " ";

        #pragma omp parallel for
        for (int i = 0; i < graph[current].size(); i++) {
            int neighbor = graph[current][i];
            if (!visited[neighbor]) {
                #pragma omp critical
                {
                    visited[neighbor] = true;
                    st.push(neighbor);
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

    cout << "DFS traversal: ";
    dfs(start, graph, visited);
    cout << endl;

    return 0;
}





// The provided code is an implementation of Depth-First Search (DFS) algorithm using OpenMP for parallelization. It performs a DFS traversal on an undirected graph. Let's go through the code step by step:

// The code includes necessary libraries such as <iostream>, <vector>, <stack>, and <omp.h>.

// The code starts with the dfs function definition. This function takes the starting vertex, the graph represented as an adjacency list (vector<vector<int>>), and a boolean vector to keep track of visited vertices.

// Inside the dfs function, a stack (st) is initialized, and the starting vertex is marked as visited and pushed to the stack.

// The DFS traversal is performed using a while loop that continues until the stack is empty.

// Within the while loop, the top element of the stack (st) is retrieved using st.top(), and a critical section (#pragma omp critical) is used to ensure that only one thread accesses the stack at a time. The retrieved element is then removed from the stack using st.pop().

// The current element is printed (cout << current << " ";).

// The neighbors of the current element are traversed, and if a neighbor has not been visited, it is marked as visited and pushed to the stack.

// The main function is defined, which is the entry point of the program.

// The user is prompted to enter the number of vertices and edges in the graph.

// A 2D vector graph is created to represent the adjacency list of the graph, and a boolean vector visited is created to track visited vertices.

// The user is prompted to enter the edges of the graph, and the corresponding adjacency list is updated accordingly.

// The user is prompted to enter the starting vertex for the DFS traversal.

// The DFS traversal is performed by calling the dfs function, passing the starting vertex, graph, and visited vector.

// The DFS traversal is printed to the console.

// The program ends with a return statement.

// Overall, the code implements parallel DFS traversal using OpenMP, allowing multiple threads to process elements in the stack simultaneously.






