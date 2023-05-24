#ifndef Bidirectional_Search
#define Bidirectional_Search

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>


class Graph{

    // add member containers

    //vector<vi> mazeGraph;


    public:

    void BDS(vector<vi> mazeGraph, vector<pair<int,int>> nodeToIndex, int numberOfVertices, int source, int destination, vector<vi> weight);
    void BFS(vector<vi> mazeGraph, list<int> &queue, bool* isVisited, int* previous);
    int visitedIntersect(int numberOfVertices, bool* forward_visited, bool* backward_visited);
    void printPathBDS(vector<vi> mazeGraph, vector<pair<int,int>> nodeToIndex, vector<vi> weight, int source, int destination, int* forward_previous, int* backward_previous, int intersectNode);
    void printQueue(list<int> queue);
    void printCoordinate(list<int> path, vector<pair<int, int>> nodeToIndex);

};


// Overloaded constructor
// Graph::Graph(vector<vi> mazeGraph){

//     this->mazeGraph = mazeGraph;

// }


int Graph::visitedIntersect(int numberOfVertices, bool* forward_visited, bool* backward_visited){

    int currentNode;

    for(currentNode = numberOfVertices-1; currentNode >= 0; --currentNode)
    {

        if(forward_visited[currentNode] and forward_visited[currentNode] == backward_visited[currentNode])
            return currentNode;

    }

    return -1;

}


void Graph::printQueue(list<int> queue){
    
    cout<<"queue: "<<endl;

    list<int>:: iterator i;

    for(i = queue.begin(); i != queue.end(); ++i){
        cout<< *i <<" ";
    }

    cout<<endl;
}

// needs fixing maybe
void Graph::BFS(vector<vi> mazeGraph, list<int> &queue, bool* isVisited, int* previous){

    // mazeGraph

    //list<int> queue;
    //vector<bool> isVisited(numberOfVertices, false);
    //vi previousNode(numberOfVertices, -1);

    //queue.push_back(startVertex);  // ***

    if(queue.empty())
        return;

    //printQueue(queue);

    int current = queue.front();
    queue.pop_front();

    //cout<<"current: "<<current<<endl;
    //cout<<"visited? "<<current<<" : "<<isVisited[current]<<endl;

    //vi::iterator i;

    //cout<<"3 visited in BFS: "<< isVisited[3]<<endl;

    for(auto i: mazeGraph[current]){

        //cout<<"check1"<<endl;
        // cout<<"element: "<<i<<endl;
        // cout<<"element visited: "<<i<<" : "<<isVisited[i]<<endl;
        
        if(!isVisited[i]){
            previous[i] = current;
            isVisited[i] = true;
            queue.push_back(i);

            // cout<<"in"<<endl;
            // cout<<"prev: "<<previous[i]<<endl;
            // cout<<"visit: "<<isVisited[previous[i]]<<endl;
            // cout<<"update: "<<endl;
        }

    }

}


void Graph::BDS(vector<vi> mazeGraph, vector<pair<int,int>> nodeToIndex, int numberOfVertices, int source, int destination, vector<vi> weight){

    bool forward_visited[numberOfVertices];
    bool backward_visited[numberOfVertices];

    int forward_previous[numberOfVertices];
    int backward_previous[numberOfVertices];

    int intersectNode = -1;

    for(int i=0; i<numberOfVertices; ++i){
        forward_visited[i] = false;
    }

    for(int i=0; i<numberOfVertices; ++i){
        backward_visited[i] = false;
    }

    // for(int i=0; i<numberOfVertices; ++i){
    //     cout<<"forward "<<i<<" "<<" visited: "<<forward_visited[i]<<endl;
    // }
    // cout<<endl;

    // for(int i=0; i<numberOfVertices; ++i){
    //     cout<<"backward "<<i<<" "<<" visited: "<<backward_visited[i]<<endl;
    // }
    // cout<<endl;

    list<int> forward_queue, backward_queue;

    forward_visited[source] = true;
    forward_previous[source] = -1;
    forward_queue.push_back(source);

    backward_visited[destination] = true;
    backward_previous[destination] = -1;
    backward_queue.push_back(destination);

    //cout<<"visited 3 here: "<<forward_visited[3]<<endl;

    //return;//

    while(!forward_queue.empty() and !backward_queue.empty())
    {

        // traversing from front
        BFS(mazeGraph, forward_queue, forward_visited, forward_previous);


        // traversing from back
        BFS(mazeGraph, backward_queue, backward_visited, backward_previous);

        intersectNode = visitedIntersect(numberOfVertices, forward_visited, backward_visited);

        if(intersectNode != -1){
            cout<<"Intersect at "<<intersectNode<<endl;
            printPathBDS(mazeGraph, nodeToIndex, weight, source, destination, forward_previous, backward_previous, intersectNode);     // left
            return;
        }

    }

}


void Graph::printPathBDS(vector<vi> mazeGraph, vector<pair<int, int>> nodeToIndex, vector<vi> weight,  int source, int destination, int* forward_previous, int* backward_previous, int intersectNode){

    int currentNode, pathLength = 0;

    list<int> path;

    currentNode = intersectNode;

    while(currentNode != -1){

        path.push_front(currentNode);

        int previousNode = forward_previous[currentNode];

        if(previousNode != -1){
            pathLength += weight[currentNode][previousNode];
        }

        currentNode = previousNode;

    }

    currentNode = intersectNode;

    while(currentNode != -1){

        path.push_back(currentNode);

        int previousNode = backward_previous[currentNode];

        if(previousNode != -1){
            pathLength += weight[currentNode][previousNode];
        }

        currentNode = previousNode;
    }

    vector<int>:: iterator i;

    cout<<"Length of the path is: "<<pathLength<<endl;

    cout<<"The path is: "<<endl;

    for(auto i = path.begin(); i != path.end(); ++i){
        cout<<*i<<"  ";
    }

    cout<<endl;

    printCoordinate(path, nodeToIndex);

}

// yet to fix
void Graph::printCoordinate(list<int> path, vector<pair<int, int>> nodeToIndex){

    vector<int>:: iterator i;

    cout<<"Path as coordinates in the maze: "<<endl;

    for(auto i = path.begin(); i != path.end(); ++i){
        cout<<"("<<nodeToIndex[*i].first<<", "<<nodeToIndex[*i].second<<") --> ";
    }

    cout<<endl;
}


#endif