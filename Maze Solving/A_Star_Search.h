#ifndef A_STAR_SEARCH_H
#define A_STAR_SEARCH_H

#include<bits/stdc++.h>
using namespace std;

class AStarSearch{

private: 
    struct Cell{
        int row, col;
        int f, g, h;
        bool obstacle;

        Cell(int r, int c) :
            row(r),
            col(c),
            f(0),
            g(0),
            h(0), 
            obstacle(false){}
    };

    // a custom comparator for priority queue based on f
    struct CompareCells{
        bool operator() (const Cell &a, const Cell &b){     // **
            return a.f > b.f;
        }
    };

    // calculates Manhattan distance heuristic 
    int calculateHeuristic(const Cell &current, const Cell &destination){
        int rowDifference = abs(current.row-destination.row);
        int colDifference = abs(current.col-destination.col);

        return rowDifference + colDifference;
    }

    // Function to check if a cell from the maze is within bounds or not
    int isValidCell(int row, int col, int mazeRow, int mazeCol){
        if(row < 0)
            return 0;
        
        if(row > mazeRow)
            return 0;

        if(col < 0)
            return 0;

        if(col > mazeCol)
            return 0;

        return 1;
    }


    public:
    vector<Cell> solveMaze(int numberOfNodes, int mazeRow, int mazeCol, int source, int destination, vector<vector<int>> &indexToNode, vector<pair<int,int>> &nodeToIndex){

        // priority queue for open list 
        priority_queue<Cell, vector<Cell>, CompareCells> openList;

        vector<Cell> mazeCell;

        // initializing the nodes as Cell 
        for(int i=0; i<numberOfNodes; ++i){
            mazeCell[i] = Cell(nodeToIndex[i].first, nodeToIndex[i].second);
        }

        // specifying the source and the destination cell
        Cell startCell = mazeCell[source];
        Cell destinationCell = mazeCell[destination];

        // initializing the starting Cell
        startCell.h = calculateHeuristic(startCell, destinationCell);
        startCell.f = startCell.h;
        openList.push(startCell);

        // the possible moves that can be made from a Cell in the maze (up, down, left, right)
        int directionAtRow[] = {-1, -1, 0, 0};
        int directionAtCol[] = {0, 0, -1, -1};

        // 2d vector to store the parent cells for each cell in the maze
        vector<vector<Cell>> parent (mazeRow, vector<Cell>(mazeCol));

        // traversing the graph for optimal path finding
        while(!openList.empty()){

        

        }

    }


};




#endif
