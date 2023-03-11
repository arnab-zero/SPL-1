#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pb push_back
#define spc " "
#define tab "\t"
typedef long long int lli;

vector<int> dis(100, INT_MAX);


// Function for Dijkstra's algorithm
void dijkstra(vector<vector<pair<int,int> > > &v, int source){

    priority_queue<int> pq;
    pq.push(source);

    dis[source] = 0;

    while(!pq.empty()){
        int m = pq.top();
        pq.pop();

        for(auto p: v[m]){
            int n = p.first;
            if(dis[n] > dis[m]+p.second){
                dis[n] = dis[m] + p.second;
                pq.push(n);
            }
        }
    }
}


// Function to print the distance of shortest path of vertices from the source vertex
void print_shortest_distances(int number_of_vertices){
    for(int i=1; i<number_of_vertices+1; ++i){
        cout<<"Shortest distance of vertex "<<i<<" from source is "<<dis[i]<<endl;
    }
}


// main functionS
int main(void){

    int number_of_vertices, number_of_edges;
    cin>>number_of_vertices>>number_of_edges;

    vector<vector<pair<int,int> > > v(number_of_vertices+1);
    for(int i=0; i<number_of_edges; ++i){
        int a, b, w;
        cin>>a>>b>>w;
        v[a].pb({b,w});
        v[b].pb({a,w});
    }

    // cout<<"Printing the list to check."<<endl;
    // for(int i=1; i<number_of_vertices+1; ++i){
    //     cout<<i<<endl;
    //     for(auto p: v[i]){
    //         cout<<p.first<<spc<<p.second<<endl;
    //     }
    // }

    int source;
    cout<<"Enter the source vertex: ";
    cin>>source;

    dijkstra(v, source);
    print_shortest_distances(number_of_vertices);

    return 0;
}
