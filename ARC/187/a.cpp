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
    vector<ll> a(n);
    rep(i, 0, n) cin >> a[i];
    // ll n = 50, k = 1;
    // vector<ll> a(n);
    // rep(i,0,n) a[i] = 50-i;
    vector<ll> ans;
    auto Do = [&](ll i) -> void {
        ans.push_back(i+1);
        swap(a[i], a[i+1]);
        a[i] += k;
    };
    auto print = [&]() {
        cout << "Yes" << endl;
        cout << ans.size() << endl;
        for(auto x: ans) cout << x << " ";
    };
    if(n == 2){
        if(a[0] <= a[1]) print();
        else if(a[1]+k <= a[0]){
            Do(0);
            print();
        }else cout << "No" << endl;
        return 0;
    }
    rep(i,1,n-1){
        while(a[i-1] > a[i]){
            Do(i), Do(i);
        }
    }
    while(a[n-3] > a[n-1] || a[n-3] > a[n-2]) Do(n-2), Do(n-2);
    Do(n-3);
    while(a[n-3] > a[n-2]) Do(n-2), Do(n-2);
    print();
    return 0;
}