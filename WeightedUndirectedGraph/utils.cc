#include "WeightedUndirGraph.hh"
set<vector<int>> Map_to_EgdeList(Undirected_Graph &g){
set<vector<int>> Sol;
auto Graph = g.give_graph();
      for(auto i: Graph){
            for(auto j:i.second){
                  /*
                        {weight, u, v}    ->> Weighted Edge List
                  */
                  vector<int> v(3);
                  v[0]=j.second;
                  v[1]=i.first;
                  v[2]=j.first;
                  Sol.insert(v);
            };
      }
return Sol;
};



void merge(vector<vector<int>> &s, int l,int mid,int h){
      vector<vector<int>> L(mid-l+1);
      vector<vector<int>> R(h-mid+1);
      int t1=0;
      for(size_t i=l; i<=mid;i++){
           L[t1] = s[i];
           t1++; 
      }
      t1=0;
      for(size_t i=mid+1; i<=h; i++){
            R[t1] = s[i];
            t1++;
      }

      int i=0,j=0,k=0;
      while(i<mid+1 and j<h+1){
            if(L[i]<R[j]){
                  s[k]=L[i];
                  i++;
            }
            else{
                  s[k]=R[j];
                  j++;
            }
            k++;
      }
      while(i<mid+1){
            s[k]=L[i];
            i++;k++;
      }
      while(j<h+1){
            s[k]=L[j];
            j++;k++;
      }
}
void merge_sort(vector<vector<int>> &s, int l, int h){
      if (l==h){
            return;
      }else{
            auto mid = (l+h)/2;
            merge_sort(s,l,mid);
            merge_sort(s,mid+1,h);
            merge(s,l,mid,h);
      }
};


set<vector<int>> Sort_EdgeList(set<vector<int>> &s){

vector<vector<int>> temp(s.begin(),s.end());
merge_sort(temp,0,temp.size()-1);
set<vector<int>> Temp(temp.begin(),temp.end());
return Temp;
}

int Biggest_edge(set<vector<int>> &l){
      // Argument must be iterable
      int max= -INT32_MAX;
      for(auto i:l){
            if(i[1]>max)
                  max=i[1];
      };
      return  max;
}