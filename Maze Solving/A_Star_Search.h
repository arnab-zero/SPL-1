#ifndef A_Star_Search

#define A_Star_Search

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

struct Cell{
    
    int row;
    int col;
    int parent;

    int f, g, h;    // f = g+h

};


class A_Star_Class{

    public:
        int numberOfVertices;
        int rowCount;
        int colCount;
        int source;
        int destination;
        vector<vector<int>> mazeGraph;
        vector<vector<int>> indexToNode;
        vector<pair<int, int>> nodeToIndex;
        vector<vector<int>> weight;
        vector<Cell> cell;

        // class constructor
        A_Star_Class(int rowCount,
                     int colCount, 
                     int source, 
                     int destination, 
                     int numberOfVertices, 
                     vector<vector<int>>& mazeGraph, 
                     vector<vector<int>>& indexToNode, 
                     vector<pair<int,int>>& nodeToIndex, 
                     vector<vector<int>>& weight)
        {

            this->source = source;
            this->destination = destination;
            this->rowCount = rowCount;
            this->colCount = colCount;
            this->numberOfVertices = numberOfVertices;
            this->mazeGraph = mazeGraph;
            this->indexToNode = indexToNode;
            this->nodeToIndex = nodeToIndex;
            this->weight = weight;

            cell = createCell(numberOfVertices);

        }

        // void printCell(){

        //     for(int i=0; i<numberOfVertices; ++i){
        //         cout<<i<<" "<<cell[i].row<<" "<<cell[i].col<<" "<<cell[i].parent<<endl;
        //     }

        // }

    private: 
        vector<Cell> createCell(int numberOfVertices){

            vector<Cell> cell(numberOfVertices);

            for(int i=0; i<numberOfVertices; ++i){
                
                cell[i].row = nodeToIndex[i].first;
                cell[i].col = nodeToIndex[i].second;

                cell[i].parent = -1;

                cell[i].f = INT_MAX;
                cell[i].g = INT_MAX;
                cell[i].h = INT_MAX;

            }

            return cell;

        }


        bool isValidCell(int node){
            
            if(cell[node].row < 0)
                return false;
            else if(cell[node].row >= rowCount)
                return false;
            else if(cell[node].col < 0)
                return false;
            else if(cell[node].col >= colCount)
                return false;
            
            return true;

        }

        // left
        bool isDestination(int node){

            if(cell[node].row == cell[destination].row and cell[node].col == cell[destination].col)
                return true;
            
            return false;
        }

        // calculates heuristic value of a vertex
        int calculateHeuristic(int node){

            int rowDifference, colDifference;

            rowDifference = abs(cell[node].row - cell[destination].row);
            colDifference = abs(cell[node].col - cell[destination].col);

            int heuristicValue = rowDifference + colDifference;

            return heuristicValue;

        }

        int printPath(){

            cout<<"The path is: "<<endl;

            stack<int> path;

            int temp = destination;
            path.push(temp);

            while(cell[temp].parent != -1){

                temp = cell[temp].parent;
                path.push(temp);
            }

            while(!path.empty()){

                cout<<path.top();
                path.pop();

                if(!path.empty())
                    cout<<"--> ";
            }

            cout<<endl;

        }


    public:
        void aStarSearch(){

            cout<<source << " "<< destination<<endl;

            if(!isValidCell(source)){
                cout<<"Invalid source vertex."<<endl;
                return;
            }
            
            if(!isValidCell(destination)){
                cout<<"Invalid source vertex."<<endl;
                return;
            }

            if(isDestination(source)){
                cout<<"Already at the destination."<<endl;
                return;
            }

            vector<bool> closedList(numberOfVertices);

            for(int i=0; i<numberOfVertices; ++i)
                closedList[i] = false;

            
            cout<<"yes"<<endl;

            cell[source].f = 0;
            cell[source].g = 0;
            cell[source].h = 0;

            cell[source].parent = -1;

            set<pair<int, int>> openList;

            openList.insert({cell[source].f, source});

            bool destinationReached = false;

            while(!openList.empty()){

                auto firstElement = *openList.begin();
                openList.erase(openList.begin());

                int currentNode = firstElement.second;

                closedList[currentNode] = true;

                vector<int>:: iterator i;

                for(i = mazeGraph[currentNode].begin(); i != mazeGraph[currentNode].end(); ++i){

                    if(isDestination(*i)){

                        cout<<"Destination vertex can be reached from the source."<<endl;

                        cell[*i].parent = currentNode;
                        printPath();        
                        destinationReached = true;
                        return;
                    }
                    else if(closedList[*i] == false){

                        int newGValue = cell[*i].g + weight[currentNode][*i];
                        int newHValue = calculateHeuristic(*i);

                        int newFValue = newGValue + newHValue;

                        if(cell[*i].f == INT_MAX or cell[*i].f > newFValue){
                            openList.insert({newFValue, *i});

                            cell[*i].f = newFValue;
                            cell[*i].g = newGValue;
                            cell[*i].h = newHValue;

                            cell[*i].parent = currentNode;
                        }

                    }

                }

            }

            if(!destinationReached){
                cout<<"Can not reach the destination."<<endl;
            }

        }


};



#endif