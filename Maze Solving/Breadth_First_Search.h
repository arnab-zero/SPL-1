#ifndef Breadth_First_Search
#define Breadth_First_Search

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#include <stdlib.h>
#include <chrono>
#include <bits/stdc++.h>

using namespace std;

class BreadthFirstSearchClass{

    public:
        int numberOfVertices;
        int rowCount;
        int colCount;
        int source;
        int destination;

        vector<vector<int>> mazeGraph;
        vector<vector<int>> indexToNode;
        vector<pair<int, int>> nodeToIndex;

        BreadthFirstSearchClass(int numberOfVertices,
                                int rowCount,
                                int colCount, 
                                int source, 
                                int destination,
                                vector<vector<int>> mazeGraph,
                                vector<vector<int>> indexToNode,
                                vector<pair<int,int>> nodeToIndex)
        {

            this->numberOfVertices = numberOfVertices;
            this->rowCount = rowCount;
            this->colCount = colCount;
            this->source = source;
            this->destination = destination;

            this->mazeGraph = mazeGraph;
            this->indexToNode = indexToNode;
            this->nodeToIndex = nodeToIndex;

        }

        void bfs();
    
    private: 
        void printPath(vector<int> previous);
        void printCoordinate(vector<int> previous, vector<pair<int,int>> nodeToIndex);

};


void BreadthFirstSearchClass::bfs(){

    auto beginning_timestamp = chrono::system_clock::now();

    queue<int> q;
    vector<int> vis(numberOfVertices, 0);
    vector<int> previous(numberOfVertices, -1);
    vector<int> dist(numberOfVertices, INT_MAX);

    q.push(source);

    while(!q.empty()){

        int current = q.front();
        q.pop();

        if(vis[current])
            continue;

        ++vis[current];

        for(auto i: mazeGraph[current]){
            if(!vis[i]){
                previous[i] = current;
                dist[i] = dist[current] + 1;
                q.push(i);
            }
        }
    }

    auto finishing_timestamp = chrono::system_clock::now();

    auto elapsed_time = chrono::duration_cast<chrono::nanoseconds>(finishing_timestamp - beginning_timestamp);

    cout<<endl<<"Result for BFS: "<<endl;
    
    if(vis[destination]){
        cout<<"Destination can be reached from the source."<<endl;
    }
    else{
        cout<<"Destination can not be reached from the source. "<<endl;
        return;
    }

    cout<<"Elapsed time for BFS path finding: "<<elapsed_time.count() << " nanoseconds."<<endl;
    cout<<endl;

    printPath(previous);

    printCoordinate(previous, nodeToIndex);

}


void BreadthFirstSearchClass::printPath(vector<int> previous){

    int currentNode = destination;

    stack<int> s;
    s.push(currentNode);

    while(currentNode != source){

        currentNode = previous[currentNode];
        s.push(currentNode);
    }

    cout<<"Path from the current position to destination: "<<endl;

    while(1){
        cout<<s.top();
        s.pop();

        if(s.empty())
            break;

        cout<<" --> ";
    }

}

void BreadthFirstSearchClass::printCoordinate(vector<int> previous, vector<pair<int,int>> nodeToIndex){

    int currentNode = destination;

    stack<int> s;
    s.push(currentNode);

    while(currentNode != source){

        currentNode = previous[currentNode];
        s.push(currentNode);
    }

    cout<<endl<<"Path from the source to destination (as coordinates): "<<endl;

    while(1){
        
        int current = s.top();
        s.pop();

        cout << "(" << nodeToIndex[current].first << "," << nodeToIndex[current].second << ")";

        if(s.empty())
            break;
        
        cout<<" --> ";

    }

}


#endif 