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
    ll n, k; cin >> n >> k;
    ll div = k+1, base = ((ll)1e9)/div + 5;
    unordered_map<ll,vector<tuple<ll,ll,ll>>> mp;
    rep(i,0,n){
        ll x, y; cin >> x >> y;
        mp[(x/div+1)*base + y/div+1].push_back({x,y,i+1});
    }
    auto check = [&](ll x1, ll y1, ll x2, ll y2) -> bool {
        return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) <= k*k;
    };
    vector<pll> ans;
    for(auto[key, vec] : mp){
        rep(i,0,vec.size()){
            rep(j,i+1,vec.size()){
                auto [x1, y1, i1] = vec[i];
                auto [x2, y2, i2] = vec[j];
                if(check(x1,y1,x2,y2)) ans.push_back({i1, i2});
            }
        }
        vector<ll> mpid = {key+1, key+base, key+base+1, key+base-1};
        for(auto id: mpid){
            if(!mp.count(id)) continue;
            for(auto [x1, y1, i1] : mp[id])for(auto [x2, y2, i2] : vec){
                if(check(x1,y1,x2,y2)) ans.push_back({i1, i2});
            }
        }
    }   
    cout << ans.size() << endl;
    for(auto &p: ans) if(p.first > p.second) swap(p.first, p.second);
    sort(ans.begin(), ans.end());
    for(auto [a, b]: ans) cout << a << " " << b << endl;
    return 0;
}