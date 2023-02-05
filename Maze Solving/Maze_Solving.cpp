#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pb push_back
#define ROW 100
#define COL 100

vector<vi> indexToNode(ROW, vi(COL, -1));			// points index to node
vector<pair<int, int>> nodeToIndex;				// points node to index
vector<vi> mazeGraph(ROW);			// adjacency list for derived graph from the maze
int nodeCounter = -1;			// starts nodes from 0

int main(void){
	int row, col;
	cout<<"Enter row and column count for the maze: ";
	cin>>row>>col;

	vector<string> graphLine(row);
	
	int i, j;	// variables for iterating loops.
	for(i=0; i<row; ++i) 
		cin>>graphLine[i];
	
	// Only for the first row of the maze
	for(j=0; j<col; ++j){
		if(graphLine[0][j] == '.'){
			indexToNode[0][j] = ++nodeCounter;		// store the node to indexToNode table and name it
			nodeToIndex.pb({0, j});				// store the index against the corresponding node

			// for non-leftmost vertices connecting with the left vertex if exists
			if(j && graphLine[0][j-1] == '.'){		
				mazeGraph[indexToNode[0][j-1]].pb(indexToNode[0][j]);		// push the edge to adjacency list
				mazeGraph[indexToNode[0][j]].pb(indexToNode[0][j-1]);		// same to do undirected.
			}
		}
	}

	// for next rows in the maze
	for(i=1; i<row; ++i){
		for(j=0; j<col; ++j){
			if(graphLine[i][j] == '.'){
				indexToNode[i][j] = ++nodeCounter;		// store the node to indexToNode table and name it
				nodeToIndex.pb({i, j});				// store the index against the corresponding node

				if(j && graphLine[i][j-1] == '.'){
					mazeGraph[indexToNode[i][j-1]].pb(indexToNode[i][j]);
					mazeGraph[indexToNode[i][j]].pb(indexToNode[i][j-1]);
				}

				// creating edge with upper vertex if it is a '.'
				if(graphLine[i-1][j] == '.'){
					mazeGraph[indexToNode[i-1][j]].pb(indexToNode[i][j]);
					mazeGraph[indexToNode[i][j]].pb(indexToNode[i-1][j]);
				}
			}
		}
	}

	// Checking if the adjacency list output is correct
	// for(i=0; i<nodeCounter; ++i){
	// 	cout<<i<<"\t";
	// 	cout<<mazeGraph[i].size()<< " ";
	// 	for(auto p: mazeGraph[i]){
	// 		cout<<p<<" ";
	// 	}
	// 	cout<<endl;
	// }
	
	

}
