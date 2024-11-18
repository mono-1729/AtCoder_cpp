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
    ll n, m, l; cin >> n >> m >> l;
    vector<ll> card(n+m+l);
    rep(i, 0, n+m+l) cin >> card[i];
    map<tuple<ll,ll,ll>, ll> dp;
    map<tuple<ll,ll,ll>, ll> check;
    auto calc = [&](auto calc, ll x, ll y, ll turn){
        if(check[{x,y,turn}] == 1) return dp[{x,y,turn}];
        check[{x,y,turn}] = 1;
        vector<ll> ta, ao, ba;
        rep(i,0,n+m+l){
            if(((x>>i)&1) == 1) ta.push_back(i);
            else if(y>>i&1) ao.push_back(i);
            else ba.push_back(i);
        }
        if(turn == 0){
            for(auto i : ta){
                for(auto j : ba){
                    if(card[i] > card[j]){
                        if(calc(calc, x^(1LL<<i)^(1LL<<j), y, 1) == 0) return dp[{x,y,turn}] = 0;
                    }
                }
                if(calc(calc, x^(1LL<<i), y, 1) == 0) return dp[{x,y,turn}] = 0;
            }
            return dp[{x,y,turn}] = 1;
        }
        else{
            for(auto i : ao){
                for(auto j : ba){
                    if(card[i] > card[j]){
                        if(calc(calc, x, y^(1LL<<i)^(1LL<<j), 0) == 1) return dp[{x,y,turn}] = 1;
                    }
                }
                if(calc(calc, x, y^(1LL<<i), 0) == 1) return dp[{x,y,turn}] = 1;
            }
            return dp[{x,y,turn}] = 0;
        }
    };
    ll sx = 0, sy = 0;
    rep(i,0,n) sx += 1LL<<i;
    rep(i,n,n+m) sy += 1LL<<i;
    if(calc(calc, sx, sy, 0) == 0) cout << "Takahashi" << endl;
    else cout << "Aoki" << endl;
    return 0;
}