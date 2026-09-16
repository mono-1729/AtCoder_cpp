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

void solve(){
    ll n, m; cin >> n >> m;
    deque<ll> q;
    auto solve = [&](auto solve, ll s, ll id) -> void {
        if(id == n){
            rep(i,0,s+1) q.push_back(i);
            return; 
        }
        ll a; cin >> a;
        if(a > s) solve(solve,s,id+1);
        else{
            ll l = a-1, r = s-a;
            if(l >= r){
                solve(solve,l,id+1);
                rep(i,0,r+1) q.push_back(q[i]);
            }else{
                solve(solve,r,id+1);
                rep(i,0,l+1) q.push_front(q[l]);
            }
        }
    };
    solve(solve,m,0);
    ll ans = 0;
    rep(i,1,m+1) ans ^= (i*(i-q[i]));
    cout << ans << endl;
    // rep(i,1,m+1) cout << q[i] << " ";
    // cout << endl;
}

int main() {
    ll t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}