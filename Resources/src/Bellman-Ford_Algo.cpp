#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pb push_back
#define spc " "
#define tab "\t"

int min_distance[100];
int vis[100];       // used as flag to mark if distances are calculated with respect to that node.
queue<int> q;

void bellman_ford_func(vector<vector<pair<int,int>>> &v){

    // if(q.empty())
    //     return;

    int node = q.front();       // distances will be counted with respect to specified vertex.
    q.pop();
    ++vis[node];

    for(auto x: v[node]){
        if(min_distance[node] + x.second < min_distance[x.first])         // minimum distance of first + given edge weight < minimum distance of second
            min_distance[x.first] = min_distance[node] + x.second;

        if(!vis[x.first]){
            q.push(x.first);
        }
    }

    if(!q.empty())
        bellman_ford_func(v);
}

// Checks for negative cycles in the graph.
bool check_negative_cycles(vector<vector<pair<int,int>>> &v){

    for(int i=1; i<v.size(); ++i){
        for(auto x: v[i]){
            if(min_distance[i] + x.second < min_distance[x.first])         // minimum distance of first + given edge weight < minimum distance of second
                return true;
        }
    }

    return false;
}


int main(void){
    int m, n;   // m = number of edges, n = number of vertices;
    cin>>n>>m;

    vector<vector<pair<int,int>>> v(n+1, vector<pair<int,int>>());     // not sure.

    for(int i=0; i<m; ++i){
        int a, b, w;    // a, b are the connected nodes
                        // w is weight of the edge
        cin>>a>>b>>w;
        v[a].pb({b,w});
        v[b].pb({a,w});
    }

    // for(int i=1; i<n+1; ++i){
    //     cout<<"for "<<i<<": "<<endl;
    //     for(int j=0; j<v[i].size(); ++j){
    //         cout<<v[i][j].first<<tab<<v[i][j].second<<endl;
    //     }
    //     cout<<endl;
    // }

    int start;
    cin>>start;
    q.push(start);
    min_distance[start] = 0;

    for(int i=1; i<n+1; ++i){
        if(i != start)
            min_distance[i] = INT_MAX;
    }

    bellman_ford_func(v);

    if(check_negative_cycles(v)){
        cout<<"Negative cycles exist in the input graph.\n";
        return 0;
    }

    for(int i=1; i<n+1; ++i){
        cout<<"Min distance for node-"<<i<<": "<<min_distance[i]<<endl;
    }

    return 0;
}

