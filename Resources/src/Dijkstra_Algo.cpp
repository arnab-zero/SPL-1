#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pb push_back
#define pii pair<int, int>
#define spc " "
#define tab "\t"
typedef long long int lli;

vector<vector<pair<int, int>>> adj_list(100);
vector<int> dis(100, INT_MAX);


void dijkstra(int vertices, int source){

    priority_queue<pii, vector<pii>, greater<pii>> pq;

    dis[source] = 0;
    pq.push({dis[source], source});

    while(!pq.empty()){

        int current = pq.top().second;
        pq.pop();

        for(auto i: adj_list[current]){
            
            if(dis[current]+i.second < dis[i.first]){
                dis[i.first] = dis[current]+i.second;
                pq.push({dis[i.first], i.first});
            }
        }
    }
}


int main(void){

    int vertices;
    cin>>vertices;
    
    int edges;
    cin>>edges;

    for(int i=0; i<edges; ++i){
        int u, v, w;
        cin>>u>>v>>w;
        adj_list[u].pb({v,w});
    }

    int source;
    cin>>source;

    dijkstra(vertices, source);

    for(int i=1; i<vertices+1; ++i){
        if(dis[i]!=INT_MAX)
            cout<<"Shortest distance to vertex "<<i<<" from vertex "<<source<<" is "<<dis[i]<<endl;
        else 
            cout<<"No path to vertex "<<i<<" from vertex "<<source<<endl;
    }

    return 0;
}
