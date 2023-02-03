#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pb push_back
#define pii pair<int, int>
#define spc " "
#define tab "\t"

vi vis(100);          // flags to note if a node is visited.
vi dis(100, INT_MAX); // initially distance of each node from the starting node is infinite.
priority_queue<pii, greater<pii>> pq;         // queue to maintain sequence of nodes that will be visited later.
int start;          // source node.

// function for dijkstra's algorithm
void dijkstra(vector<vector<pii>> &v)
{
    if(pq.empty())      // if priority queue ends up to be empty, we stop recursion
        return;

    pii node = pq.top();    // we take the first element from the min-priority queue
    pq.pop();       // pop the first element

    if(vis[node.second])
        return;

    for(int i=0; i<v[node.second].size(); ++i){
        int current = v[node][i].second;       // node associated by edge 

        if(node.first + v[node][i].first < dis[current]){
            dis[current] = dis[node] + v[node][i].first;
            pq.push({dis[current], current});
        }
    }

    vis[node.second] = 1;

    // int maxDistance = 0, newNode;
    // for(int i=0; i<v[node].size(); ++i){
    //     if(v[node][i].second > maxDistance){
    //         maxDistance = v[node][i].second;
    //         newNode = v[node][i].first;
    //     }
    // }

    dijkstra(v);
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

        v[b].pb({w, a});        // as we will keep it arranged by the first element in priority queue
        v[a].pb({w, b});
    }

    // for(int i=1; i<m+1; ++i){
    //     for(int j=0; j<v[i].size(); ++j){
    //         cout<<i<<tab<<v[i][j].first<<tab<<v[i][j].second<<endl;
    //     }
    // }

    cin >> start;

    dis[start] = 0;
    pq.push({0, start});    // pushing the source node to priority queue

    dijkstra(v);

    // print here.

    return 0;
}