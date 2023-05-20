#ifndef A_STAR_SEARCH_H
#define A_STAR_SEARCH_H

#include<bits/stdc++.h>
using namespace std;

class AStarSearch{

private:
    int row, col, vertexCount;
    vector<vector<int>> graphList;

public:
    AStarSearch(int row, int col, int vertexCount, vector<vector<int>> inputAdjacencyList){
        this->row = row;        // number of rows in the graph.
        this->col = col;        // number of columns in the graph.
        this->vertexCount = vertexCount;

        graphList = inputAdjacencyList;
    }

    void printGraph(){
        cout<<"Adjacency List for the graph is: "<<endl;
        
        for(int i=0; i<vertexCount; ++i){
            cout<<i<<"\t";

            for(auto p: graphList[i]){
                cout<<p<<" ";
            }

            cout<<endl;
        }

        cout<<endl;
    }

    // Creating Node structure
    struct Node {
        int id; // node id
        int g, h; // cost and heuristic values

        Node(int i) : id(i), g(0), h(0) {}

        // Overloading '<' operator for sorting the priority queue
        bool operator<(const Node& other) const {
            return g + h > other.g + other.h;
        }
    };


    private:
    
    // Function to calculate the heuristic value (Euclidean distance) between two nodes
    int calculateHeuristic(int node1, int node2) {

        return abs(node2 - node1);
    }

    // Function to find the shortest path using A* algorithm
    vector<int> aStarFunction(const vector<vector<int>>& graph, int start, int target) {
        int numNodes = graph.size();

        // Check if the start and target nodes are valid
        if (start < 0 || start >= numNodes || target < 0 || target >= numNodes) {
            cout << "Invalid start or target node!" << endl;
            return {};
        }

        // Vector to store the visited nodes
        vector<bool> visited(numNodes, false);

        // Vector to store the path
        vector<int> path(numNodes, -1);

        // Priority queue to store the unvisited nodes
        priority_queue<Node> unvisited;

        // Create a map to store the heuristic values of each node
        unordered_map<int, int> heuristic;

        // Traverse the graph and calculate the heuristic value for each node
        for (int i = 0; i < numNodes; ++i) {
            heuristic[i] = calculateHeuristic(i, target);
        }

        // Create the start node and initialize its cost and heuristic values
        Node startNode(start);
        startNode.g = 0;
        startNode.h = heuristic[start];

        // Push the start node to the unvisited list
        unvisited.push(startNode);

        // Loop until the unvisited list is empty
        while (!unvisited.empty()) {
            // Get the node with the minimum f value from the unvisited list
            Node current = unvisited.top();
            unvisited.pop();

            int nodeId = current.id;

            // Mark the current node as visited
            visited[nodeId] = true;

            // Check if the current node is the target node
            if (nodeId == target) {
                // Generate the path by following the parent nodes from the target node to the start node
                vector<int> finalPath;
                int node = target;
                while (node != -1) {
                    finalPath.push_back(node);
                    node = path[node];
                }

                reverse(finalPath.begin(), finalPath.end());
                return finalPath;
            }

            // Generate all the neighboring nodes
            for (int neighbor : graph[nodeId]) {
                // Check if the neighboring node is not visited
                if (!visited[neighbor]) {
                    // Calculate the g value of the neighboring node
                    int newG = current.g + 1;

                    // Check if the neighboring node is already in the unvisited list
                    // If yes, update its cost value if the new value is better
                    bool inunvisitedList = false;
                    for (Node& node : unvisited) {
                        if (node.id == neighbor) {
                            inunvisitedList = true;
                            if (newG < node.g) {
                                node.g = newG;
                                path[neighbor] = nodeId;
                            }
                            break;
                        }
                    }

                    // If the neighboring node is not in the unvisited list, add it
                    if (!inunvisitedList) {
                        Node neighborNode(neighbor);
                        neighborNode.g = newG;
                        neighborNode.h = heuristic[neighbor];
                        unvisited.push(neighborNode);
                        path[neighbor] = nodeId;
                    }
                }
            }
        }

        // If the unvisited list becomes empty and the target node is not reached, there is no path
        cout << "No path found!" << endl;
        return {};
    }

    // Function to print the path
    void printPath(const vector<int>& path) {
        if (path.empty()) {
            cout << "No path found!" << endl;
            return;
        }

        cout << "Path:" << endl;
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }

};




#endif
