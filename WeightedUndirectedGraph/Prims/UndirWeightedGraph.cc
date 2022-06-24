#include <queue>
#include <initializer_list>
#include <iostream>
#include <vector>
#include <map>
#include <cstring>

using std::map;
using std::cin;
using std::cout;
using std::pair;
using std::vector;
using std::priority_queue;
using std::initializer_list;

class graph{
      friend pair<vector<int>,vector<int>> prims(graph& g);
      map<int,vector<pair<int,int>>> m;
      graph();
public:
      graph(initializer_list<pair<int,vector<pair<int,int>>>> l){
            for(auto i: l){
                  m[i.first] = i.second;
                  for(auto j: i.second)
                        if(!m[j.first].empty())
                              continue;
                        else{
                              m[j.first].push_back(pair<int,int>(i.first,j.second));                  
                  }
            }
      }
      void show(){
            for(auto i: m){
                  cout<<i.first<<",";
                  for(auto j: i.second)
                        cout<<j.first<<"-"<<j.second<<" ";
                  cout<<std::endl;
            }
      }
      int size(){ return m.size(); }
      
};
int give_min(vector<int> arr,vector<int> visited,int size){
      auto min=-1,min_val = INT32_MAX;
      for(int i=0; i<size; i++){
            if(!visited[i] && min_val>=arr[i]){
                  min_val = arr[i]; min = i;
            }
      }

      return min;
}

pair<vector<int>,vector<int>> prims(graph& g){
      vector<int> cost(g.size(),INT32_MAX);
      vector<int> parent(g.size(),-1);
      vector<int> visited(g.size(),0);

      cost[0]=0;
      parent[0]=0;

      int n=g.size();
      n--;
      while((n)--){
            int node = give_min(cost,visited,g.size());
            visited[node] =1;
            for(auto i: g.m[node]){
                  if(cost[i.first]>i.second ){
                        cost[i.first] = i.second;
                        parent[i.first] = node;
                  }
            }
      }
      pair<vector<int>,vector<int>> p(cost,parent);

      return p;
}
#define node pair<int,vector<pair<int,int>>>
#define N    pair<int,int>
int main(int argc, char const *argv[])
{
      initializer_list<pair<int,vector<pair<int,int>>>> l = {node(0,{N(1,1),N(2,2),N(3,4),N(4,0)}),
                                                   node(1,{N(0,1),N(2,8)}),
                                                   node(2,{N(0,2),N(3,3),N(6,8)}),
                                                   node(3,{N(0,4),N(2,3),N(4,6)}),
                                                   node(4,{N(0,0),N(3,6),N(5,2)}),
                                                   node(5,{N(4,2),N(6,-1)}),
                                                   node(6,{N(2,8),N(5,-1)})};
      graph g(l);
      auto n = g.size();
      auto ans = prims(g);
      for(int i=0; i<n; i++){
            cout<<i<<'-'<<ans.second[i]<<" at cost "<<ans.first[i]<<std::endl;
      }

      return 0;
}
