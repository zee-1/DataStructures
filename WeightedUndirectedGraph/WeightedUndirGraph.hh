#pragma once

#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <initializer_list>

using std::set;
using std::map;
using std::cin;
using std::cout;
using std::pair;
using std::vector;
using std::initializer_list;

class Undirected_Graph{
      /*
            convention:
                  pair of( int A, set of pair of(int u,int w) S)
                  A - represents Vertex
                  S - is a set of all edges paired with weight
                        here -> u <- is the connected edge and -> w <- is weight
      */
protected:
      friend int connects_to(int a, int b);
      map<int,set<pair<int,int>>> m;
      int size=0;
      void depthFirst(int i,vector<int> &visited){
            if(!visited[i-1]){
                  cout<<i<<std::endl;
                  visited[i-1]=1;
                  for(auto j:m[i])
                        depthFirst(j.first,visited);
            }
      }
public:
      // ~Undirected_Graph(){
      //       std::cout<<"Distructor of map called"<<std::endl;
      // }
      Undirected_Graph();
      Undirected_Graph(initializer_list<pair<int,set<pair<int,int>>>> l){
            std::cout<<"Graph Created"<<std::endl;
            for(auto i: l){
                  // m[i.first] = i.second;
                  for(auto k: i.second)
                        m[i.first].insert(k);
                  for(auto j: i.second)
                        if(!m[j.first].empty())
                              continue;
                        else{
                              m[j.first].insert(pair<int,int>(i.first,j.second));
                        }
            }
      };
      void DFS(int i){
            vector<int> v(m.size(),0);
            depthFirst(i,v);
      }

      void show(){
            for(auto i: m){
                  cout<< i.first<<" -{";
                  for(auto j:m[i.first])
                        cout<<" "<<j.first<<"-"<<j.second;
                  cout<<"}"<<std::endl;
            }
      };
      map<int,set<pair<int,int>>> give_graph(){return m;};

      int Size(){return size;};
      
};
#define node pair<int,set<pair<int,int>>>
# define edge pair<int,int>