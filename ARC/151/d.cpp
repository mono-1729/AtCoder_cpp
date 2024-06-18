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
    ll n,q; cin >> n >> q;
    vector<mint> a(1<<n);
    rep(i,0,1<<n){
        ll tmp; cin >> tmp;
        a[i] = tmp;
    }
    vector<vector<int>> query(18);
    rep(i,0,q){
        ll x, y; cin >> x >> y;
        query[x].push_back(y);
    }
    rep(i,0,n){
        mint n00 = 1, n01 = 0, n10 = 0, n11 = 1;
        for(auto y: query[i]){
            if(y == 0) n10 += n00, n11 += n01;
            else n00 += n10, n01 += n11;
        }
        vector<mint> newa(1<<n);
        rep(j,0,1<<n){
            if(j>>i&1){
                newa[j] = a[j]*n11 + a[j^(1LL<<i)]*n10;
            }
            else{
                newa[j] = a[j]*n00 + a[j^(1LL<<i)]*n01;
            }
        }
        swap(a,newa);
    }
    for(auto x: a) cout << x.val() << " ";
    cout << endl;
    return 0;   
}