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
    cout << fixed << setprecision(15);
    ll n; cin >> n;
    vector<vector<ll>> dice(n);
    vector<vector<ll>> oknum(n,vector<ll>(n,0));
    rep(i,0,n){
        ll k; cin >> k;
        dice[i].resize(k);
        rep(j,0,k){
            cin >> dice[i][j];
        }
    }
    rep(i,0,n){
        unordered_map<ll,ll> mp;
        rep(j,0,dice[i].size())mp[dice[i][j]]++;
        rep(j,i+1,n){
            rep(k,0,dice[j].size()){
                oknum[i][j] += mp[dice[j][k]];
                oknum[j][i] += mp[dice[j][k]];
            }
        }
    }
    double ans = 0;
    rep(i,0,n)rep(j,i+1,n){
        ll num = oknum[i][j];
        // cout << ans << " " << num << " " << dice[i].size() << " " << dice[j].size() << endl;
        chmax(ans,(double)num / (dice[i].size() * dice[j].size()));
    }
    cout << ans << endl;
    return 0;
}