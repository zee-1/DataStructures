// Dijkstra algorithm 
#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
  Graph(int n) : n_(n), g_(n) {}
  void AddEdge(int u, int v, int w) {
    g_[u].push_back(Edge(v, w));
  }
  vector<int> Dijkstra(int s) {
    std::vector<int> dist(n_, INT32_MAX);
    std::vector<bool> used(n_, false);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
    dist[s] = 0;
    q.push(std::make_pair(0, s));
    while (!q.empty()) {
      int d = q.top().first;
      int v = q.top().second;
      q.pop();
      if (used[v]) continue;
      used[v] = true;
      for (auto e : g_[v]) {
        if (dist[e.to] > dist[v] + e.w) {
          dist[e.to] = dist[v] + e.w;
          q.push(std::make_pair(dist[e.to], e.to));
        }
      }
    }
    return dist;
  }
private:
      struct Edge {
      int to, w;
      Edge(int to, int w) : to(to), w(w) {}
      };
      int n_;
      std::vector<std::vector<Edge>> g_;
};
int main(int argc, char const *argv[])
{
  Graph g(6+1);
  g.AddEdge(1,2,1);
  g.AddEdge(2,1,1);
  g.AddEdge(1,5,4);
  g.AddEdge(5,1,4);
  g.AddEdge(2,3,3);
  g.AddEdge(3,2,3);
  g.AddEdge(2,5,5);
  g.AddEdge(5,2,5);
  g.AddEdge(3,4,1);
  g.AddEdge(4,3,1);
  g.AddEdge(3,6,0);
  g.AddEdge(6,3,0);
  g.AddEdge(3,2,3);
  g.AddEdge(5,6,6);
  g.AddEdge(6,5,6);
  

  auto a = g.Dijkstra(1);

  for(int i=1; i<=6;i++){
    std::cout<<"Cost of "<<1<<" to "<< i <<' ' << a[i] <<std::endl;
  }
  return 0;
}
