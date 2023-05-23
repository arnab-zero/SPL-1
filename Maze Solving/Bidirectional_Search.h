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
    void BDS();
    void BFS(vector<vi> mazeGraph, int numberOfVertices, int startVertex);
    int visitedIntersect();
    void printPathBDS();
    void printQueue(list<int> queue);
};


// Overloaded constructor
// Graph::Graph(vector<vi> mazeGraph){

//     this->mazeGraph = mazeGraph;

// }


int Graph::visitedIntersect(){

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
void Graph::BFS(vector<vi> mazeGraph, int numberOfVertices, int startVertex){

    // mazeGraph

    list<int> queue;
    vector<bool> isVisited(numberOfVertices, false);
    vi previousNode(numberOfVertices, -1);

    queue.push_back(startVertex);  // ***

    //cout<<"anything"<<endl;

    printQueue(queue);

    int current = queue.front();
    queue.pop_front();

    cout<<"current: "<<current<<endl;

    vi::iterator i;

    for(i = mazeGraph[current].begin(); i != mazeGraph[current].end(); ++i){
        
        if(!isVisited[*i]){
            previousNode[*i] = current;
            isVisited[*i] = true;
            queue.push_back(*i);
        }

    }

}


void Graph::BDS(){

}


#endif