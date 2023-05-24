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

        }


    public:
        void aStarSearch(){

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

            cell[source].f = 0;
            cell[source].g = 0;
            cell[source].h = 0;

            



        }


};



#endif