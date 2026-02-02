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
    ll n, k; cin >> n >> k;
    vector<ll> c(n,0);
    queue<vector<mint>> q;
    rep(i,0,n){
        ll x; cin >> x;
        x--;
        q.push({c[x],1});
        c[x]++;
    }
    while(q.size() > 1){
        vector<mint> a = q.front(); q.pop();
        vector<mint> b = q.front(); q.pop();
        q.push(convolution(a, b));
    }
    mint ans = 0;
    vector<mint> vec = q.front();
    // for(auto x: vec) cout << x.val() << " ";
    // cout << endl;
    rep(i,0,n+1){
        if((n-i)%2 == k%2 && i >= n-k){
            ans += vec[i];
        }
    }
    cout << ans.val() << endl;
    return 0;
}