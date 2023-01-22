#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pb push_back
#define spc " "
#define tab "\t"

vi vis(100, 0);         // if a vertex is visited or not
vi start_ts(100);
vi end_ts(100);
stack<int> s;           
int prev, timestamp = -1;

// DFS function
void dfs(vector<vi> &v){

    // if(s.empty())
    //     return;

    int node = s.top();
    s.pop();

    start_ts[node] = ++timestamp;

    if(!vis[node]){          // checking if the node is visited previously.
        cout<<" --> "<<node;
        
    }
    
    ++vis[node];

    for(auto i: v[node]){
        if(!vis[i])         // checking if the node is visited previously.
            s.push(i);      // inserting the node to stack.
    }

    if(!s.empty())
        dfs(v);         // recursive call to dfs.

    end_ts[node] = ++timestamp;
}

// main function
int main(void){
    int m, n, start;    // m = number of vertices, n = number of edges
    cin>>m>>n;

    vector<vi> v(m+2);  // Stores indirected edges of graph

    for(int i=0; i<n; ++i){
        int x, y;
        cin>>x>>y;

        v[x].pb(y);
        v[y].pb(x);
    }

    cin>>start;
    s.push(start);   // inserting starting node to stack.
    dfs(v);          // DFS function call
    cout<<endl;

    cout<<"done"<<endl;

    cout<<"Timestamps: "<<endl;
    for(int i=1; i<n+1; ++i){
        cout<<"For vertex "<<i<<"\tstart: "<<start_ts[i]<<"\tend: "<<end_ts[i]<<endl;
    }

    return 0;
}