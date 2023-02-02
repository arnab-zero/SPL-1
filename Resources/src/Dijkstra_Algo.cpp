#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pb push_back
#define spc " "
#define tab "\t"

vi vis(100);          // flags to note if a node is visited.
vi dis(100, INT_MAX); // initially distance of each node from the starting node is infinite.
queue<int> q;         // queue to maintain sequence of nodes that will be visited later.

// function for dijkstra's algorithm
void dijkstra(vector<vector<pair<int, int>>> &v, int node)
{
    if(vis[node])
        return;

    for(int i=0; i<v[node].size(); ++i){
        int current = v[node][i].first;

        if(dis[node] + v[node][i].second < dis[current])
            dis[current] = dis[node] + v[node][i].second;
    }

    vis[node] = 1;

    int maxDistance = 0, newNode;

    for(int i=0; i<v[node].size(); ++i){
        if(v[node][i].second > maxDistance){
            maxDistance = v[node][i].second;
            newNode = v[node][i].first;
        }
    }

    dijkstra(v, newNode);
}

// main function
int main(void)
{
    int m, n; // m = number of edges, n = number of vertices;
    cin >> n >> m;

    vector<vector<pair<int, int>>> v(m + 1); // 2d vector of pairs to store the weighted edges.

    for (int i = 1; i < m + 1; ++i)
    {
        int a, b, w; // a, b are connected vertices and w is the weight of the edge.
        cin >> a >> b >> w;

        v[b].pb({a, w});
        v[a].pb({b, w});
    }

    // for(int i=1; i<m+1; ++i){
    //     for(int j=0; j<v[i].size(); ++j){
    //         cout<<i<<tab<<v[i][j].first<<tab<<v[i][j].second<<endl;
    //     }
    // }

    int start; // node to calculate distances from.
    cin >> start;

    
    dis[start] = 0;

    // q.push(start);

    dijkstra(v, start);

    // print here.

    return 0;
}