#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <atcoder/all>
using namespace atcoder;
using namespace boost::multiprecision;
using namespace std;
#define rep(i, a, n) for(int i = a; i < n; i++)
#define rrep(i, a, n) for(int i = a; i >= n; i--)
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
    vector<ll> a(n*2), sum(n*2+1,0);
    rep(i,0,n) cin >> a[i], a[i+n] = a[i];
    rep(i,0,n*2) sum[i+1] = sum[i] + a[i];
    vector<vector<ll>> next(n, vector<ll>(20, 0));
    vector<vector<ll>> dp(n, vector<ll>(20, 0));
    auto can = [&](ll x) -> bool {
        rep(i,0,n){
            ll nex = lower_bound(sum.begin(), sum.end(), sum[i]+x) - sum.begin();
            next[i][0] = (nex+n)%n;
            dp[i][0] = nex - i;
        }
        rep(j,1,20) rep(i,0,n){
            next[i][j] = next[next[i][j-1]][j-1];
            dp[i][j] = dp[i][j-1] + dp[next[i][j-1]][j-1];
        }
        ll minv = INF;
        rep(i,0,n){
            ll now = i;
            ll res = 0;
            rrep(j,19,0){
                if(k>>j&1){
                    res += dp[now][j];
                    now = next[now][j];
                }
            }
            chmin(minv, res);
        }
        return minv <= n;
    };
    auto solve = [&](ll x) -> void {
        rep(i,0,n){
            ll nex = lower_bound(sum.begin(), sum.end(), sum[i]+x) - sum.begin();
            next[i][0] = (nex+n)%n;
            dp[i][0] = nex - i;
        }
        rep(j,1,20) rep(i,0,n){
            next[i][j] = next[next[i][j-1]][j-1];
            dp[i][j] = dp[i][j-1] + dp[next[i][j-1]][j-1];
        }
        ll cnt = 0;
        rep(i,0,n){
            ll now = i;
            ll res = 0;
            rrep(j,19,0){
                if(k>>j&1){
                    res += dp[now][j];
                    now = next[now][j];
                }
            }
            if(res <= n) cnt++;
        }
        cout << n - cnt << endl;
    };
    ll l = 0, r = 3e9;
    while(r-l > 1){
        ll m = (l+r)/2;
        if(can(m)) l = m;
        else r = m;
    }
    cout << l << " ";
    solve(l);
    return 0;
}