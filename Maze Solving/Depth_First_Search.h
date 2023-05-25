#ifndef Depth_First_Search
#define Depth_First_Search

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

class Depth_First_Search_Class{

    public:
        int rowCount;
        int colCount;
        pair<int, int> source;
        pair<int, int> destination;
        vector<string> mazeLine;

        Depth_First_Search_Class(int rowCount,
                                 int colCount,
                                 pair<int,int> source,
                                 pair<int,int> destination,
                                 vector<string>& mazeLine)
        {
            this->rowCount = rowCount;
            this->colCount = colCount;
            this->source = source;
            this->destination = destination;
            
            this->mazeLine = mazeLine;
        }

        void findDeadEnds();

    private: 
        stack<pair<int, int>> dfsStack;
        void dfs(vector<vector<bool>>& isVisitedCell);
        bool isValidCell(int row, int cell);
        void printDeadEndCoordinates(vector<vector<bool>>& isVisitedCell);
        bool isDeadEnd(int x, int y, vector<vector<bool>>& isVisitedCell);

};


bool Depth_First_Search_Class::isValidCell(int row, int col){

    if(row < 0)
        return false;

    if(row >= rowCount)
        return false;

    if(col < 0)
        return false;
    
    if(col >= colCount)
        return false;
    
    return true;

}


void Depth_First_Search_Class::findDeadEnds(){

    vector<vector<bool>> isVisitedCell(rowCount, vector<bool>(colCount, false));

    // for(int i=0; i<rowCount; ++i){
    //     for(int j=0; j<colCount; ++j){
    //         cout<<mazeLine[i][j]<<"";
    //     }
    //     cout<<endl;
    // }
    // cout<<"start: "<<source.first<<" "<<source.second<<endl;
    // cout<<"finish: "<<destination.first<<" "<<destination.second<<endl;

    Depth_First_Search_Class::dfsStack.push(source);

    dfs(isVisitedCell);

    cout<<endl;

    for(int i=0; i<rowCount; ++i){
        for(int j=0; j<colCount; ++j){
            cout<<isVisitedCell[i][j]<<" ";
        }
        cout<<endl;
    }

    printDeadEndCoordinates(isVisitedCell);

}


void Depth_First_Search_Class::dfs(vector<vector<bool>>& isVisitedCell){

    if(Depth_First_Search_Class::dfsStack.empty())
        return;

    auto current = Depth_First_Search_Class::dfsStack.top();
    Depth_First_Search_Class::dfsStack.pop();

    int row = current.first;
    int col = current.second;

    isVisitedCell[row][col] = true;

    if(isValidCell(row-1, col) and !isVisitedCell[row-1][col]){
        if(mazeLine[row-1][col] == '.' or mazeLine[row-1][col] == 'S' or mazeLine[row-1][col] == 'D')
            Depth_First_Search_Class::dfsStack.push({row-1, col});
    }

    if(isValidCell(row+1, col) and !isVisitedCell[row+1][col]){
        if(mazeLine[row+1][col] == '.' or mazeLine[row+1][col] == 'S' or mazeLine[row+1][col] == 'D')
            Depth_First_Search_Class::dfsStack.push({row+1, col});
    }

    if(isValidCell(row, col-1) and !isVisitedCell[row][col-1]){
        if(mazeLine[row][col-1] == '.' or mazeLine[row][col-1] == 'S' or mazeLine[row][col-1] == 'D')
            Depth_First_Search_Class::dfsStack.push({row, col-1});
    }

    if(isValidCell(row, col+1) and !isVisitedCell[row][col+1]){
        if(mazeLine[row][col+1] == '.' or mazeLine[row][col+1] == 'S' or mazeLine[row][col+1] == 'D')
            Depth_First_Search_Class::dfsStack.push({row, col+1});
    }

    dfs(isVisitedCell);
}


bool Depth_First_Search_Class::isDeadEnd(int x, int y, vector<vector<bool>>& isVisitedCell){

    bool verdict = true;

    if(mazeLine[x][y] == '*' or mazeLine[x][y] == 'S' or mazeLine[x][y] == 'D')
        verdict = verdict & false;

    if(isValidCell(x-1, y) and (mazeLine[x-1][y] == '.' or mazeLine[x-1][y] == 'S' or mazeLine[x-1][y] == 'D')){
        if(!isVisitedCell[x-1][y])
            verdict = verdict & false;
    }

    if(isValidCell(x+1, y) and (mazeLine[x+1][y] == '.' or mazeLine[x+1][y] == 'S' or mazeLine[x+1][y] == 'D')){
        if(!isVisitedCell[x+1][y])
            verdict = verdict & false;
    }

    if(isValidCell(x, y-1) and (mazeLine[x][y-1] == '.' or mazeLine[x][y-1] == 'S' or mazeLine[x][y-1] == 'D')){
        if(!isVisitedCell[x][y-1])
            verdict = verdict & false;
    }

    if(isValidCell(x, y+1) and mazeLine[x][y+1] == '.'  or mazeLine[x][+1] == 'S' or mazeLine[x][y+1] == 'D'){
        if(!isVisitedCell[x][y+1])
            verdict = verdict & false;
    }

    if(mazeLine[x-1][y] == '.' and mazeLine[x-1][y] == mazeLine[x+1][y]){
        if(isValidCell(x-1, y) and isValidCell(x+1, y))
            verdict = verdict & false;
    }

    if(isValidCell(x, y-1) and isValidCell(x, y+1)){
        if(mazeLine[x][y-1] == '.' and mazeLine[x][y-1] == mazeLine[x][y+1]){
            verdict = verdict & false;
        }
        else if(mazeLine[x][y-1] == 'S' or mazeLine[x][y-1] == 'D'){
            if(mazeLine[x][y+1] == '.')
                verdict = verdict & false;
        }
        else if(mazeLine[x][y+1] == 'S' or mazeLine[x][y+1] == 'D'){
            if(mazeLine[x][y-1] == '.')
                verdict = verdict & false;
        }
    }

    if(isValidCell(x-1, y) and isValidCell(x+1, y)){
        if(mazeLine[x-1][y] == '.' and mazeLine[x-1][y] == mazeLine[x+1][y]){
            verdict = verdict & false;
        }
        else if(mazeLine[x-1][y] == 'S' or mazeLine[x-1][y] == 'D'){
            if(mazeLine[x+1][y] == '.')
                verdict = verdict & false;
        }
        else if(mazeLine[x+1][y] == 'S' or mazeLine[x+1][y] == 'D'){
            if(mazeLine[x-1][y] == '.')
                verdict = verdict & false;
        }
    }

    return verdict;

}


void Depth_First_Search_Class::printDeadEndCoordinates(vector<vector<bool>>& isVisitedCell){

    cout<<"Coordinates of the dead ends: "<<endl;

    for(int i=0; i<rowCount; ++i){
        for(int j=0; j<colCount; ++j){

            if(isDeadEnd(i, j, isVisitedCell)){
                cout<< "(" << i << "," << j << ")"<<", ";
            }

        }
    }

}



#endif
