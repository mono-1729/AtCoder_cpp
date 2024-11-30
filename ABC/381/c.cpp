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
    string s; cin >> s;
    vector<pair<char, ll>> v;
    ll now = 0;
    while(now < n){
        char c = s[now];
        ll cnt = 0;
        while(now < n && s[now] == c){
            now++;
            cnt++;
        }
        v.push_back({c, cnt});
    }
    ll ans = 1;
    rep(i,0,(ll)v.size()-2){
        if(i+2 >= v.size()) break;
        auto [c1, cnt1] = v[i];
        auto [c2, cnt2] = v[i+1];
        auto [c3, cnt3] = v[i+2];
        if(c1 == '1' && c2 == '/' && c3 == '2' && cnt2 == 1){
            chmax(ans,min(cnt1, cnt3)*2+1);
        }
    }

    cout << ans << endl;
    return 0;
}