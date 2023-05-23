#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pb push_back
#define spc " "
#define tab "\t"
#define ROW 100
#define COL 100

vector<vi> mazeGraph(ROW);

int main(void){
    int row, col;
    cout<<"Enter row and column for the maze: ";
    cin>>row>>col;

    cout<<endl;
    cout<<"Enter the maze: ";
    vector<string> mazeLine(row);

    int i, j;
    for(i=0; i<row; ++i)
        cin>>mazeLine[i];

    
}
