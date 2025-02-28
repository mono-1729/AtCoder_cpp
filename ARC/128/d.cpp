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

using S = mint;
S op(S x1, S x2) {
    return x1+x2;
}
S e() {return 0;}

int main() {
    ll n; cin >> n;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    segtree<S,op,e> seg(n);
    seg.set(0,1);
    vector<ll> vec = {0};
    rep(i,0,n-1){
        if(a[i] == a[i+1]) vec.push_back(i+1);
    }
    ll right = 0, type = 1;
    unordered_map<ll,ll> mp;
    mp[a[0]]++;
    rep(i,1,n){
        if(mp[a[i]] == 0) type++;
        mp[a[i]]++;
        while(type > 2){
            mp[a[right]]--;
            if(mp[a[right]] == 0) type--;
            right++;
        }
        ll l = vec[upper_bound(all(vec), i) - vec.begin() - 1];
        ll r = min(i-2, right);
        mint num = seg.get(i-1);
        if(i >= 2 && a[i] != a[i-1] && a[i-1] != a[i-2]) num += seg.get(i-2);
        if(l < r) num += seg.prod(l,r); 
        seg.set(i,num);
    }
    cout << seg.get(n-1).val() << endl;
    return 0;
}