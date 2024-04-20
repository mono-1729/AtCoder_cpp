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
    ll n;cin>>n;
    vector<vector<ll>> g(n);
    vector<ll> a(n);
    rep(i,0,n)cin>>a[i];
    rep(i,0,n-1){
        ll u,v;cin>>u>>v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    ll ok = 1,ng =1e9+1,mid;
    auto solve = [&](auto& solve, ll v, ll p, ll up, ll low, ll upmin, ll lowmax, ll depth)->ll{
        // cout<<ok<<" "<<ng<<" "<<mid<<" "<<v<<endl;
        if(a[v]>=mid){
            up++;
            chmin(upmin,a[v]);
        }
        else{
            low++;
            chmax(lowmax,a[v]);
        }
        if(p!=-1 && g[v].size()==1) return(up>low || (up==low && (upmin+lowmax)/2>=mid));
        ll res = depth%2;
        for(auto nv:g[v]){
            if(nv==p) continue;
            if(solve(solve,nv,v,up,low,upmin,lowmax,depth+1)==1-depth%2) res = 1-depth%2;
        }
        return res;
    };
    while(ng-ok>1){
        mid = (ng+ok)/2;
        //cout<<ok<<" "<<ng<<" "<<mid<<endl;
        if(solve(solve,0,-1,0,0,INF,0,0))ok = mid;
        else ng = mid;
    }
    cout<<ok<<endl;
    return 0;
}