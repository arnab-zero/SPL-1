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
    void BDS(vector<vi> mazeGraph, int numberOfVertices, int source, int destination);
    void BFS(vector<vi> mazeGraph, list<int> &queue, bool* isVisited, int* previous);
    int visitedIntersect(int numberOfVertices, bool* forward_visited, bool* backward_visited);
    void printPathBDS();
    void printQueue(list<int> queue);
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
        cout<<"element: "<<i<<endl;
        cout<<"element visited: "<<i<<" : "<<isVisited[i]<<endl;
        
        if(!isVisited[i]){
            previous[i] = current;
            isVisited[i] = true;
            queue.push_back(i);

            // cout<<"in"<<endl;
            // cout<<"prev: "<<previous[i]<<endl;
            // cout<<"visit: "<<isVisited[previous[i]]<<endl;
            // cout<<"update: "<<endl;
        }

        printQueue(queue);

    }

}


void Graph::BDS(vector<vi> mazeGraph, int numberOfVertices, int source, int destination){

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
            printPathBDS();     // left
            return;
        }

    }

}


void Graph::printPathBDS(){

    



}


#endif