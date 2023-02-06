#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pb push_back
#define spc " "
#define tab "\t"
#define ROW 100			// row count for indexToNode table
#define COL 100			// col count for indexToNode table

vector<vi> indexToNode(ROW, vi(COL, -1));		// points index to node
vector<pair<int, int>> nodeToIndex;				// points node to index
vector<vi> mazeGraph(ROW);			// adjacency list for derived graph from the maze
queue<int> q;			// queue
vi vis(100);			// if a vertex is visited or not
vi dist(100);			// distance of each vertex from starting vertex
vi previous(100);		// previous vertex of each vertex

int nodeCounter = -1;			// starts nodes from 0

// BFS function for graph traversal
void bfs(){
	if(q.empty())
		return;
	
	int current = q.front();
	q.pop();

	if(vis[current])
		return;
	
	++vis[current];

	for(auto i: mazeGraph[current]){
		if(!vis[i]){
			previous[i] = current;
			dist[i] = dist[current] + 1;
			q.push(i);
		}
		bfs();
	}
}

// main function
int main(void){
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
		if(mazeLine[0][j] == '.'){
			indexToNode[0][j] = ++nodeCounter;		// store the node to indexToNode table and name it
			nodeToIndex.pb({0, j});				// store the index against the corresponding node

			// for non-leftmost vertices connecting with the left vertex if exists
			if(j && mazeLine[0][j-1] == '.'){		
				mazeGraph[indexToNode[0][j-1]].pb(indexToNode[0][j]);		// push the edge to adjacency list
				mazeGraph[indexToNode[0][j]].pb(indexToNode[0][j-1]);		// same to do undirected.
			}
		}
	}

	// for next rows in the maze
	for(i=1; i<row; ++i){
		for(j=0; j<col; ++j){
			if(mazeLine[i][j] == '.'){
				indexToNode[i][j] = ++nodeCounter;		// store the node to indexToNode table and name it
				nodeToIndex.pb({i, j});				// store the index against the corresponding node

				// for non-leftmost vertices connecting with the left vertex if exists
				if(j && mazeLine[i][j-1] == '.'){
					mazeGraph[indexToNode[i][j-1]].pb(indexToNode[i][j]);
					mazeGraph[indexToNode[i][j]].pb(indexToNode[i][j-1]);
				}

				// creating edge with upper vertex if it is a '.'
				if(mazeLine[i-1][j] == '.'){
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
	
	q.push(0);			// starting from the vertex 0
	//  bfs() function call for graph traversal on the graph found from the maze
	bfs();				

	cout<<"After BFS: "<<endl;
	cout<<"Vertex"<<"\t"<<"Visited"<<" "<<"Distance"<<" "<<"Previous"<<endl;

	for(i=0; i<nodeCounter; ++i){
		cout<<i<<"\t"<<vis[i]<<" "<<dist[i]<<" "<<previous[i]<<endl;
	}
	
	return 0;
}
