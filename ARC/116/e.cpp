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
    ll n,k;cin>>n>>k;
    vector<vector<ll>> g(n);
    rep(i,0,n-1){
        ll x,y;cin>>x>>y;
        x--;y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    ll ng = 0,ok = n;
    while(ok-ng>1){
        ll mid=(ok+ng)/2;
        auto solve = [&](auto& solve,ll v,ll p)->pll{
            pll res = {0,0};
            for(auto nv:g[v]){
                if(nv==p)continue;
                pll tmp = solve(solve,nv,v);
                res.second+=tmp.second;
                if(res.first<=0 && tmp.first<=0) chmin(res.first,tmp.first);
                else if(res.first>=0 && tmp.first>=0) chmax(res.first,tmp.first);
                else if(res.first>0){if(res.first<abs(tmp.first))res.first=tmp.first;}
                else if(abs(res.first)<=tmp.first)res.first=tmp.first;
            }
            if(res.first==mid)return{-mid,res.second+1};
            else return {res.first+1,res.second};
        };
        pll x = solve(solve,0,-1);
        if(x.first>0)x.second++;
        if(x.second>k)ng=mid;
        else ok=mid;
    }
    cout<<ok<<endl;
    return 0;
}