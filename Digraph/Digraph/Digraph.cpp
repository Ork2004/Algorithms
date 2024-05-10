#include <iostream>
#include <vector>

class Edge {
public:
    int start;
    int end;
    int weight;

    Edge(int start, int end, int weight) : start(start), end(end), weight(weight) {}
};

template<typename T>
class Vertex {
public:
    T id;
    std::vector<Edge> edges;

    int startTime;
    int finishTime;

    Vertex(T id) : id(id), startTime(-1), finishTime(-1) {}
};


template<typename T>
class Graph {
public:
    std::vector<Vertex<T>> vertices;
    std::vector<std::vector<int>> incidenceMatrix;

    Graph(int numVertices) : vertices(numVertices, Vertex<T>(-1)) {
        incidenceMatrix.resize(numVertices, std::vector<int>(numVertices, 0));
        for (int i = 0; i < numVertices; ++i) {
            vertices[i].id = i;
        }
    }

    void addEdge(int start, int end, int weight) {
        if (start < 0 || start >= vertices.size() || end < 0 || end >= vertices.size()) {
            std::cerr << "Invalid vertex index." << std::endl;
            return;
        }
        vertices[start].edges.push_back(Edge(start, end, weight));
        incidenceMatrix[start][end] = weight;
    }

    void Dijkstra(int source) {
        std::vector<int> dist(vertices.size(), INT_MAX);
        std::vector<bool> visited(vertices.size(), false);
        dist[source] = 0;

        for (int count = 0; count < vertices.size() - 1; ++count) {
            int u = minDistance(dist, visited);
            visited[u] = true;

            for (const Edge& edge : vertices[u].edges) {
                int v = edge.end;
                if (!visited[v] && dist[u] != INT_MAX && dist[u] + edge.weight < dist[v]) {
                    dist[v] = dist[u] + edge.weight;
                }
            }
        }

        std::cout << "Shortest distances from vertex " << source << ":\n";
        for (int i = 0; i < vertices.size(); ++i) {
            std::cout << "Vertex " << i << ": " << dist[i] << std::endl;
        }
    }

    void DFSVisit(Vertex<T>* u, int& time) {
        time++;
        u->startTime = time;

        for (const Edge& edge : u->edges) {
            Vertex<T>* v = &vertices[edge.end];
            if (v->startTime == -1) {
                DFSVisit(v, time);
            }
        }

        time++;
        u->finishTime = time;
    }

    void DFS(int startVertex) {
        int time = 0;
        Vertex<T>* startNode = &vertices[startVertex];
        DFSVisit(startNode, time);
    }

private:

    int minDistance(const std::vector<int>& dist, const std::vector<bool>& visited) {
        int min = INT_MAX, minIndex;

        for (int v = 0; v < vertices.size(); ++v) {
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                minIndex = v;
            }
        }

        return minIndex;
    }
};


int main() {
    Graph<int> graph(6);

    graph.addEdge(0, 1, 5);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 8);
    graph.addEdge(1, 4, 2);
    graph.addEdge(2, 5, 4);
    graph.addEdge(3, 4, 1);
    graph.addEdge(4, 5, 6);

    std::cout << "\Dijkstra:\n";
    graph.Dijkstra(0);

    std::cout << "\nDFS:\n";
    graph.DFS(0);

    std::cout << "Start and Finish times:\n";
    for (const auto& vertex : graph.vertices) {
        std::cout << "Vertex " << vertex.id << ": ";
        std::cout << "Start: " << vertex.startTime << ", Finish: " << vertex.finishTime << std::endl;
    }

    return 0;
}

