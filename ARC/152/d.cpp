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
    ll n, k; cin >> n >> k;
    if(n%2 == 0){
        cout << -1 << endl;
        return 0;
    }
    ll g = gcd(n,k);
    vector<pll> ans;
    vector<vector<ll>> nums(n/g);
    rep(i,0,g)nums[0].push_back(i);
    rep(i,0,n/g-1)rep(j,0,g) nums[i+1].push_back((nums[i][j]+k)%n);
    rep(x,0,n/g)rep(y,0,g){
        if(x%2 == 0 && x != n/g-1 && y%2 == 0) ans.push_back({nums[x][y], nums[x+1][y]});
        if(x%2 == 0 && x != n/g-1 && y%2 == 0 && y != g-1) ans.push_back({nums[x][y], nums[x][y+1]});
        if(x == n/g -2 && y%2 == 1) ans.push_back({nums[x][y], nums[x][y+1]});
    }
    cout << ans.size() << endl;
    for(auto [a,b] : ans) cout << a << " " << b << endl;
    return 0;
}