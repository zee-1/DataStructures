#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::cin;

#define inf INT32_MAX

class Graph{
      int** matrix;
      int x;
      Graph();
public:
Graph(int x){
      this->x = x;
      matrix = new int*[x];
      for(int i=0;  i<x; i++){
            matrix[i] = new int[x];
      }
};
Graph(int x, int **arr){
      this->x = x;
      matrix  = new int*[x];
      
      for(int i=0;  i<x; i++){
                  matrix[i]     = new int[x];
      }
      for(int i=0; i<x; i++){
            for(int j=0; j<x; j++){
                  matrix [i][j] = arr[i][j];
            }
      }
};
vector<int> bellman_ford(int src){
vector<int> v          (x,INT32_MAX);
vector<int> prev_parent(x,-1);
v[src] =0;

for(int i=0; i<x;i++){
      for(int j =0;j<x;j++){
            int temp = (matrix[i][j]==inf || v[j]==inf)?inf:(matrix[i][j] + v[j]);
            if( temp < v[i]){
                  v[i] = temp;
                  prev_parent[i] = j;
            }
}

for(int i=0; i<x;i++){
      for(int j=0; j<x;j++){
            int temp = (v[j]==inf || matrix[i][j]==inf)?inf:( v[j]+matrix[i][j] );
            if(temp< v[i]){
                  std::cout<<"Negative Cycle detected! With new cost "<<temp<<" and prev was "<<v[i]<<std::endl;
            }
      }
}
}
return v;
}
}; 

int main(int argc, char const *argv[])
{
      int x=6;
      int ** matrix = new int*[x];
      for(int i=0;  i<x; i++){
            matrix[i] = new int[x];
      }
      int arr[6][6] = {
            {0,1,2,4,0,inf},
            {1,0,8,inf,inf,inf},
            {2,8,0,3,inf,7},
            {4,inf,3,0,6,inf},
            {0,inf,inf,6,0,2},
            {inf,inf,7,inf,2,0}
      };

      for(int i=0; i<6; i++){
            for(int j=0; j<6;j++){
                  matrix[i][j] = arr[i][j];
            }
      }
      Graph g(6,matrix);
      auto temp=g.bellman_ford(1); 
      
      for(int i=0; i<temp.size(); i++){
            cout<<"Cost of "<<1 <<" - "<<i<<" = "<<temp[i]<<std::endl;
      }
      return 0;
}
