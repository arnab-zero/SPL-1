#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pb push_back
#define spc " "
#define tab "\t"

vi vis(100, 0);         // if a vertex is visited or not
vi previous(100, 0);        // previously visited vertex while traversing 
vi dis(100, INT_MAX);   // distance of vertices from the starting vertex
queue<int> q;           

// BFS function 
void bfs(vector<vi> &v){

    if(q.empty())
        return;

    int node = q.front();
    q.pop();

    if(!vis[node]){
        cout<<" --> "<<node;
        ++vis[node];

        for(auto i: v[node]){
            if(!vis[i]){        // Could've made it easier maybe.
                previous[i] = node;
                dis[i] = dis[node] + 1;
                q.push(i);
            }
        }
    }

    bfs(v);
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
    q.push(start);

    dis[start] = 0;
    previous[start] = -1;

    bfs(v);
    cout<<endl;

    for(int i=1; i<n+1; ++i){
        cout<<"vertex: "<<i<<"\tprevious: "<<previous[i]<<tab;
        cout<<"distance: "<<dis[i]<<endl;
    }

    // for(int i=0; i<n+1; ++i){
    //     for(int j=0; j<v[i].size(); ++j){
    //         cout<<v[i][j]<<spc;
    //     }
    //     cout<<endl;
    // }

    return 0;
}

