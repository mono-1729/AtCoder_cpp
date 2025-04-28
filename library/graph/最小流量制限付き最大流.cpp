#include<bits/stdc++.h>
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long

//BEGIN CUT HERE
// O(E V^2)
// O(E \min(E^{1/2}, V^{2/3})) if caps are constant

// https://beet-aizu.github.io/library/maxflow/leastflow.cpp.html

template<typename Flow,bool directed>
struct Dinic{
  struct Edge {
    int dst;
    Flow cap;
    int rev;
    Edge(int dst,Flow cap,int rev):dst(dst),cap(cap),rev(rev){}
  };

  vector< vector<Edge> > G;
  vector<int> level,iter;

  Dinic(int n):G(n),level(n),iter(n){}

  int add_edge(int src,int dst,Flow cap){
    int e=G[src].size();
    int r=(src==dst?e+1:G[dst].size());
    G[src].emplace_back(dst,cap,r);
    G[dst].emplace_back(src,directed?0:cap,e);
    return e;
  }

  void bfs(int s){
    fill(level.begin(),level.end(),-1);
    queue<int> que;
    level[s]=0;
    que.emplace(s);
    while(!que.empty()){
      int v=que.front();que.pop();
      for(Edge &e : G[v]) {
        if(e.cap>0 and level[e.dst]<0){
          level[e.dst]=level[v]+1;
          que.emplace(e.dst);
        }
      }
    }
  }

  Flow dfs(int v,int t,Flow f){
    if(v==t) return f;
    for(int &i=iter[v];i<(int)G[v].size();i++){
      Edge &e=G[v][i];
      if(e.cap>0 and level[v]<level[e.dst]){
        Flow d=dfs(e.dst,t,min(f,e.cap));
        if(d==0) continue;
        e.cap-=d;
        G[e.dst][e.rev].cap+=d;
        return d;
      }
    }
    return 0;
  }

  Flow flow(int s,int t,Flow lim){
    Flow fl=0;
    while(1){
      bfs(s);
      if(level[t]<0 or lim==0) break;
      fill(iter.begin(),iter.end(),0);

      while(1){
        Flow f=dfs(s,t,lim);
        if(f==0) break;
        fl+=f;
        lim-=f;
      }
    }
    return fl;
  }

  Flow flow(int s,int t){
    return flow(s,t,numeric_limits<Flow>::max()/2);
  }

  Flow cut(int s,int t,int x,int a){
    static_assert(directed, "must be directed");
    auto &e=G[x][a];
    int y=e.dst;
    Flow cr=G[y][e.rev].cap;
    if(cr==0) return e.cap=0;
    e.cap=G[y][e.rev].cap=0;
    Flow cap=cr-flow(x,y,cr);
    if(x!=s and cap!=0) flow(x,s,cap);
    if(t!=y and cap!=0) flow(t,y,cap);
    return cap;
  }

  Flow link(int s,int t,int x,int a,Flow f){
    auto &e=G[x][a];
    e.cap+=f;
    return flow(s,t,f);
  }
};

template<typename T>
struct LeastFlow{
  Dinic<T, true> G;
  int X,Y;
  T sum;
  LeastFlow(int n):G(n+2),X(n),Y(n+1),sum(0){}

  void add_edge(int from,int to,T low,T hgh){
    assert(low<=hgh);
    G.add_edge(from,to,hgh-low);
    G.add_edge(X,to,low);
    G.add_edge(from,Y,low);
    sum+=low;
  }

  T flow(int s,int t){
    T a=G.flow(X,Y);
    T b=G.flow(s,Y);
    T c=G.flow(X,t);
    T d=G.flow(s,t);
    return (b==c and a+b==sum)?b+d:T(-1);
  }
};

int main() {
    ll h, w; cin >> h >> w;
    vector<string> c(h);
    rep(i,0,h) cin >> c[i];
    LeastFlow<ll> g(h*w+2);
    ll start = h*w, end = h*w+1;
    vector<ll> dx = {1,-1, 0, 0}, dy = {0, 0, 1, -1};
    rep(i,0,h)rep(j,0,w){
        ll id = i*w+j;
        if(c[i][j] == '1') continue;
        ll low = 0, high = 1;
        if(c[i][j] == '2') low = 1;
        if((i+j)%2 == 0){
            g.add_edge(start, id, low, high);
            rep(k,0,4){
                ll ni = i+dx[k], nj = j+dy[k];
                if(ni < 0 || nj < 0 || ni >= h || nj >= w) continue;
                if(c[ni][nj] == '1') continue;
                g.add_edge(id, ni*w+nj, 0, 1);
            }
        }
        else g.add_edge(id, end, low, high);
    }
    if(g.flow(start, end) == -1) cout << "No" << endl;
    else cout << "Yes" << endl;
    return 0;
}