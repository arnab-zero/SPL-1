#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

// Define a structure for representing a cell in the maze
struct Cell {
    int row, col; // Position of the cell in the maze
    int f, g, h; // Cost values for A* algorithm
    bool obstacle; // Indicates if the cell is an obstacle

    Cell(int r, int c) : row(r), col(c), f(0), g(0), h(0), obstacle(false) {}
};

// Define a custom comparator for the priority queue based on the f value
struct CompareCells {
    bool operator()(const Cell& a, const Cell& b) const {
        return a.f > b.f;
    }
};

// Function to calculate the heuristic value (Manhattan distance)
int calculateHeuristic(const Cell& current, const Cell& goal) {
    return abs(current.row - goal.row) + abs(current.col - goal.col);
}

// Function to check if a cell is within the maze bounds
bool isValidCell(int row, int col, int rows, int cols) {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

// Function to perform A* search to find the optimal path in the maze
vector<Cell> solveMaze(vector<vector<Cell>>& maze, Cell& start, Cell& goal) {
    int rows = maze.size();
    int cols = maze[0].size();

    // Priority queue for open list
    priority_queue<Cell, vector<Cell>, CompareCells> openList;

    // Initialize the starting cell
    start.h = calculateHeuristic(start, goal);
    start.f = start.h;
    openList.push(start);

    // Define the possible moves (up, down, left, right)
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // Create a 2D vector to store the parent cells for each cell in the maze
    vector<vector<Cell>> parent(rows, vector<Cell>(cols));

    while (!openList.empty()) {
        // Get the cell with the lowest f value from the open list
        Cell current = openList.top();
        openList.pop();

        // Check if the current cell is the goal
        if (current.row == goal.row && current.col == goal.col) {
            // Reconstruct the path from the goal to the start
            vector<Cell> path;
            Cell cell = current;
            while (cell.row != start.row || cell.col != start.col) {
                path.push_back(cell);
                cell = parent[cell.row][cell.col];
            }
            path.push_back(start);

            // Reverse the path to start from the beginning
            reverse(path.begin(), path.end());

            return path;
        }

        // Explore the neighboring cells
        for (int i = 0; i < 4; i++) {
            int newRow = current.row + dr[i];
            int newCol = current.col + dc[i];

            if (isValidCell(newRow, newCol, rows, cols) && !maze[newRow][newCol].obstacle) {
                Cell& neighbor = maze[newRow][newCol];

                // Calculate the tentative g value
                int newG = current.g + 1;

                // Check if the neighbor is already in the open list
                bool isOpen = false;
                for (const Cell& openCell : openList) {
                    if (openCell.row == neighbor.row && openCell.col == neighbor.col) {
                        isOpen = true;
                        break;
                    }
                }

                // Check if the neighbor is already in the closed list
                bool isClosed = parent[neighbor.row][neighbor.col].row != -1;

                // Update the neighbor's values if it's a better path
                if (!isOpen && !isClosed) {
                    neighbor.g = newG;
                    neighbor.h = calculateHeuristic(neighbor, goal);
                    neighbor.f = neighbor.g + neighbor.h;
                    openList.push(neighbor);
                    parent[neighbor.row][neighbor.col] = current;
                } else if (isOpen && newG < neighbor.g) {
                    neighbor.g = newG;
                    neighbor.f = neighbor.g + neighbor.h;
                    parent[neighbor.row][neighbor.col] = current;
                }
            }
        }
    }

    // If the open list is empty and we haven't reached the goal, there is no path
    return {};
}

int main() {
    int rows, cols;

    cout << "Enter the number of rows in the maze: ";
    cin >> rows;

    cout << "Enter the number of columns in the maze: ";
    cin >> cols;

    // Create a 2D vector to represent the maze
    vector<vector<Cell>> maze(rows, vector<Cell>(cols, Cell(-1, -1)));

    // Get the maze from the user
    cout << "Enter the maze (S: start, G: goal, X: obstacle, .: empty space):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char cell;
            cin >> cell;

            if (cell == 'S') {
                maze[i][j] = Cell(i, j);
                maze[i][j].obstacle = false;
            } else if (cell == 'G') {
                maze[i][j] = Cell(i, j);
                maze[i][j].obstacle = false;
            } else if (cell == 'X') {
                maze[i][j] = Cell(i, j);
                maze[i][j].obstacle = true;
            } else {
                maze[i][j] = Cell(i, j);
                maze[i][j].obstacle = false;
            }
        }
    }

    // Find the start and goal cells
    Cell start, goal;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!maze[i][j].obstacle) {
                if (maze[i][j].row == -1 && maze[i][j].col == -1) {
                    maze[i][j].row = i;
                    maze[i][j].col = j;
                }
                if (maze[i][j].row == i && maze[i][j].col == j) {
                    if (start.row == -1 && start.col == -1) {
                        start = maze[i][j];
                    } else {
                        goal = maze[i][j];
                    }
                }
            }
        }
    }

    // Solve the maze
    vector<Cell> path = solveMaze(maze, start, goal);

    // Print the maze with the optimal path
    cout << "Maze with the optimal path:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j].obstacle) {
                cout << "X ";
            } else if (maze[i][j].row == start.row && maze[i][j].col == start.col) {
                cout << "S ";
            } else if (maze[i][j].row == goal.row && maze[i][j].col == goal.col) {
                cout << "G ";
            } else if (find(path.begin(), path.end(), maze[i][j]) != path.end()) {
                cout << "* ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }

    return 0;
}
