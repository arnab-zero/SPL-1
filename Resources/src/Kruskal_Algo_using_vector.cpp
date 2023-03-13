#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pb push_back
#define spc " "
#define tab "\t"
typedef long long int lli;


// initializing parents
void make_ds(int ds[], int v){
    ds[v] = v;
}

// function for disjoint set find operation
int ds_find(int ds[], int v){

    if(ds[v]==v)
        return v;
    else 
        return ds[v] = ds_find(ds,ds[v]);
}

// function for disjoint set union
int ds_union(int ds[], int u, int v){

    int parent_u = ds_find(ds,u), parent_v = ds_find(ds,v);

    if(parent_u != parent_v){
        ds[parent_v] = parent_u;
    }
    else    
        return -1;
}


vector<pair<int,int>> mst;

// Compare function for priority queue
bool comparePairs (const pair<int, pair<int,int>>& a, const pair<int, pair<int,int>>& b) {
        return a.first < b.first; // Compare based on the first integer value
}


int main(void){

    int vertices; 
    cout<<"Enter the number of vertices: ";
    cin>>vertices;

    int edges;
    cout<<"Enter the number of edges: ";
    cin>>edges;

    int ds[vertices+1];     // Disjoint set of the vertices

    for(int i=1; i<vertices+1; ++i){
        make_ds(ds,i);
    }

    cout<<endl<<"Enter the adjacency list: "<<endl;

    vector<pair<int, pair<int,int>>> list;     // **********

    for(int i=0; i<edges; ++i){
        int u, v, w;
        cin>>u>>v>>w;
        list.pb({w,{u,v}});
    }

    sort(list.begin(), list.end(), comparePairs);

    vector<pair<int,int>> mst;
    int minimum_path_weight = 0;

    for(int i=0; i<list.size(); ++i){

        auto element = list[i];

        int u = element.second.first, v = element.second.second;

        if(ds_union(ds,u,v) != -1){
            mst.pb({u,v});
            minimum_path_weight += element.first;       // Summing up the total weight
        }
    }

    cout<<endl<<endl<<"Total minimum path weight: "<<minimum_path_weight<<endl;

    for(auto i: mst){
        cout<<(char)(i.first+'a'-1)<<spc<<(char)(i.second+'a'-1)<<endl;
    }

    return 0;
}
