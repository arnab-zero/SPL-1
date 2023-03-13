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
void ds_union(int ds[], int u, int v){

    int parent_u = ds_find(ds,u), parent_v = ds_find(ds,v);

    if(parent_u != parent_v){
        ds[parent_v] = parent_u;
        cout<<"Included to a same tree."<<endl;
    }
    else 
        cout<<"Already in the same tree."<<endl;
}

// main function
int main(void){

    int vertices;
    cin>>vertices;

    int ds[vertices+1];
    for(int i=1; i<vertices+1; ++i){
        make_ds(ds,i);
    }

    int q;
    cin>>q;
    while(q--){
        int t;
        cin>>t;

        if(t==1){
            int u;
            cin>>u;
            cout<<"Parent: "<<ds_find(ds,u)<<endl;
        }
        else if(t==2){
            int u, v;
            cin>>u>>v;
            ds_union(ds,u,v);
        }
    }

    return 0;
}
