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
    ll n, m, q; cin >> n >> m >> q;
    vector<pll> ans(q);
    vector<set<pll>> now(n+m);
    vector<tuple<ll,ll,ll,ll,ll>> query;
    rep(i,0,m){
        ll a, b, s, t; cin >> a >> b >> s >> t;
        a--;b--;
        query.push_back({s,1,a,i+n,b});
        query.push_back({t,0,a,i+n,b});
    }
    rep(i,0,q){
        ll x, y, z; cin >> x >> y >> z;
        y--;
        query.push_back({x,-1,z,y,i});
    }
    sort(query.begin(), query.end());
    for(auto query_ : query){
        if(get<1>(query_) == -1){
            auto [start_time, type, end_time, start_pos, idx] = query_;
            now[start_pos].insert({end_time,idx});
        }else if(get<1>(query_) == 0){
            auto [start, type, v, bus, nv] = query_;
            while(!now[bus].empty() && (*now[bus].begin()).first <= start){
                auto [time,idx] = *now[bus].begin();
                now[bus].erase(now[bus].begin());
                ans[idx] = {v,nv};
            }
            if(now[bus].size() > now[nv].size()) swap(now[bus],now[nv]);
            for(auto x: now[bus]) now[nv].insert(x);
            now[bus].clear();
        }else{
            auto [start, type, v, bus, nv] = query_;
            while(!now[v].empty() && (*now[v].begin()).first <= start){
                auto [time,idx] = *now[v].begin();
                now[v].erase(now[v].begin());
                ans[idx] = {v,-1};
            }
            if(now[v].size() > now[bus].size()) swap(now[v],now[bus]);
            for(auto x: now[v]) now[bus].insert(x);
            now[v].clear();
        }
    }

    rep(i,0,n){
        for(auto x: now[i]) ans[x.second] = {i,-1};
    }
    for(auto [a,b]: ans){
        if(b == -1) cout << a+1 << endl;
        else cout << a+1 << " " << b+1 << endl;
    }
    return 0;
}