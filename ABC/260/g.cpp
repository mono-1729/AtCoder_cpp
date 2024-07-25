#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <atcoder/all>
using namespace atcoder;
using namespace boost::multiprecision;
using namespace std;
#define rep(i, a, n) for(int i = a; i < n; i++)
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
    int n, m; cin >> n >> m;
    vector<string> s(n);
    rep(i,0,n) cin >> s[i];
    vector<vector<int>> col(n,vector<int>(n+1,0)),diag(3*n,vector<int>(n+1,0));

    rep(i,0,n){
        rep(j,0,n){
            if(s[i][j] == 'O'){
                col[j][i]++;
                col[j][min(n,i+m)]--;
                if(2*i+j+2*m < 3*n){
                    diag[2*i+j+2*m][i]--;
                    diag[2*i+j+2*m][min(n,i+m)]++;
                }
            }
        }
    }
    rep(i,0,n)rep(j,0,n) col[i][j+1] += col[i][j];
    rep(i,0,3*n)rep(j,0,n) diag[i][j+1] += diag[i][j];
    vector<vector<ll>> sum(n,vector<ll>(n,0));
    rep(i,0,n)rep(j,0,n){
        sum[i][j] += col[j][i];
    }
    rep(k,0,3*n)rep(i,0,n){
        int j = k - i*2;
        if(j >= 0 && j < n) sum[i][j] += diag[k][i];
    }
    rep(i,0,n)rep(j,0,n-1) sum[i][j+1] += sum[i][j];
    int q; cin >> q;
    while(q--){
        int x, y; cin >> x >> y;
        x--; y--;
        cout << sum[x][y] << endl;
    }

    return 0;
}