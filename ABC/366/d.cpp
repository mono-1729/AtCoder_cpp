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
    ll n; cin >> n;
    vector<vector<vector<ll>>> sum(n+1, vector<vector<ll>>(n+1, vector<ll>(n+1, 0)));
    rep(i,0,n)rep(j,0,n)rep(k,0,n) cin >> sum[i+1][j+1][k+1];
    rep(i,0,n)rep(j,0,n+1)rep(k,0,n+1) sum[i+1][j][k] += sum[i][j][k];
    rep(i,0,n+1)rep(j,0,n)rep(k,0,n+1) sum[i][j+1][k] += sum[i][j][k];
    rep(i,0,n+1)rep(j,0,n+1)rep(k,0,n) sum[i][j][k+1] += sum[i][j][k];
    auto calcsum = [&](int x1, int y1, int z1, int x2, int y2, int z2){
        return sum[x2][y2][z2] - sum[x1][y2][z2] - sum[x2][y1][z2] - sum[x2][y2][z1] + sum[x1][y1][z2] + sum[x1][y2][z1] + sum[x2][y1][z1] - sum[x1][y1][z1];
    };
    ll q; cin >> q;
    rep(i,0,q){
        ll x1, x2, y1, y2, z1, z2; cin >> x1 >> x2 >> y1 >> y2 >> z1 >> z2;
        x1--; y1--; z1--;
        cout << calcsum(x1, y1, z1, x2, y2, z2) << endl;
    }

    return 0;
}