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
    ll n; cin >> n;
    vector<ll> a(n), b(n);
    vector<pll> vec(n);
    rep(i,0,n) cin >> a[i];
    rep(i,0,n) cin >> b[i];
    rep(i,0,n) vec[i] = {a[i], b[i]};
    sort(vec.begin(), vec.end(), greater<pll>());
    rep(i,0,n)rep(j,i+1,n)if(a[i] == a[j] && b[i] != b[j]){
        cout << "No" << endl;
        return 0;
    }
    cout << "Yes" << endl;
    ll num = 1e10;
    if(n == 1 || vec[0].first == 0){
        cout << 1 << endl;
        if(vec[0].first <= vec[0].second) cout << vec[0].second - vec[0].first  << " " << num<< endl;
        else cout << num + vec[0].second - vec[0].first << " " << num << endl;
        return 0;
    }
    cout << n << endl;
    ll sum = num + vec[n-1].second - vec[0].second - vec[n-1].first;
    cout << num + vec[n-1].second - vec[0].second - vec[n-1].first << " " << sum + vec[0].first << endl;  
    rep(i,1,n-1){
        sum += num + vec[i-1].second - vec[i].second;
        cout << num + vec[i-1].second - vec[i].second << " " << sum + vec[i].first << endl;
    }
    cout << vec[n-2].second << " " << num << endl;

    return 0;
}