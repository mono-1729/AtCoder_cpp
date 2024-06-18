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
    ll n,m,k; cin >> n >> m >> k;
    vector<vector<char>> ans(n*2+1, vector<char>(m*2+1, '+'));
    rep(i,0,n)rep(j,0,m) ans[i*2+1][j*2+1] = 'o';
    rep(i,0,n)rep(j,0,m-1) ans[i*2+1][j*2+2] = '|';
    rep(i,0,n-1){
        rep(j,0,m-1) ans[i*2+2][j*2+1] = '-';
        ans[i*2+2][m*2-1] = '.';
    }
    ans[0][m*2-1] = 'S';
    ans[n*2][m*2-1] = 'G';
    if(k<n || (k-n)%2==1){
        cout << "No" << endl;
        return 0;
    }
    k-=n;
    for(int i = 0; i<n-1; i+=2){
        rrep(j,m-1,1){
            if(k>0){
                ans[2*i+1][2*j] = '.';
                ans[2*i+2][2*j-1] = '.';
                ans[2*i+3][2*j] = '.';
                ans[2*i+2][2*j+1] = '-';
                k-=2;
            }
        }
    }

    for(int j = 0; j<m-2; j+=2){
        if(k>0){
            ans[2*n-2][2*j+1] = '.';
            ans[2*n-1][2*j+2] = '.';
            ans[2*n-2][2*j+3] = '.';
            ans[2*n-3][2*j+2] = '|';
            k-=2;
        }
    }

    cout << "Yes" << endl;
    rep(i,0,n*2+1){
        rep(j,0,m*2+1) cout << ans[i][j];
        cout << endl;
    }
    return 0;
}