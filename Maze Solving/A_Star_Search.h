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

    struct CompareCells{
        bool operator() (const Cell &a, const Cell &b){     // **
            return a.f > b.f;
        }
    };

    


};




#endif
