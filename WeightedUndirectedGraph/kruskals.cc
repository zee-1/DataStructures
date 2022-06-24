#include "utils.cc"
#include "WeightedUndirGraph.hh"
#include "DisjointSet.hh"
#include <queue>

using namespace std;

int kruskalsAlgo(Undirected_Graph &g){

      set<vector<int>> edgeList = Map_to_EgdeList(g);
      auto lastEdge = Biggest_edge(edgeList);
      DisjointSet s(lastEdge);

      int cost=0;
      int count =lastEdge;
      for(auto i :edgeList){
            if(count){
                  auto set_a = s.find_parent(i[1]);
                  auto set_b = s.find_parent(i[2]);
            if(set_a==-1 and set_b==-1){
                  s.insert    (i[1],-1);
                  s.insert    (i[2],i[1]);
                  std::cout<<"Selected Edge:"<< i[1]<<" - "<<i[2] <<std::endl;
                  
                  count -=2;cost+=i[0];
            }else if(set_a !=set_b){
                  s.Union(set_a,set_b);
                  cost+=i[0];
                  std::cout<<"Selected Edge:"<< i[1]<<" - "<<i[2] <<std::endl;

            }else{
                  continue;
            }
      }
      };
      cout<<" \nTotal cost:"<<cost<<endl;
return cost;
}


int main(int argc, char const *argv[])
{      initializer_list<node> l = {node(1,{edge(2,3),edge(4,1),edge(5,2)}),node(2,{edge(3,1),edge(5,3)}),node(4,{edge(2,9)})};
      Undirected_Graph G(l);
      auto list = Map_to_EgdeList(G);

      for( auto i:list){
            cout<<i[0]<<" "<<i[1]<<" "<<i[2]<<"\n";
      }

      kruskalsAlgo(G);

      return 0;
}
