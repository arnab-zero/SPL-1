#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <cmath>
#include <stack>
#include <chrono>

#include "Breadth_First_Search.h"
#include "Bidirectional_Search.h"
#include "A_Star_Search.h"

using namespace std;

#define vi vector<int>
#define pb push_back
#define spc " "
#define tab "\t"
#define ROW 100			// row count for indexToNode table
#define COL 100			// col count for indexToNode table

vector<vi> indexToNode(ROW, vi(COL, -1));		// points index of node
vector<pair<int, int>> nodeToIndex;				// points co-ordinate of indexed nodes
vector<vi> mazeGraph(ROW);			// adjacency list for derived graph from the maze
queue<int> q;			// queue
vi vis(100);			// if a vertex is visited or not
vi dist(100);			// distance of each vertex from starting vertex
vi previous(100);		// previous vertex of each vertex

int nodeCounter = -1;			// starts nodes from 0
int start, finish;		// start = start vertex in the graph, finish = destination in the graph		


// main function
int main(void){

	freopen("Maze_Input2.txt", "r", stdin);

	int row, col;
	cout<<"Enter row and column count for the maze: ";
	cin>>row>>col;

	cout<<endl;
	cout<<"Enter the maze: ";
	vector<string> mazeLine(row);
	
	int i, j;	// variables for iterating loops.
	for(i=0; i<row; ++i) 
		cin>>mazeLine[i];
	
	// Only for the first row of the maze
	for(j=0; j<col; ++j){
		if(mazeLine[0][j] == '.' || mazeLine[0][j] == 'S' || mazeLine[0][j] == 'D'){
			indexToNode[0][j] = ++nodeCounter;		// store the node to indexToNode table and name it
			nodeToIndex.pb({0, j});				// store the index against the corresponding node

			// for non-leftmost vertices connecting with the left vertex if exists
			if(j && (mazeLine[0][j-1] == '.' || mazeLine[0][j-1] == 'S' || mazeLine[0][j-1] == 'D')){		
				mazeGraph[indexToNode[0][j-1]].pb(indexToNode[0][j]);		// push the edge to adjacency list
				mazeGraph[indexToNode[0][j]].pb(indexToNode[0][j-1]);		// same to do undirected.
			}
		}

		// save the vertex if it is start or end
		if(mazeLine[0][j] == 'S')
			start = nodeCounter;
		else if(mazeLine[0][j] == 'D')
			finish = nodeCounter;
	}

	// for next rows in the maze
	for(i=1; i<row; ++i){
		for(j=0; j<col; ++j){
			if(mazeLine[i][j] == '.' || mazeLine[i][j] == 'S' || mazeLine[i][j] == 'D'){
				indexToNode[i][j] = ++nodeCounter;		// store the node to indexToNode table and name it
				nodeToIndex.pb({i, j});				// store the index against the corresponding node

				// for non-leftmost vertices connecting with the left vertex if exists
				if(j && (mazeLine[i][j-1] == '.' || mazeLine[i][j-1] == 'S' || mazeLine[i][j-1] == 'D')){
					mazeGraph[indexToNode[i][j-1]].pb(indexToNode[i][j]);
					mazeGraph[indexToNode[i][j]].pb(indexToNode[i][j-1]);
				}

				// creating edge with upper vertex if it is a '.'
				if(mazeLine[i-1][j] == '.' || mazeLine[i-1][j] == 'S' || mazeLine[i-1][j] == 'D'){
					mazeGraph[indexToNode[i-1][j]].pb(indexToNode[i][j]);
					mazeGraph[indexToNode[i][j]].pb(indexToNode[i-1][j]);
				}
			}

			// save the vertex if it is start or end
			if(mazeLine[i][j] == 'S')
				start = nodeCounter;
			else if(mazeLine[i][j] == 'D')
				finish = nodeCounter;
		}
	}


    // Creating a 2D array that holds edge weights in the graph
    vector<vector<int>> weight(nodeCounter+1, vector<int>(nodeCounter+1, -1));

    for(int i=0; i<nodeCounter+1; ++i){
        int currentNodeRow = nodeToIndex[i].first;
        int currentNodeCol = nodeToIndex[i].second;

        for(auto neighborNode: mazeGraph[i]){
            int neighborNodeRow = nodeToIndex[neighborNode].first;
            int neighborNodeCol = nodeToIndex[neighborNode].second;

            if(currentNodeRow == neighborNodeRow){
                int distance = abs(currentNodeCol - neighborNodeCol);

                weight[i][neighborNode] = distance;
                weight[neighborNode][i] = distance;
            }
        }
    }

    // for(int i=0; i<nodeCounter+1; ++i){
    //     cout<<"vertex: "<<i<<endl;
    //     cout<<"row "<<nodeToIndex[i].first<<" col "<<nodeToIndex[i].second<<endl;

    //     for(auto p: mazeGraph[i]){
    //         cout<<"for "<<p<<" row "<<nodeToIndex[p].first<<" col "<<nodeToIndex[p].second;
    //         cout<<" weight is "<<weight[i][p]<<endl;
    //     }

    //     cout<<endl;
    // }


	// // Checking if the adjacency list output is correct
	// for(i=0; i<nodeCounter+1; ++i){
	// 	cout<<i<<"\t";
	// 	cout<<mazeGraph[i].size()<< " ";
	// 	for(auto p: mazeGraph[i]){
	// 		cout<<p<<" ";
	// 	}
	// 	cout<<endl;
	// }
	// cout<<"Start: "<<start<<endl<<"Finish: "<<finish<<endl;

	
    BreadthFirstSearchClass bfsObj(nodeCounter+1, row, col, start, finish, mazeGraph, indexToNode, nodeToIndex);
	bfsObj.bfs();

    cout<<"Result of Bidirectional Search: "<<endl;
    Graph obj;

    // beginning time of bidirectional search on the Maze
    auto bds_clock_begin = chrono::system_clock::now();

    obj.BDS(mazeGraph, nodeToIndex, nodeCounter+1, start, finish, weight);

    // finishing time stamp of bidirectional search on the maze
    auto bds_clock_end = chrono::system_clock::now();

    auto time_elapsed_for_bds = chrono::duration_cast<chrono::nanoseconds>(bds_clock_end - bds_clock_begin);

    cout<<"Time elapsed for BDS on maze: "<< time_elapsed_for_bds.count();
    cout<<" nanoseconds."<<endl;


	A_Star_Class a_star_obj(row, col, start, finish, nodeCounter+1, mazeGraph, indexToNode, nodeToIndex, weight);

	cout<<endl<<endl<<"Result of A* search: "<<endl;

	// beginning time of A* search on the maze
	auto a_star_search_beginning = chrono::system_clock::now();
	
	a_star_obj.aStarSearch();

	// finishing time of A* search on the maze
	auto a_star_search_ending = chrono::system_clock::now();

	auto time_elapsed_for_a_star = chrono::duration_cast<chrono::nanoseconds>(a_star_search_ending - a_star_search_beginning);

	cout<<"Time elapsed for A* search on the maze: " << time_elapsed_for_a_star.count() << " nanoseconds" <<endl;


	return 0;
}
