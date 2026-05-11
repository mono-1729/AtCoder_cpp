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
    if(b == 0) return a;
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
    cout << fixed << setprecision(15);
    ll k; cin >> k;
    ll n = 1 << k;
    vector<ll> r(n);
    rep(i,0,n) cin >> r[i];
    vector<vector<ld>> p(k+1,vector<ld>(n,0));
    vector<vector<ld>> win(n,vector<ld>(n,0));
    vector<ll> pow2(k+1,1);
    rep(i,0,k) pow2[i+1] = pow2[i]*2;
    rep(i,0,n)rep(j,0,n) win[i][j] = 1.0/((ld)1.0+powl(10,(r[j]-r[i])/400.0));
    rep(i,0,n) p[0][i] = 1;
    rep(t,0,k){
        rep(i,0,n)rep(j,0,n){
            if(i/pow2[t] != j/pow2[t] && i/pow2[t+1] == j/pow2[t+1]){
                p[t+1][i] += p[t][i]*p[t][j]*win[i][j];
            }
        }
    }
    rep(i,0,n) cout << p[k][i] << endl;
    return 0;
}