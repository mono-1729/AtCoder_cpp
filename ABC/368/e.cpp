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
    ll n, m, x0; cin >> n >> m >> x0;
    vector<ll> delay(m);
    delay[0] = x0;
    vector<ll> arrive(n,0);
    vector<tuple<ll,ll,ll>> event;
    vector<ll> a(m), b(m);
    rep(i,0,m){
        ll a_, b_, s, t; cin >> a_ >> b_ >> s >> t;
        a_--; b_--;
        a[i] = a_;
        b[i] = b_;
        event.push_back({s, 1, i});
        event.push_back({t, -1, i});
    }
    sort(event.begin(), event.end());
    for(auto [t, d, i] : event){
        if(d == -1){
            chmax(arrive[b[i]], t + delay[i]);
        }else{
            ll time = max(arrive[a[i]], t);
            if(i != 0) delay[i] = time - t;
        }
    }
    rep(i,1,m) cout << delay[i] << " ";
    cout << endl;
    return 0;
}