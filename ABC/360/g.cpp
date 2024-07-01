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

using S = long long;
S op(S x1, S x2) {
    return max(x1,x2);
} 
bool f(S x){
    return 1;
}
S e() {return -INF;}

int main() {
    ll n; cin >> n;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    set<ll> st1, st2;
    st1.insert(-1);
    st2.insert(-1);
    st2.insert(0);
    rep(i,0,n){
        st1.insert(a[i]);
        st2.insert(a[i]);
        st2.insert(a[i]+1);
    }
    unordered_map<ll,ll> mp1, mp2;
    int cnt1 = 0, cnt2 = 0;
    for(auto x: st1){
        mp1[x] = cnt1;
        cnt1++;
    }
    for(auto x: st2){
        mp2[x] = cnt2;
        cnt2++;
    }
    segtree<S,op,e> seg1(cnt1), seg2(cnt2);
    seg1.set(0,0);
    seg2.set(0,0);
    ll pre = -1;
    rep(i,0,n){
        seg1.set(mp1[a[i]],seg1.prod(0,mp1[a[i]])+1);
        ll tmp = seg2.prod(0,mp2[a[i]])+1;
        seg2.set(mp2[pre+1],seg1.prod(0,mp1[pre]+1)+1);
        seg2.set(mp2[a[i]],tmp);
        pre = a[i];
    }
    cout << seg2.all_prod() << endl;
    return 0;
}