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
    ll k; cin >> k;
    string s, t; cin >> s>> t;
    ll n = s.size(), m = t.size();
    if(abs(n - m) > k){
        cout << "No" << endl;
        return 0;
    }
    vector<ll> dp(k*2+1, INF);
    rep(i,0,k+1) if(i <= m) dp[i+k] = i; 
    rep(i,0,n){
        vector<ll> ndp(k*2+1, INF);
        rep(j,-k,k+1){
            if(dp[j+k] == INF) continue;
            if(i + j > m) continue;
            if(i + j < 0) continue;
            if(s[i] == t[i+j]){
                chmin(ndp[j+k], dp[j+k]);
            }else{
                chmin(ndp[j+k], dp[j+k]+1);
            }
            if(j > -k) chmin(ndp[j+k-1], dp[j+k]+1);        
        }
        rep(j,1,k*2+1){
            if(i+j+1-k > m) break;
            chmin(ndp[j], ndp[j-1]+1);
        }
        swap(dp, ndp);
    }
    if(dp[k+(m-n)] <= k) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}