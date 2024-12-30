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
    ll n, m; cin >> n >> m;
    map<ll,vector<pll>> mp;
    rep(i, 0, m){
        ll x, y; cin >> x >> y;
        char c; cin >> c;
        ll cc = (c == 'B' ? 0 : 1);
        mp[y].push_back({x, cc});
    }
    ll ok = 1;
    ll lastb = IINF;
    for(auto& [k, v] : mp){
        sort(v.begin(), v.end());
        ll flg = false;
        rep(i, 0, v.size()){
            if(v[i].second == 1){
                flg = true;
                chmin(lastb,v[i].first-1);
            }else{
                if(flg) ok = 0;
                if(lastb < v[i].first) ok = 0;
            }
        }
    }
    if(ok) cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}