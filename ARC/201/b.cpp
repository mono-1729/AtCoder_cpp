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
#define all(x) (x).begin(), (x).end()
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
    ll t; cin >> t;
    while(t--){
        ll n, w; cin >> n >> w;
        vector<vector<ll>> items(61);
        rep(i,0,n){
            ll x, y; cin >> x >> y;
            items[x].push_back(y);
        }
        ll ans = 0;
        rep(i,0,60){
            sort(all(items[i]));
            if(items[i].size() > 0 && (w>>i&1)){
                ans += items[i].back();
                items[i].pop_back();
            }
            while(items[i].size()){
                ll num = items[i].back();
                items[i].pop_back();
                if(items[i].size()){
                    num += items[i].back();
                    items[i].pop_back();
                }
                items[i+1].push_back(num);
            }
        }
        cout << ans << endl;
    }
    return 0;
}