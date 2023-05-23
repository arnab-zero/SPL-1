#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <cmath>
#include <stack>
#include <bits/stdc++.h>

#include "Bidirectional_Search.h"

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


    // Creating a 2D array that holds edge weights in the graph
    vector<vector<int>> weight(nodeCounter+1, vector<int>(nodeCounter, -1));

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

    // for(int i=0; i<row; ++i){
    //     for(int j=0; j< col; ++j){
    //         int node = indexToNode[i][j];
    //         cout<<" col "<<j<<" row "<<i<<" node "<< indexToNode[i][j]<<endl;
    //         cout<<"node "<<node<<" col "<<nodeToIndex[node].second<<" row "<<nodeToIndex[node].first<<endl<<endl;
    //     }
    //     cout<<endl<<endl<<endl;
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

	// q.push(start);			// starting from the vertex 0
	// bfs();				//  BFS graph traversal on the graph found from the maze

	// cout<<"After BFS: "<<endl;
	// cout<<"Vertex"<<"\t"<<"Visited"<<" "<<"Distance"<<" "<<"Previous"<<endl;
	// for(i=0; i<nodeCounter; ++i){
	// 	cout<<i<<"\t"<<vis[i]<<" "<<dist[i]<<" "<<previous[i]<<endl;
	// }
	// cout<<finish<<"\t"<<vis[finish]<<" "<<dist[finish]<<" "<<previous[finish]<<endl;
	
	stack<int> s;		// stack to store the path from destination to current position.

	// int currentNode = finish;		// starting from destination.
	// s.push(currentNode);		// destination vertex pushed to the stack first.
	// while(currentNode != start){
	// 	currentNode = previous[currentNode];		// previous vertex would be new currentNode.
	// 	s.push(currentNode);		// current node pushed to the stack.
	// }

	// cout<<endl;
	
	// if(vis[finish])
	// 	cout<<"Destination can be reached from the current position."<<endl;
	// else{
	// 	cout<<"There is no path to reach the destination."<<endl;
	// 	return 0;
	// } 

	// cout<<"Distance from the current position: "<<dist[finish]<<endl;

	// cout<<"Path from the current position to destination: ";
	// while(1){
	// 	cout<<s.top();
	// 	s.pop();
	// 	if(s.empty())
	// 		break;
	// 	cout<<" --> ";
	// }

	// AStarSearch obj;
	// obj.solveMaze(nodeCounter, row, col, start, finish, indexToNode, nodeToIndex);


    Graph obj;

    //obj.BFS(mazeGraph, nodeCounter+1, 0);

    obj.BDS(mazeGraph, nodeCounter+1, start, finish);


	return 0;
}
