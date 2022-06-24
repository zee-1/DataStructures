#pragma once

#include <vector>
#include <initializer_list>

using std::vector;
using std::initializer_list;

template <typename T>
int Largest_elem(T l){
      // Argument must be iterable
      int max= -INT32_MAX;
      for(auto i:l){
            if(i>max)
                  max=i;
      };
      return  max;
}

class DisjointSet{
      vector<int> v;
      DisjointSet();
public:
      bool insert       (int,int);
      void Union        (int A, int B);
      int  find_parent  (int);
      int  countSets    ();
      int Size() {return v.size();};
      void show(){
            for(int i=0 ;i<v.size(); i++){
                  std::cout<<i<<"--"<<v[i]<<std::endl;
            }
      };                   //for debugging purpose only
      int operator[](int a){
            return v[a];
      }
      DisjointSet(int a){
            v.resize(a+1,-1);
            std::cout<<"Set created"<<std::endl;
      };
      DisjointSet(initializer_list<int> l,int set_name){
            auto size = Largest_elem(l);
            v.resize(size+1,-1);
            for(auto i: l){
                  insert(i,set_name);
            };
      };

      
};

bool DisjointSet::insert(int a, int parent){
      if(a>v.size())
            return  false;
      else if(parent==-1)
            v[a]=a;
      else 
            (v[a]=find_parent(parent));
      return true;
}

void DisjointSet::Union(int Set_A, int Set_B){
      if(Set_A>Set_B){
            v[find_parent(Set_B)] = v[find_parent(Set_A)];
            for(auto &i:v){
                  if(i==Set_B){
                        i = Set_A;
                  }
            }
      }else{
            v[find_parent(Set_A)] = v[find_parent(Set_B)];
            for(auto &i:v){
                  if(i==Set_A){
                        i = Set_B;
                  }
            }
      }
}

int DisjointSet::find_parent(int a){
      /*
       returns -1 if element doesn't exists in set
       returns parent if element exists
      */
      
      if(v[a]==-1){
            return -1;
      }
      if (a == v[a])
            return a;
      return find_parent(v[a]);
}

int DisjointSet::countSets(){
set<int> Set(v.begin(),v.end());
int count=Set.size();

return count;
}