#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <atcoder/all>
using namespace atcoder;
using namespace boost::multiprecision;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint998244353;

ll gcd(ll a, ll b){
    if(a%b == 0){
      return b;
    }else{
      return gcd(b, a%b);
    }
}

ll lcm(ll a, ll b){
    return a*b / gcd(a, b);
}

ll powMod(ll x, ll n) {
    if (n == 0) return 1 % MOD;
    ll val = powMod(x, n / 2);
    val *= val;
    val %= MOD;
    if (n % 2 == 1) val *= x;
    return val % MOD;
}

int main() {
    ll n,m,k,l;cin>>n>>m>>k>>l;
    vector<ll> a(n),b(l);
    rep(i,0,n)cin>>a[i],a[i]--;
    rep(i,0,l)cin>>b[i],b[i]--;
    vector<vector<pll>> g(n);
    rep(i,0,m){
        ll u,v,c;cin>>u>>v>>c;
        u--;v--;
        g[u].push_back({v,c});
        g[v].push_back({u,c}); 
    }
    vector<vector<pll>> dist(n,vector<pll>(2,{INF,-1}));
    priority_queue<tuple<ll,ll,ll>,vector<tuple<ll,ll,ll>> , greater<tuple<ll,ll,ll>>> pq;
    rep(i,0,l){
        pq.push({0,b[i],a[b[i]]});
        dist[b[i]][0] = {0,a[b[i]]};
    }
    while(!pq.empty()){
        ll d,v,country;tie(d,v,country)= pq.top();
        pq.pop();
        if((dist[v][0].first!=d || dist[v][0].second!=country)&&(dist[v][1].first!=d && dist[v][1].second!=country)) continue;
        for(auto nq:g[v]){
            ll nv = nq.first,cost=nq.second;
            if(country == dist[nv][0].second){
                if(dist[nv][0].first>d+cost){
                    dist[nv][0].first=d+cost;
                    pq.push({d+cost,nv,country});
                }
            }
            else if(country == dist[nv][1].second){
                if(dist[nv][1].first>d+cost){
                    dist[nv][1].first=d+cost;
                    pq.push({d+cost,nv,country});
                    if(dist[nv][0].first>dist[nv][1].first) swap(dist[nv][0],dist[nv][1]);
                }
            }
            else if (dist[nv][0].first>d+cost){
                swap(dist[nv][0],dist[nv][1]);
                dist[nv][0]={d+cost,country};
                pq.push({d+cost,nv,country});
            }
            else if (dist[nv][1].first>d+cost){
                dist[nv][1]={d+cost,country};
                pq.push({d+cost,nv,country});
            }
        }
    }
    rep(i,0,n){
        if(dist[i][0].second!=-1 && dist[i][0].second!=a[i]) cout<<dist[i][0].first<<" ";
        else if(dist[i][1].second!=-1 && dist[i][1].second!=a[i]) cout<<dist[i][1].first<<" ";
        else cout<<-1<<" ";
    }
    cout<<endl;
    return 0;
}