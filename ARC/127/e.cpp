#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
#define ld long double
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

ll powMod(ll x, ll n, ll mod) {
    if (n == 0) return 1 % mod;
    ll val = powMod(x, n / 2, mod);
    val *= val;
    val %= mod;
    if (n % 2 == 1) val *= x;
    return val % mod;
}

int main() {
    ll a, b; cin >> a >> b;
    ll n = a+b;
    vector<ll> p(n);
    rep(i,0,n) cin >> p[i];
    vector<ll> num;
    set<ll> st;
    ll cnt = 0;
    for(auto x: p){
        if(x == 1) st.insert(cnt++);
        else num.push_back(*st.rbegin()), st.erase(*st.rbegin());
    }
    sort(all(num));
    vector<mint> dp(a+1);
    dp[0] = 1;
    rep(i,0,b){
        vector<mint> ndp(a+1);
        vector<mint> sum(a+1);
        rep(j,0,a) sum[j+1] = sum[j]+dp[j];
        rep(j,num[i]+1,a+1){
            ndp[j] = sum[j];
        }
        swap(dp,ndp);
    }
    mint ans = 0;
    for(auto x: dp) ans += x;
    cout << ans.val() << endl;
    return 0;
}