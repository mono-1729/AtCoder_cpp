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

class xor_set{
private:
    vector<ll> w;
public:
    xor_set () {}
    void insert(ll x){
        for(ll v : w) if(v & -v & x) x ^= v;
        if(x == 0) return;
        for(ll& v : w) if(x & -x & v) v ^= x;
        w.push_back(x);
    }
    // 独立か判定
    ll count(ll x){
        for(ll v : w) if(v & -v & x) x ^= v;
        if(x == 0) return 1;
        else return 0;
    }
    vector<ll> get(){return w;}
};

int main() {
    ll n; cin >> n;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    ll ans = 0;
    ll num = 0;
    rrep(i,59,0){
        xor_set st;
        int cnt = 0;
        rep(j,0,n) if(a[j] >> i & 1) cnt++;
        if(cnt%2 == 1){
            rep(j,0,n) a[j] &= (a[j] ^ (1LL << i));
            num += 1LL << i;
        }
        rep(j,0,n) st.insert(a[j] >> i);
        if(st.count((ans >> i) | 1)){
            ans |= 1LL << i;
            num += 1LL << i;
        }
        else rep(j,0,n) a[j] &= (a[j] ^ (1LL << i));
    }
    cout << ans + num << endl;
    return 0;
}