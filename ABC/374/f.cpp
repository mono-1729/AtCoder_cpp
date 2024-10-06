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
    ll n, k, x; cin >> n >> k >> x;
    vector<ll> t(n), sum(n+1, 0);
    rep(i, 0, n) cin >> t[i];
    rep(i, 0, n) sum[i+1] = sum[i] + t[i];
    set<ll> st;
    st.insert(-x);
    rep(i, 0, n){
        st.insert(t[i]);
        rep(j, 1, n+1) st.insert(t[i] + x*j);
    }
    unordered_map<ll, ll> mp;
    vector<ll> v;
    ll cnt = 0;
    for(auto i : st) mp[i] = cnt++, v.push_back(i);
    vector<vector<ll>> dp(cnt+1, vector<ll>(n+1,INF));
    dp[0][0] = 0;
    rep(i, 0, cnt){
        rep(j, 0, n+1){
            if(dp[i][j] == INF) continue;
            chmin(dp[i+1][j], dp[i][j]);
            rep(num, 1, k+1){
                if(j+num > n) break;
                ll nt = max(t[j+num-1], v[i]+x);
                chmin(dp[mp[nt]][j+num], dp[i][j]+num*nt-(sum[j+num]-sum[j]));
            }
        }
    }
    cout << dp[cnt][n] << endl;
    return 0;
}