#include <bits/stdc++.h>
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
int start, finish;		

int main(void){

    freopen("Maze_Input.txt", "r", stdin);

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

    AStarSearch obj;

    obj.solveMaze(nodeCounter, row, col, start, finish, indexToNode, nodeToIndex);
    obj.printPath();

    return 0;

}
