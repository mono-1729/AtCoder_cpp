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
    ll t; cin >> t;
    vector<vector<ll>> check(31, vector<ll>(200005, 0));
    vector<vector<ll>> ans(31);
    vector<ll> pow2(31, 1);
    rep(i,1,31) pow2[i] = pow2[i-1] * 2;
    rep(kk,1,31){
        rep(i,1,200005){
            if(i >= pow2[kk]) break;
            if(check[kk][i] == 0){
                ll num = i;
                while(num * 2 < pow2[kk]) num *= 2;
                ans[kk].push_back(num);
                for(ll j = i; j < 200005; j *= 2){
                    check[kk][j] = 1;
                }
            }
        }
    }
    while(t--){
        ll n, k; cin >> n >> k;
        vector<ll> a;
        rep(i,0,n){
            if(ans[k].size() > i){
                a.push_back(ans[k][i]);
            }else{
                a.push_back(1);
            }
        }
        for(auto x : a) cout << x << " ";
        cout << endl;
    }
    return 0;
}