#ifndef A_STAR_SEARCH_H
#define A_STAR_SEARCH_H

#include<bits/stdc++.h>
using namespace std;

class AStarSearch{

private: 
    struct Cell{
        int node, row, col;
        int f, g, h;
        bool obstacle;

        Cell(int i, int r, int c) :
            node(i),
            row(r),
            col(c),
            f(0),
            g(0),
            h(0), 
            obstacle(false){}
    };

private:
    // a custom comparator for priority queue based on f
    struct CompareCells{
        bool operator() (const Cell &a, const Cell &b){     // **
            return a.f > b.f;
        }
    };

private:
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

    // stores the optimal path
    vector<Cell> optimalPath;

    void solveMaze(int numberOfNodes, int mazeRow, int mazeCol, int source, int destination, vector<vector<int>> &indexToNode, vector<pair<int,int>> &nodeToIndex){

        // priority queue for open list 
        priority_queue<Cell, vector<Cell>, CompareCells> openList;

        // map to keep track of elements
        map<int, bool> openCellMap;

        vector<Cell> mazeCell;

        // initializing the nodes as Cell 
        for(int i=0; i<numberOfNodes; ++i){
            mazeCell[i] = Cell(i, nodeToIndex[i].first, nodeToIndex[i].second);
        }

        // specifying the source and the destination cell
        Cell startCell = mazeCell[source];
        Cell destinationCell = mazeCell[destination];

        // initializing the starting Cell
        startCell.h = calculateHeuristic(startCell, destinationCell);
        startCell.f = startCell.h;
        openList.push(startCell);
        openCellMap[indexToNode[startCell.row][startCell.col]] = true;


        // the possible moves that can be made from a Cell in the maze (up, down, left, right)
        int directionAtRow[] = {-1, -1, 0, 0};
        int directionAtCol[] = {0, 0, -1, -1};

        // 2d vector to store the parent cells for each cell in the maze
        vector<vector<Cell>> parent (mazeRow, vector<Cell>(mazeCol));

        // traversing the graph for optimal path finding
        while(!openList.empty()){

            Cell currentCell = openList.top();
            openList.pop();
            openCellMap[indexToNode[currentCell.row][currentCell.col]] = false;

            // checks if current cell is the destination cell
            if(currentCell.row == destinationCell.row and currentCell.col==destinationCell.col){
                
                //vector<Cell> optimalPath;
                Cell cell = currentCell;

                while(cell.row != startCell.row or cell.col!=startCell.col){
                    optimalPath.push_back(cell);
                    cell = parent[cell.row][cell.col];
                }

                optimalPath.push_back(startCell);

                reverse(optimalPath.begin(), optimalPath.end());
            }

            // to the neighbor cells
            for(int i=0; i<4; ++i){
                int neighborRow = currentCell.row + directionAtRow[i];
                int neighborCol = currentCell.col + directionAtCol[i];

                if(isValidCell(neighborRow, neighborCol, mazeRow, mazeCol) and indexToNode[neighborRow][neighborCol] != -1){
                    Cell neighborCell = mazeCell[indexToNode[neighborRow][neighborCol]];

                    int updatedG = currentCell.g + 1;

                    // checking if its in the open list
                    bool isOpen = false;

                    if(openCellMap.count(neighborCell.node) and openCellMap[neighborCell.node]==true){
                        isOpen = true;
                    }


                    // checking if the neighbor cell is already in the closed list
                    bool isClosed = (parent[neighborCell.row][neighborCell.col].row != -1);

                    // updating the neighbor if it's a better choice;
                    if(!isOpen and !isClosed){
                        neighborCell.g = updatedG;
                        neighborCell.h = calculateHeuristic(neighborCell, destinationCell);
                        neighborCell.f = neighborCell.g + neighborCell.h;
                        openList.push(neighborCell);
                        parent[neighborCell.row][neighborCell.col] = currentCell;
                    }
                    else if(isOpen and updatedG < neighborCell.g){
                        neighborCell.g = updatedG;
                        neighborCell.f = neighborCell.g + neighborCell.h;
                        parent[neighborCell.row][neighborCell.col] = currentCell;
                    }
                    
                }
               
            }

        }

    }

    void printPath(){

        cout<<"A* search result: \n";

        for(auto i: optimalPath){
            cout<<i.node<<" ";
        }

        cout<<endl;

    }

};




#endif
