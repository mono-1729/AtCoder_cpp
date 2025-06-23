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
    if(n <= 12){
        vector<vector<ll>> a(n,vector<ll>(n));
        rep(i,0,n) cin >> a[0][i];
        rep(i,1,n) cin >> a[i][0];
        rep(i,1,n)rep(j,1,n){
            if(min(a[i-1][j],a[i][j-1]) != 0) a[i][j] = 0;
            else if(a[i-1][j] == 1 || a[i][j-1] == 1) a[i][j] = 2;
            else a[i][j] = 1;
        }
        vector<ll> cnt(3);
        rep(i,0,n)rep(j,0,n) cnt[a[i][j]]++;
        cout << cnt[0] << " " << cnt[1] << " " << cnt[2] << endl;
    }else{
        vector<vector<ll>> tate(n,vector<ll>(10)), yoko(10,vector<ll>(n));
        rep(i,0,n) cin >> yoko[0][i];
        rep(i,1,n) cin >> tate[i][0];
        rep(i,0,10) tate[0][i] = yoko[0][i];
        rep(i,1,10) yoko[i][0] = tate[i][0];
        rep(i,1,n)rep(j,1,10){
            if(min(tate[i-1][j],tate[i][j-1]) != 0) tate[i][j] = 0;
            else if(tate[i-1][j] == 1 || tate[i][j-1] == 1) tate[i][j] = 2;
            else tate[i][j] = 1;
        }
        rep(i,1,10)rep(j,1,n){
            if(min(yoko[i-1][j],yoko[i][j-1]) != 0) yoko[i][j] = 0;
            else if(yoko[i-1][j] == 1 || yoko[i][j-1] == 1) yoko[i][j] = 2;
            else yoko[i][j] = 1;
        }
        vector<ll> cnt(3);
        rep(i,0,10)rep(j,0,n) cnt[yoko[i][j]]++;
        rep(i,10,n)rep(j,0,10) cnt[tate[i][j]]++;
        rep(i,10,n){
            cnt[yoko[9][i]] += n-i-1;
            cnt[tate[i][9]] += n-i-1;
        }
        cnt[yoko[9][9]] += n-10;
        cout << cnt[0] << " " << cnt[1] << " " << cnt[2] << endl;
        // rep(i,0,10){
        //     rep(j,0,n) cout << yoko[i][j] << " ";
        //     cout << endl;
        // }
    }
    return 0;
}