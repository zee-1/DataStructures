#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::vector;

#define inf INT32_MAX

vector<vector<int>> floydWarshal(vector<int> v[]){
    int n = v[0].size();
    vector<vector<int>> R[n];
    for(int i=0; i<n; i++){
        R[i].resize(n);
        for(int j=0; j<n; j++){
           R[i][j].resize(n);
        }
    }
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(k==0)    R[k][i][j] = v[i][j];
                else    R[k][i][j] = std::min(R[k-1][i][j],(R[k-1][i][k]==inf || R[k-1][k][j]==inf)?inf:(R[k-1][i][k]+R[k-1][k][j]));
            }
        }
    }
    return R[n-1];
}

void visualizeFloyWarshal(vector<vector<int>> v){
    int n= v.size();
    cout<<"    1   2   3   4   5"<<std::endl;
    std::cout<<"------------------------------"<<std::endl;
    for(int i=0; i<n; i++){
        cout<<1+i<<"|  ";
        for(int j=0; j<n; j++){
            ((v[i][j]==inf)?(cout<<"inf"):(cout<<v[i][j]));cout<<"   ";
        }
        cout<<std::endl;
    }
}
int main(int argc, char const *argv[])
{
    vector<int> v[]={
        {0  ,3  ,8  ,inf,-4 },
        {inf,0  ,inf,1  , 7 },
        {inf,4  ,0  ,-5 ,inf},
        {2  ,inf,inf,0  ,inf},
        {inf,inf,inf,6  ,0  }
    };
    cout<<"Starting floyd washal:"<<std::endl;
    visualizeFloyWarshal(floydWarshal(v));
    cout<<"Ending floyd warshal:" <<std::endl;
    return 0;
}
