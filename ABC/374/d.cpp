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
    cout << fixed << setprecision(20);
    ll n;double s, t; cin >> n >> s >> t;
    vector<ll> a(n), b(n), c(n), d(n);
    rep(i,0,n) cin >> a[i] >> b[i] >> c[i] >> d[i];
    vector<ll> vec(n);
    iota(vec.begin(), vec.end(), 0);
    double ans = INF;
    do{
        rep(bit,0,1<<n){
            ll x = 0, y = 0;
            double num = 0;
            rep(i,0,n){
                if(bit>>i&1){
                    num += sqrt((double)(x-a[vec[i]])*(x-a[vec[i]]) + (y-b[vec[i]])*(y-b[vec[i]]))/s;
                    num += sqrt((double)(c[vec[i]]-a[vec[i]])*(c[vec[i]]-a[vec[i]]) + (d[vec[i]]-b[vec[i]])*(d[vec[i]]-b[vec[i]]))/t;
                    x = c[vec[i]];
                    y = d[vec[i]];
                }
                else{
                    num += sqrt((double)(x-c[vec[i]])*(x-c[vec[i]]) + (y-d[vec[i]])*(y-d[vec[i]]))/s;
                    num += sqrt((double)(a[vec[i]]-c[vec[i]])*(a[vec[i]]-c[vec[i]]) + (b[vec[i]]-d[vec[i]])*(b[vec[i]]-d[vec[i]]))/t;
                    x = a[vec[i]];
                    y = b[vec[i]];
                }
            }
            chmin(ans, num);
        }
    }while(next_permutation(vec.begin(), vec.end()));
    cout << ans << endl;
    return 0;
}